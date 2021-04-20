/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 22:51:14 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/04/09 12:35:44 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **get_arguments(t_data *data, char *s, char control_operator)
{
	char	**ret;
	int		i;
	int		loc;
	int		size;

	size = count_arguments(s, control_operator);
	ret = malloc(sizeof(char*) * (size + 1));
	if (!ret)
		exit(1);
	loc = 0;
	i = 0;
	while (i < size)
	{
		ret[i] = ft_strdup("");
		if (!ret[i])
			exit(1);		
		loc += get_arg(data, &ret[i], s + loc, control_operator);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

static char	*get_command(t_data *data, char *s, char control_operator)
{
	char	*ret;
	int		i;

	i = 0;
	while (s[i] && s[i] != control_operator)
	{
		i++;
		if (is_metacharacter(s[i]))
			break;
	}
	ret = ft_strdup("");
	if (!ret)
		exit(1);
	get_arg(data, &ret, s, s[i]);
	return (ret);
}

static char	*get_control_operator(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	while (s[i] && is_control_operator(s[i]))
		i++;
	ret = ft_substr(s, 0, i);
	if (!ret)
		exit(1);
	return (ret);
}

static int	tokenize(t_data *data, char *s, char *p_control_operator)
{
	int		loc;
	t_token	*token;

	loc = skip_whitespaces_int(s);
	if (!s[loc])
		return (0);
	token = (t_token*)malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->cmd = get_command(data, s + loc, *p_control_operator);
	if (!token->cmd)
		exit(1);
	loc += skip_until_char_function(s + loc, is_metacharacter);
	loc += skip_whitespaces_int(s + loc);
	token->arg = get_arguments(data, s + loc, *p_control_operator);
	if (!token->arg)
		exit(1);
	token->cop = get_control_operator(p_control_operator);
	if (!token->cop)
		exit(1);
	ft_lstadd_back(&data->token, ft_lstnew(token));
	return (ft_strlen(token->cop));
}

void	get_token(t_data *data, char *s)
{
	int		i;
	int		token_start;
	
	if (count_quotes(s) == -1)
		return (ft_putstr_fd("Multiline command1\n", 2));
	if (count_backslash(s, ft_strlen(s)) % 2 != 0)
		return (ft_putstr_fd("Multiline command2\n", 2));
	if (ft_strlen(s) > 0 && s[ft_strlen(s) - 1] == '|')
		return (ft_putstr_fd("Multiline command3\n", 2));
	token_start = 0;
	i = 0;
	while (s[i])
	{
		if (is_control_operator(s[i]) && !(count_backslash(s, i) % 2))
		{
			token_start += i + tokenize(data, s + token_start, s + i);
			i = token_start;
		}
		else if (s[i] == '\'' && !(count_backslash(s, i) % 2))
			i += skip_until_char_incl(s + i + 1, '\'');
		else if (s[i] == '\"' && !(count_backslash(s, i) % 2))
			i += skip_doubleq(s + i + 1);
		i++;
	}
	tokenize(data, s + token_start, s + ft_strlen(s));
}
