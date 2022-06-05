/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 10:21:10 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/05 17:32:42 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Prints arguments
** Prints spaces in between arguments
** Prints no newline if option -n is used
** No return value
*/

void	ft_echo(t_data *data)
{
	int		i;
	int		newline;

	i = 1;
	if (data->args[i] && !ft_strcmp(data->args[i], "-n"))
	{
		i++;
		newline = 0;
	}
	else
		newline = 1;
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
