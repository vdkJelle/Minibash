/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_count.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:38:31 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/09 12:37:20 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Skips until the end of the word
**	Increments the count if a metacharacter is encountered
**	Returns the index of the end of the word
*/

static int	skip_non_metacharacters(char *s, char control_operator, int *count)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != control_operator && !is_metacharacter(s[i]))
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
**	Counts the amount of arguments
**	Arguments are words that are seperated by metacharacters
**	First calls skip_non_metacharacters to get to the end of the word
**	Saves metacharacters as a word to if they are not a whitespace...
**	... to check if they are valid later in check_expression
**	Returns an integer with the amount or arguments it counted
*/

int	count_arguments(char *s, char control_op)
{
	int	i;
	int	count;

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
**	Counts the amount of backslashes before the pointer
**	Returns an integer with the amount of backslashes it counted
*/

int	count_backslash(char *s, int loc)
{
	int	i;
	int	count;

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
