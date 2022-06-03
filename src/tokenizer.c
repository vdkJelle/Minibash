/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 22:51:14 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/03 13:26:32 by tessa         ########   odam.nl         */
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

// static t_word	**get_arguments(t_data *data, char *s, char control_operator)
// {
// 	int		i;
// 	int		loc;
// 	int		size;
// 	t_word	**args;

// 	size = count_arguments(s, control_operator);
// 	args = ft_malloc(sizeof(t_word*) * (size + 1));
// 	loc = 0;
// 	i = 0;
// 	while (i < size)
// 	{
// 		args[i] = malloc_guard(ft_calloc(sizeof(t_word), 1));
// 		loc += get_arg(data, &args[i], s + loc, control_operator);
// 		args[i]->word = join_word(args[i]);
// 		i++;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }

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

// static int	create_token(t_data *data, char *s, char *p_control_operator)
// {
// 	int		i;
// 	t_token	*token;

// 	loc = skip_while_char(s, is_whitespace);
// 	if (!s[i]])
// 		return (0);
// 	if ((s[i]] == ';' && (!s[i + 1] || (s[i + 1] && is_whitespace(s[i + 1])))))
// 		return (1);
// 	token = malloc_guard(ft_calloc(sizeof(t_token), 1));
// 	if (!is_control_operator(s[i]]))
// 	{
// 		// token->cmd = get_command(data, s + loc, *p_control_operator);
// 		// loc += skip_while_not_char(s + loc, is_metacharacter);
// 		// loc += skip_while_char(s + loc, is_whitespace);
// 		token->arg = get_arguments(data, s + loc, *p_control_operator);
// 		token->control_operator = get_control_operator(p_control_operator);
// 	}
// 	else
// 		token->control_operator = get_control_operator(s + loc);
// 	ft_lstadd_back(&data->token, ft_lstnew(token));
// 	return (ft_strlen(token->control_operator));
// }

/*
** Creates a token and adds it to the to the linked list
** Each token consists of
**		a string
**		control operator, a string with one or a combinations of ; | ( ) &
** Each token is seperated by control operators
** Returns an index to the end of the token
** Returns 0 if the input is empty or only consists of whitespaces
** Returns 1 if the input only consists of ; with nothing or whitespaces after it
*/

static int create_token(t_data *data, char *s, char *p_control_operator)
{
	int		len;
	t_token	*token;

	if (!s[0])
		return (0);
	token = malloc_guard(ft_calloc(sizeof(t_token), 1));
	if (!is_control_operator(s[0]))
	{
		len = 0;
		while (s[len] != p_control_operator[0])
			len++;
		token->string = malloc_guard(ft_substr(s, 0, len));
		token->control_operator = get_control_operator(p_control_operator);
	}
	else
		token->control_operator = get_control_operator(p_control_operator);
	ft_lstadd_back(&data->token, malloc_guard(ft_lstnew(token)));
	return (ft_strlen(token->control_operator));
}

static int	tokenize(t_data *data, char *s, int *start, int *end)
{
	int	cont;

	cont = 0;
	if (s[*end] == ';')
	{
		*end += create_token(data, s + *start, s + *end);
		*end += skip_while_char(s + *end, is_whitespace);
		*start = *end;
		cont = 1;
	}
	else
	{
		*end += create_token(data, s + *start, s + *end);
		*end += skip_while_char(s + *end, is_whitespace);
		*start = *end;
		cont = 1;
	}
	return (cont);
}

/*
** Tokenizes the input
** Each token is seperated by control operators
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
			if (tokenize(data, s, &token_start, &i))
				continue ;
		}
		else if (s[i] == '\"' && !(count_backslash(s, i) % 2))
			i += skip_until_next_doubleq(s + i);
		else if (s[i] == '\'' && !(count_backslash(s, i) % 2))
			i += skip_until_char_excl(s + i, '\'');
		if (s[i])
			i++;
	}
	tokenize(data, s, &token_start, &i);
}
