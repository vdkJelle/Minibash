/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string_skip.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 11:08:17 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/03/30 20:53:16 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		skip_doubleq(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '\"')
	{
		i++;
		if (line[i] && count_backslash(line, i) % 2 == 1)
			i++;
	}
	if (line[i] && line[i] == '\"')
		i++;
	return (i);
}

int		skip_until_char_incl(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] && s[i] == c)
		i++;
	return (i);
}

int		skip_until_char_excl(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int		skip_whitespaces_int(char *s)
{
	int		i;

	i = 0;
	while (s[i] && is_whitespace(s[i]))
		i++;
	return (i);
}

int		skip_until_metacharacter_excl(char *s)
{
	int		i;

	i = 0;
	while (s[i] && !is_metacharacter(s[i]))
		i++;
	return (i);
}

int		skip_until_char_function(char *s, int (*ft_isthis)(char c))
{
	int		i;

	i = 0;
	while (s[i] && !ft_isthis(s[i]))
		i++;
	return (i);
}

// int		skip_until_metacharacter_incl(char *s)
// {
// 	int		i;

// 	i = 0;
// 	while (s[i] && !is_metacharacter(s[i]))
// 		i++;
// 	if (s[i] && is_metacharacter(s[i]))
// 		i++;
// 	return (i);
// }

// void	skip_char(char **s, char c)
// {
// 	if (!(*s))
// 		return ;
// 	if (**s && **s == c)
// 		(*s)++;
// }

// void	skip_chars(char **s, char c)
// {
// 	if (!(*s))
// 		return ;
// 	while (**s && **s == c)
// 		(*s)++;
// }

// int		skip_chars_int(char *s, char c)
// {
// 	int		i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i] && s[i] == c)
// 		i++;
// 	return (i);
// }

// void	skip_whitespaces(char **s)
// {
// 	if (!(*s))
// 		return ;
// 	while (**s && is_whitespace(**s))
// 		(*s)++;
// }

// void	skip_nonwhitespaces(char **s)
// {
// 	if (!(*s))
// 		return ;
// 	while (**s && is_whitespace(**s))
// 		(*s)++;
// }

// int		skip_nonwhitespaces_int(char *s)
// {
// 	int		i;

// 	i = 0;
// 	while (s[i] && !is_whitespace(s[i]))
// 		i++;
// 	return (i);
// }
