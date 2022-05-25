/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_multis_command.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 12:12:20 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/13 12:18:28 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Counts the amount of double and single quotes
** Returns 0 if there is an even amount of double or single quotes
** Returns 1 if there is an uneven amount of double or single quotes
*/

static int	count_quotes(char *s)
{
	int		i;
	int		len;

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
** Checks for multiline commands
** Returns 1 if there is an uneven amount of quotes
** Returns 1 if there is an uneven amount of backslashes at the end
** Returns 1 if there is a pipe at the end
** Returns 0 if there are no multiline commands
*/

int			check_multiline_command(t_data *data, char *s)
{
	int		len;

	len = ft_strlen(s);
	if (count_backslash(s, len) % 2)
	{
		data->exit_status = 1;
		ft_putstr_fd("Multiline command\n", 2);
		return (1);
	}
	if (count_quotes(s))
	{
		data->exit_status = 1;
		ft_putstr_fd("Multiline command\n", 2);
		return (1);
	}
	while (len > 0 && is_whitespace(s[len - 1]))
		len--;
	if (len > 0 && s[len - 1] == '|')
	{
		data->exit_status = 1;
		ft_putstr_fd("Multiline command\n", 2);
		return (1);
	}
	return (0);
}
