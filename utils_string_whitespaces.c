/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string_whitespaces.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 12:19:07 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/02/25 14:34:54 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
	|| c == '\f')
		return (1);
	return (0);
}

void	skip_whitespaces(char **s)
{
	if (!(*s))
		return ;
	while (**s && is_whitespace(**s))
		(*s)++;
}

int		skip_whitespaces_int(char *s)
{
	int	i;

	i = 0;
	while (s[i] && is_whitespace(s[i]))
		i++;
	return (i);
}

void	skip_nonwhitespaces(char **s)
{
	if (!(*s))
		return ;
	while (**s && is_whitespace(**s))
		(*s)++;
}

int		skip_nonwhitespaces_int(char *s)
{
	int	i;

	i = 0;
	while (s[i] && !is_whitespace(s[i]))
		i++;
	return (i);
}
