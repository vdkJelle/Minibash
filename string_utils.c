/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:38:31 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/04 18:39:45 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
