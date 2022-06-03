/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_skip_characters.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 11:08:17 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/03 13:27:51 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Returns location of the next double quote, doesn't skip over it
** Makes sure the double quote is not escaped by a backslash
** Assumes starting character is the opening double quote
** Returns an integer with the index of the next double quote
*/

int	skip_until_next_doubleq(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != '\"')
	{
		i++;
		if (s[i] && s[i] == '\"' && count_backslash(s, i) % 2)
			i++;
	}
	return (i);
}

int	skip_until_char_excl(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	skip_until_char_incl(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] && s[i] == c)
		i++;
	return (i);
}

int	skip_while_char(char *s, int (*ft_isthis)(char c))
{
	int		i;

	i = 0;
	while (s[i] && ft_isthis(s[i]))
		i++;
	return (i);
}

int	skip_while_not_char(char *s, int (*ft_isthis)(char c))
{
	int	i;

	i = 0;
	while (s[i] && !ft_isthis(s[i]))
		i++;
	return (i);
}
