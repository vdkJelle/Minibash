/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string_count.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:38:31 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/04/02 21:17:34 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_non_metacharacters(char *s, char control_op, int *count)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != control_op && !is_metacharacter(s[i]))
	{
		if (s[i] == '\'' && !(count_backslash(s, i) % 2))
			i += skip_until_char_incl(s + i + 1, '\'');
		else if (s[i] == '\"' && !(count_backslash(s, i) % 2))			
			i += skip_doubleq(s + i + 1);
		i++;
		if (is_metacharacter(s[i]) && count_backslash(s, i) % 2)
			i++;
		else if (is_metacharacter(s[i]))
			(*count)++;
	}
	return (i);
}

int			count_arguments(char *s, char control_op)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != control_op)
	{
		i += skip_non_metacharacters(s + i, control_op, &count);
		i += skip_whitespaces_int(s + i);
		if (s[i] && s[i] != control_op && is_metacharacter(s[i]))
			count++;
		while (s[i] && s[i] != control_op && !is_whitespace(s[i]) && is_metacharacter(s[i]))
			i++;
		i += skip_whitespaces_int(s + i);
	}
	return (count);
}

int			count_backslash(char *line, int loc)
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

// int	count_words(char const *s, char c)
// {
// 	int	i;
// 	int	wc;

// 	i = 0;
// 	wc = 0;
// 	while (s[i] == c && s[i])
// 		i++;
// 	while (s[i])
// 	{
// 		while (s[i] && s[i] != c)
// 			i++;
// 		wc++;
// 		while (s[i] && s[i] == c)
// 			i++;
// 	}
// 	return (wc);
// }