/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string_count.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:38:31 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/05/24 12:34:19 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Skips until the end of the word
** Increments the count
** Returns the index of the end of the word
*/

static int	skip_non_metacharacters(char *s, char control_op, int *count)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != control_op && !is_metacharacter(s[i]))
	{
		if (s[i] == '\'' && !(count_backslash(s, i) % 2))
			i += skip_until_next_singleq(s + i);
		else if (s[i] == '\"' && !(count_backslash(s, i) % 2))			
			i += skip_until_next_doubleq(s + i);
		i++;
		if (is_metacharacter(s[i]) && count_backslash(s, i) % 2)
			i++;
		else if (is_metacharacter(s[i]))
			(*count)++;
	}
	return (i);
}

/*
** Counts the amount of arguments
** Arguments are words that are seperated by metacharacters
** First calls skip_non_metacharacters to get to the end of the word
** Saves metacharacters as a word to if they are not a whitespace
**		to check if they are valid later in check_token
** Returns an integer with the count
*/

int			count_arguments(char *s, char control_op)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != control_op)
	{
		i += skip_non_metacharacters(s + i, control_op, &count);
		i += skip_while_char(s + i, is_whitespace);
		if (s[i] && s[i] != control_op && is_metacharacter(s[i]))
			count++;
		while (s[i] && s[i] != control_op && !is_whitespace(s[i])
		&& is_metacharacter(s[i]))
			i++;
		i += skip_while_char(s + i, is_whitespace);
	}
	return (count);
}

/*
** Counts the amount of backslashes before the pointer
** Returns an integer with the count
*/

int			count_backslash(char *s, int loc)
{
	int		i;
	int		count;

	i = loc - 1;
	if (i < 0)
		return (0);
	count = 0;
	while (i >= 0 && s[i] == '\\')
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