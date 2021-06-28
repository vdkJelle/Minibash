 /* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_handle_arg_chars.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 14:29:30 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/04/28 16:32:47 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Saves a single character as a word segment
** Returns 1
*/

int		handle_char(t_data *data, t_word **word, char *s)
{
	char	*single_char;
	
	(void)data;
	if (!s)
		return (-1);
	single_char = malloc(sizeof(char) * 2);
	if (!single_char)
		exit(1);
	single_char[0] = s[0];
	single_char[1] = '\0';
	ft_lstadd_back(&((*word)->word_segment), ft_lstnew(single_char));
	if (!(*word)->word_segment)
		exit(1);
	return (1);
}

/*
** Saves everything between double quotes as a word segment
** If the next character is a double quote, nothing is saved
** If there is a backslash and the next character is a backslash, double quote
**		or dollar sign, the next character is saved instead of the current
** If there is a dollar sign environmental variables have to be handles if
**		the next character is not a double quote
**		the next character is the first character of a valid identifier
** Returns index of the end of the word segment
*/

int		handle_doublequotes(t_data *data, t_word **word, char *s)
{
	int		i;
	
	if (s[1] && s[1] == '\"')
		return (2);
	i = 1;
	while (s[i] && (s[i] != '\"'
	|| (s[i] == '\"' && count_backslash(s, i) % 2)))
	{
		if (s[i] == '\\' && s[i + 1] && ft_strchr("\\\"$", s[i + 1]))
			i += handle_char(data, word, s + i + 1);
		else if (s[i] == '$' && !(count_backslash(s, i) % 2)
		&& s[i + 1] != '\"' && !(s[i + 1] != '_' && !ft_isalpha(s[i + 1])))
			i += handle_environment_variable(data, word, s + i) - 1;
		else
			handle_char(data, word, s + i);
		i++;
	}
	return (i + 1);
}

/*
** Adds the value of an environmental variable as a word segment
** If the next character is a question mark
**		the exit status is saved as a word segment
** Looks up the value of an environmental variable with get_env based on the key
** If no value is found nothing is saved
** Returns index of the end of the key
*/

int		handle_environment_variable(t_data *d, t_word **word, char *s)
{
	char	*key;
	char	*value;
	int		len;

	if (s[0] == '$' && s[1] != '?')
	{
		len = 0;
		while (s[len + 1] && (s[len + 1] == '_' || ft_isalnum(s[len + 1])))
			len++;
		key = ft_substr(s, 1, len);
		if (!key)
			exit(1);
		value = get_env(d->our_env, key);
		free(key);
		if (!value || value[0] == '\0')
			return (len + 1);
		ft_lstadd_back(&((*word)->word_segment), ft_lstnew(ft_strdup(value)));
		if (!(*word)->word_segment)
			exit(1);
		return (len + 1);
	}
	ft_lstadd_back(&(*word)->word_segment, ft_lstnew(ft_itoa(d->exit_status)));
	if (!(*word)->word_segment)
		exit(1);
	return (2);
}

/*
** Saves metacharacters as a word
** Only if they are the encountered as the first character of a new word
** Whitespaces are never saved
** Returns index of the end of the word + potentially skipped whitespaces
*/

int		handle_metacharacter(t_data *data, t_word **word, char *s)
{
	int		i;

	(void)data;
	i = skip_while_char(s, is_whitespace);
	while (is_metacharacter(s[i])
	&& !is_whitespace(s[i]) && !is_control_operator(s[i]))
	{
		handle_char(data, word, s + i);
		(*word)->metacharacter = 1;
		i++;
	}
	i += skip_while_char(s + i, is_whitespace);
	return (i);
}

/*
** Saves everything between single quotes as a word segment
** If the next character is a single quote, nothing is saved
** Returns index of the end of the word segment
*/

int		handle_singlequotes(t_data *data, t_word **word, char *s)
{
	int		i;
	int		len;

	(void)data;
	i = 0;
	if (s[i + 1] && s[i + 1] == '\'')
		return (2);
	len = skip_until_char_excl(s + 1, '\'');
	if (len > 0)
	{
		ft_lstadd_back(&((*word)->word_segment), ft_lstnew(ft_substr(s, 1, len)));
		if (!(*word)->word_segment)
			exit(1);
	}
	return (len + 2);
}
