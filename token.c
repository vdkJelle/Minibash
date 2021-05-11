/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 22:51:14 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/11 23:08:48 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*join_word(t_word *arg)
{
	char	*word;
	int		size;
	t_list	*temp;

	temp = arg->word_segment;
	size = 0;
	while (temp)
	{
		size += ft_strlen(((char*)temp->content));
		temp = temp->next;
	}
	word = ft_calloc(size + 1, sizeof(char));
	if (!word)
		exit(1);
	temp = arg->word_segment;
	while (temp)
	{
		ft_strlcat(word, (char*)temp->content, size + 1);
		temp = temp->next;
	}
	return (word);
}

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

static t_word	*get_command(t_data *data, char *s, char control_operator)
{
	int		i;
	t_word	*command;

	i = 0;
	while (s[i] && s[i] != control_operator)
	{
		i++;
		if (is_metacharacter(s[i]))
			break ;
	}
	command = ft_calloc(1, sizeof(t_word));
	if (!command)
		exit(1);
	get_arg(data, &command, s, s[i]);
	command->word = join_word(command);
	return (command);
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

// crashes with echo hi ;;
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
		// perror("-1");
		// printf("s = %s\n", s + i);
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
