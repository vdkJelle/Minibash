/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 22:51:14 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/13 17:13:20 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_word	**get_arguments(t_data *data, char *s, char control_operator)
{
	int		i;
	int		loc;
	int		size;
	t_word	**args;

	size = count_arguments(s, control_operator);
	args = malloc(sizeof(t_word*) * (size + 1));
	if (!args)
		exit(1);
	loc = 0;
	i = 0;
	while (i < size)
	{
		args[i] = ft_calloc(1, sizeof(t_word));
		if (!args[i])
			exit(1);
		loc += get_arg(data, &args[i], s + loc, control_operator);
		args[i]->word = join_word(args[i]);
		i++;
	}
	args[i] = NULL;
	return (args);
}

static t_word	*get_command(t_data *data, char *s, char control_operator)
{
	int		i;
	t_word	*command;

	command = ft_calloc(1, sizeof(t_word));
	if (!command)
		exit(1);
	i = 0;
	while (s[i] && s[i] != control_operator)
	{
		i++;
		if (is_metacharacter(s[i]))
			break ;
	}
	get_arg(data, &command, s, s[i]);
	command->word = join_word(command);
	return (command);
}

static char	*get_control_operator(char *s)
{
	char	*ret;

	ret = ft_substr(s, 0, skip_while_char(s, is_control_operator));
	if (!ret)
		exit(1);
	return (ret);
}

static int	tokenize(t_data *data, char *s, char *p_control_operator)
{
	int		loc;
	t_token	*token;

	loc = skip_while_char(s, is_metacharacter);
	if (!s[loc])
	{	
		data->exit_status = 0;
		return (0);
	}
	token = (t_token*)malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->cmd = get_command(data, s + loc, *p_control_operator);
	if (!token->cmd)
		exit(1);
	loc += skip_while_not_char(s + loc, is_metacharacter);
	loc += skip_while_char(s + loc, is_whitespace);
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
	
	if (check_multiline_command(data, s))
		return ;
	token_start = 0;
	i = 0;
	while (s[i])
	{
		if (is_control_operator(s[i]) && !(count_backslash(s, i) % 2))
		{
			i += tokenize(data, s + token_start, s + i);
			token_start = i;
		}
		else if (s[i] == '\"' && !(count_backslash(s, i) % 2))
			i += skip_until_next_doubleq(s + i);
		else if (s[i] == '\'' && !(count_backslash(s, i) % 2))
			i += skip_until_next_singleq(s + i);
		if (s[i])
			i++;
	}
	tokenize(data, s + token_start, s + ft_strlen(s));
}

// static char **get_arguments(t_data *data, char *s, char control_operator)
// {
// 	char	**ret;
// 	int		i;
// 	int		loc;
// 	int		size;

// 	size = count_arguments(s, control_operator);
// 	ret = malloc(sizeof(char*) * (size + 1));
// 	if (!ret)
// 		exit(1);
// 	loc = 0;
// 	i = 0;
// 	while (i < size)
// 	{
// 		ret[i] = ft_strdup("");
// 		if (!ret[i])
// 			exit(1);
// 		loc += get_arg(data, &ret[i], s + loc, control_operator);
// 		i++;
// 	}
// 	ret[i] = NULL;
// 	return (ret);
// }

// static char	*get_command(t_data *data, char *s, char control_operator)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	while (s[i] && s[i] != control_operator)
// 	{
// 		i++;
// 		if (is_metacharacter(s[i]))
// 			break ;
// 	}
// 	ret = ft_strdup("");
// 	if (!ret)
// 		exit(1);
// 	get_arg(data, &ret, s, s[i]);
// 	return (ret);
// }