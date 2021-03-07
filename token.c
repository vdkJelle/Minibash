/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 12:37:26 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/03/07 20:00:51 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_key(char *s)
{
	int		len;
	char	*key;
	
	len = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (NULL);
	while (s[len] && (ft_isalpha(s[len]) || ft_isdigit(s[len]) || s[len] == '_'))
		len++;
	key = ft_substr(s, 0, len);
	if (!key)
		exit(1);
	return (key);
}

static int	arg_env_between_doubleq(char **ret, char **our_env, char *s)
{
	int		len;
	char	*key;
	char	*value;

	len = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
	{
		if (s[len] != '\"')
			len++;
		while (s[len] && !is_whitespace(s[len]) && s[len] != '\"' && s[len] != '\\')
			len++;
		return (len);
	}
	while (s[len] && (ft_isalpha(s[len]) || ft_isdigit(s[len]) || s[len] == '_'))
		len++;
	key = ft_substr(s, 0, len);
	if (!key)
		exit(1);
	value = get_env(our_env, key);
	free(key);
	if (value)
		*ret = ft_strjoin_free_s1(*ret, value);
	return (len);
}

static int	arg_between_doubleq(char **ret, char **our_env, char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '\"')
	{
		if (s[i] == '\\')
		{
			if (ft_strchr("\\\"", s[i + 1]))
			{
				*ret = ft_strjoin_char(*ret, s[i + 1]);
				i++;
			}
			else
				*ret = ft_strjoin_char(*ret, s[i]);
		}
		else if (s[i] == '$' && count_backslash(s, i) % 2 == 0)
			i += arg_env_between_doubleq(ret, our_env, s + i + 1);
		else
			*ret = ft_strjoin_char(*ret, s[i]);
		i++;
		if (s[i] == '\"' && count_backslash(s, i) % 2 != 0)
		{
			*ret = ft_strjoin_char(*ret, s[i]);
			i++;
		}
	}
	return (i);
}

static int	put_arg(t_data *data, char **ret, char *s, char c)
{
	char	*key;
	char	*value;
	int		i;
	int		len;

	*ret = ft_strdup("");
	key = NULL;
	i = 0;
	i += skip_whitespaces_int(s);
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\'' && count_backslash(s, i) % 2 == 0)
		{
			len = skip_until_char(s + i + 1, '\'');
			*ret = ft_strjoin_free_both(*ret, ft_substr(s, i + 1, len));
			i += len + 1;
		}
		else if (s[i] == '\"' && count_backslash(s, i) % 2 == 0)
		{
			len = arg_between_doubleq(ret, data->our_env, s + i + 1);
			i += len + 1;
		}
		else if (s[i] == '\\')
		{
			if (i > 0 && count_backslash(s, i) % 2 != 0)
			{
				*ret = ft_strjoin_free_both(*ret, ft_substr(s, i, 1));
			}
		}
		else if (s[i] == ' ' && count_backslash(s, i) % 2 == 0)
		{
			return (i);
		}
		else if (s[i] == '$' && count_backslash(s, i) % 2 == 0)
		{
			key = get_key(s + i + 1);
			value = get_env(data->our_env, key);
			*ret = ft_strjoin_free_s1(*ret, value);
			i += ft_strlen(key);
			free(key);
		}
		// else if (s[i] == '>' && count_backslash(s, i) % 2 == 0)
		// {
		// 	i += handle_redirection(data, s + i, c);
		// }
		else
			*ret = ft_strjoin_char(*ret, s[i]);
		i++;
	}
	return (i);
}

static char **get_arg(t_data *data, char *s, char c)
{
	int		i;
	int		loc;
	int		size;
	char	**arg;

	i = 0;
	loc = 0;
	size = count_arguments(s, c);
	arg = malloc(sizeof(char*) * (size + 1));
	while (i < size)
	{
		loc += put_arg(data, &arg[i], s + loc, c);
		i++;
	}
	arg[i] = NULL;
	return (arg);	
}

static int	tokenize(t_data *data, char *s, char c)
{
	int		lencmd;
	int		lenarg;
	t_token *tok;

	lencmd = 0;
	lenarg = 0;
	tok = (t_token*)malloc(sizeof(t_token));
	if (!tok)
		exit(1);
	skip_whitespaces(&s);
	lencmd += skip_nonwhitespaces_int(s);
	tok->cmd = ft_substr(s, 0, lencmd);
	if (!tok->cmd)
		exit(1);
	lencmd += skip_whitespaces_int(s);
	lenarg += skip_until_char(s + lencmd, c);
	// if (!ft_strcmp(tok->cmd, "export"))
	// 	tok->arg = get_export_arg(s + lencmd, data->our_env, c);
	// else
		tok->arg = get_arg(data, s + lencmd, c);
	if (!tok->arg)
		exit(1);
	ft_lstadd_back(&data->token, ft_lstnew(tok));
	return (lencmd + lenarg);
}

void		get_token(t_data *data, char *s)
{
	int		i;
	int		saved;

	if (count_quotes(s) == -1)
		return (ft_putstr_fd("Multis command1\n", 2));
	if (count_backslash(s, ft_strlen(s)) % 2 != 0)
		return (ft_putstr_fd("Multis command2\n", 2));
	i = 0;
	saved = 0;
	while (s[i])
	{
		if (s[i] == ';')
			saved += 1 + tokenize(data, s + saved, ';');
		else if (s[i] == '|')
			saved += 1 + tokenize(data, s + saved, '|');
		else if (s[i] == '\'' && count_backslash(s, i) % 2 == 0)
			i += skip_until_char(s + i + 1, '\'');
		else if (s[i] == '\"' && count_backslash(s, i) % 2 == 0)
			i += skip_doubleq(s + i + 1);
		i++;
	}
	tokenize(data, s + saved, '\0');
}
