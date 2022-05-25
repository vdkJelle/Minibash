/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 22:51:14 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/05/25 16:10:02 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Gets the arguments
** Calls count_arguments to get the size of the array of arguments
** Calls get_arg to get the word segements of the argument
** Calls join word to merge the word segments of the command into one word
** Returns an malloced array of malloced t_word structs
*/

static t_word	**get_arguments(t_data *data, char *s, char control_operator)
{
	int		i;
	int		loc;
	int		size;
	t_word	**args;

	size = count_arguments(s, control_operator);
	args = ft_malloc(sizeof(t_word*) * (size + 1));
	loc = 0;
	i = 0;
	while (i < size)
	{
		args[i] = malloc_guard(ft_calloc(sizeof(t_word), 1));
		loc += get_arg(data, &args[i], s + loc, control_operator);
		args[i]->word = join_word(args[i]);
		i++;
	}
	args[i] = NULL;
	return (args);
}

/*
** Gets the command
** Calls get arg to get the word segements of the command
** Calls join word to merge the word segments of the command into one word
** Returns a malloced t_word struct
*/

// static t_word	*get_command(t_data *data, char *s, char control_operator)
// {
// 	int		i;
// 	t_word	*command;

// 	command = ft_calloc(sizeof(t_word), 1);
// 	if (!command)
// 		exit(1);
// 	i = 0;
// 	while (s[i] && s[i] != control_operator)
// 	{
// 		if (is_metacharacter(s[i]))
// 			break ;
// 		i++;
// 	}
// 	get_arg(data, &command, s, s[i]);
// 	command->word = join_word(command);
// 	return (command);
// }

/*
** Gets the control operator
** Returns a malloced string with the control operator
*/

static char	*get_control_operator(char *s)
{
	char	*ret;

	ret = malloc_guard(ft_substr(s, 0, skip_while_char(s, is_control_operator)));
	return (ret);
}

/*
** Creates a token set and adds it to the to the linked list
** Each token set consists of
**		arguments, none, one or more words
**		control operator, a string with one or a combinations of ; | ( ) &
** Words are seperated by metacharacters
** Returns an index to the end of the token set
** Returns 0 if the input is empty or only consists of whitespaces
** Returns 1 if the input only consists of ; with nothing or whitespaces after it
*/

static int	create_token(t_data *data, char *s, char *p_control_operator)
{
	int		loc;
	t_token	*token;

	loc = skip_while_char(s, is_whitespace);
	if (!s[loc])
		return (0);
	if ((s[loc] == ';' && (!s[loc + 1] || (s[loc + 1] && is_whitespace(s[loc + 1])))))
		return (1);
	token = malloc_guard(ft_calloc(sizeof(t_token), 1));
	if (!token)
		exit(1);
	if (!is_control_operator(s[loc]))
	{
		// token->cmd = get_command(data, s + loc, *p_control_operator);
		// loc += skip_while_not_char(s + loc, is_metacharacter);
		// loc += skip_while_char(s + loc, is_whitespace);
		token->arg = get_arguments(data, s + loc, *p_control_operator);
		token->cop = get_control_operator(p_control_operator);
	}
	else
		token->cop = get_control_operator(s + loc);
	ft_lstadd_back(&data->token, ft_lstnew(token));
	return (ft_strlen(token->cop));
}

static int	tokenize(t_data *data, char *s, int start, int end)
{
	int		i;
	// char	*substring;
	
	i = end;
	if (s[i] == ';')
		i += create_token(data, s + start, s + end);
	else
	{
		// substring = malloc_guard(ft_substr(s, start, end - start + 1));
		// i += create_token(data, substring, s + end);
		// free(substring);
				i += create_token(data, s + start, s + end);
	}
	return (i);
}

/*
** Tokenizes and parses the input
** Each token set is seperated by control operators
** No return value
*/

void	get_token(t_data *data, char *s)
{
	int		i;
	int		token_start;

	token_start = 0;
	i = 0;
	while (s[i])
	{
		i += skip_while_char(s + i, is_whitespace);
		if (is_control_operator(s[i]) && !(count_backslash(s, i) % 2))
		{
			i = tokenize(data, s, token_start, i);
			token_start = i;
		}
		else if (s[i] == '\"' && !(count_backslash(s, i) % 2))
			i += skip_until_next_doubleq(s + i);
		else if (s[i] == '\'' && !(count_backslash(s, i) % 2))
			i += skip_until_next_singleq(s + i);
		if (s[i])
			i++;
	}
	i += tokenize(data, s, token_start, i);
}
