/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_multiline_command.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 19:57:51 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/11/08 15:57:32 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Counts the amount of double and single quotes
**	Returns 0 if there is an even amount of quotes
**	Returns 1 if there is an uneven amount quotes
*/

static int	count_quotes(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (s[i])
	{
		if (s[i] == '\"' && !(count_backslash(s, i) % 2))
		{
			i += skip_until_next_doubleq(s + i);
			if (i >= len)
				return (1);
		}
		else if (s[i] == '\'' && !(count_backslash(s, i) % 2))
		{
			i += skip_until_next_singleq(s + i);
			if (i >= len)
				return (1);
		}
		i++;
	}
	return (0);
}

/*
**	Checks for multiline commands
**	Returns 1 if there is an uneven amount of quotes
**	Returns 1 if there is an uneven amount of backslashes at the end
**	Returns 0 if there are no multiline commands
*/

int	check_multiline_command(t_data *data, char *s)
{
	int	len;

	len = ft_strlen(s);
	if (count_backslash(s, len) % 2)
	{
		print_error(data, 2, make_array(SHELL, "Multiline command", NULL,
				NULL));
		return (1);
	}
	if (count_quotes(s))
	{
		print_error(data, 2, make_array(SHELL, "Multiline command", NULL,
				NULL));
		return (1);
	}
	return (0);
}
