/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_skip_characters.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 11:08:17 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/06 18:19:44 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Finds the location of the next double quote, doesn't skip over it
** Makes sure the double quote is not escaped
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

/*
** Skips over the string until it finds the character c for the first time
** Returns an integer with the index of the character c
*/

int	skip_until_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

/*
** Skips over the string while the character belongs to a set of characters
** Returns an integer with the index where the character no longer matches the set of characters
*/

int	skip_while_char(char *s, int (*ft_isthis)(char c))
{
	int	i;

	i = 0;
	while (s[i] && ft_isthis(s[i]))
		i++;
	return (i);
}

/*
** Skips over the string while the character does not belong to a set of characters
** Returns an integer with the index where the character matches the set of characters
*/

int	skip_while_not_char(char *s, int (*ft_isthis)(char c))
{
	int	i;

	i = 0;
	while (s[i] && !ft_isthis(s[i]))
		i++;
	return (i);
}
