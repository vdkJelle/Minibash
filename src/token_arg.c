/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_arg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 20:56:05 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/18 19:08:06 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Determines the type of character that has been encountered
** Checks if special characters are not escaped
** In case of an environmental character also checkes if
**		the next character is not a control operator
**		the next character is the first character of a valid identifier
** Returns the type of character
*/

arg_characters	get_arg_characters(char *s, int i)
{
	if (s[i] == '\'' && !(count_backslash(s, i) % 2))
		return (SINGLEQUOTE);
	else if (s[i] == '\"' && !(count_backslash(s, i) % 2))
		return (DOUBLEQUOTE);
	else if (s[i] == '\\' && !(count_backslash(s, i) % 2))
		return (BACKSLASH);
	else if (s[i] == '$' && !(count_backslash(s, i) % 2)
	&& !is_control_operator(s[i + 1])
	&& !(s[i + 1] != '_' && s[i + 1] != '?' && !ft_isalpha(s[i + 1])))
		return (ENVIRONMENT_VARIABLE);
	else if (is_metacharacter(s[i]) && !(count_backslash(s, i) % 2))
		return (METACHARACTER);
	else
		return (CHAR);
}

/*
** Gets the argument
** An argument is a word and words are seperated by metacharacters
** Checks if the first character is a metacharacter
**		it is saved as a word to check for a redirection or parser error later
** Loops over the input string and calls get_arg_character
**		to see which arg_handler function needs to be called
** If the character is a backslash it can be skipped
** If the character is a metacharacter the end of the word has been reached and
**		the function returns
** If the character is not a backslash or a metacharacter the correct
**		arg_handler function is called where word segments are added to the word
** Returns index of the end of the word
*/

int				get_arg(t_data *data, t_word **word, char *s, char control_op)
{
	int				i;
	arg_characters	ac;
	f_arg_handler	arg_handler[5];

	arg_handler[CHAR] = handle_char;
    arg_handler[DOUBLEQUOTE] = handle_doublequotes;
    arg_handler[ENVIRONMENT_VARIABLE] = handle_environment_variable;
	arg_handler[METACHARACTER] = handle_metacharacter;
    arg_handler[SINGLEQUOTE] = handle_singlequotes;
	if (s[0] && is_metacharacter(s[0]))
		return (arg_handler[METACHARACTER](data, word, s));
	i = 0;
	while (s[i] && s[i] != control_op)
	{
		ac = get_arg_characters(s, i);
		if (ac == BACKSLASH)
			i++;
		else if (ac == METACHARACTER)
			return (i + skip_while_char(s + i, is_whitespace));
		else
			i += arg_handler[ac](data, word, s + i);
	}
	return (i);
}
