/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 22:51:14 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/10/19 10:51:31 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Gets the control operator
**	Returns a malloced string with the control operator
*/

static char	*get_control_operator(char *s)
{
	char	*ret;

	ret = malloc_guard(ft_substr(s, 0,
				skip_while_char(s, is_control_operator)));
	return (ret);
}

/*
**	Creates a token and adds it to the to the linked list
**	Each token consists of
**		- a string
**		- control operator, a string with one or a combinations of ; | ( ) &
**	Returns an index to the end of the token
*/

static int	create_token(t_data *data, char *s, char *p_control_operator)
{
	t_token	*token;

	if (!s[0])
		return (0);
	token = malloc_guard(ft_calloc(sizeof(t_token), 1));
	if (!is_control_operator(s[0]))
		token->string = malloc_guard(ft_substr(s, 0, skip_until_char(s,
						p_control_operator[0])));
	token->control_operator = get_control_operator(p_control_operator);
	ft_lstadd_back(&data->token, malloc_guard(ft_lstnew(token)));
	return (ft_strlen(token->control_operator));
}

/*
**	Tokenizes the input
**	Each token is seperated by control operators
**	No return value
*/

void	get_token(t_data *data, char *s)
{
	int	i;
	int	token_start;

	token_start = 0;
	i = 0;
	while (s[i])
	{
		i += skip_while_char(s + i, is_whitespace);
		if (is_control_operator(s[i]) && !(count_backslash(s, i) % 2))
		{
			i += create_token(data, s + token_start, s + i);
			i += skip_while_char(s + i, is_whitespace);
			token_start = i;
			continue ;
		}
		else if (s[i] == '\"' && !(count_backslash(s, i) % 2))
			i += skip_until_next_doubleq(s + i);
		else if (s[i] == '\'' && !(count_backslash(s, i) % 2))
			i += skip_until_next_singleq(s + i);
		if (s[i])
			i++;
	}
	create_token(data, s + token_start, s + i);
}
