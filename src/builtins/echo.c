/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 10:21:10 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/11/03 17:30:30 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	skip_while_n(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] == 'n')
	{
		i++;
	}
	return (i);
}

/*
**	Prints all arguments with spaces in between
**	Prints no newline if option -n is used
**	No return value
*/

void	ft_echo(t_data *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (data->args[i] && !ft_strncmp(data->args[i], "-n", 2))
	{
		if (ft_strlen(data->args[i]) != skip_while_n(data->args[i]))
			break ;
		newline = 0;
		i++;
	}
	while (data->args[i])
	{
		ft_putstr_fd(data->args[i], data->our_fd[WRITE]);
		if (data->args[i + 1])
			ft_putchar_fd(' ', data->our_fd[WRITE]);
		i++;
	}
	if (newline == 1)
		ft_putchar_fd('\n', data->our_fd[WRITE]);
	data->exit_status = 0;
}
