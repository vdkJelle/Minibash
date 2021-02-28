/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 11:23:24 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/02/28 12:27:08 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_double_quotes(char *line)
{
	int		i;

	i = 1;
	while (line[i] && line[i] != '\"')
	{
		i++;
		if (line[i] && line[i] == '\"' && count_backslash(line, i) % 2 != 0)
			i++;
	}
	return (i);
}

static int	count_single_quotes(char *line)
{
	int		i;

	i = 1;
	while (line[i] && line[i] != '\'')
		i++;
	return (i);
}

int			count_quotes(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && count_backslash(line, i) % 2 == 0)
		{
			i += count_single_quotes(line + i);
			if (i >= (int)ft_strlen(line))
				return (-1);
		}
		else if (line[i] == '\"' && count_backslash(line, i) % 2 == 0)
		{
			i += count_double_quotes(line + i);
			if (i >= (int)ft_strlen(line))
				return (-1);
		}
		i++;
	}
	return (0);
}
