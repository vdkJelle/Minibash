/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_skip_characters.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 11:08:17 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/01 14:24:51 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Returns location of the next double quote, doesn't skip over it
** Makes sure the double quote is not escaped
** Assumes starting character is a double quote
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

/*
** Returns location of the next single quote, doesn't skip over it
** Assumes starting character is a single quote
*/

int	skip_until_next_singleq(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != '\'')
		i++;
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
