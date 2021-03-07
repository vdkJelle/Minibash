/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string_whitespaces.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 12:19:07 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/03/07 19:57:47 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_invalid(char *s)
{
	if (!s)
		return (0);
	if (ft_strncmp("||", s, 2), ft_strncmp("&&", s, 2), ft_strncmp(";;", s, 2))
		return (1);
	if (s[0] && (s[0] == '&' || s[0] == '(' || s[0] == ')'))
		return (1);
	return (0);
}

// other metacharacters are & ( )
int		is_metacharacter(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

// tokens are seperated by spaces and tabs
int		is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
	// || c == '\r' || c == '\n' || c == '\v' || c == '\f')
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
