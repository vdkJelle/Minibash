/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:38:31 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/25 16:16:41 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_backslash(char *line, int loc)
{
	int		i;
	int		count;

	i = loc - 1;
	if (i < 0)
		return (0);
	count = 0;
	while (line[i] == '\\')
	{
		count++;
		i--;
	}
	return (count);
}

int	count_words(char const *s, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		wc++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (wc);
}
