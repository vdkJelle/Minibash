/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 10:21:10 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/04/20 15:10:12 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_data *data)
{
	int		newline;
	int		i;
	int		fd;
	char	**arguments;

	// arguments = ((t_token*)data->token->content)->arg;
	arguments = data->arg;	
	fd = data->our_fd[1];
	i = 1;
	if (arguments[i] && !ft_strcmp(arguments[i], "-n"))
	{
		i++;
		newline = 0;
	}
	else
		newline = 1;
	while (arguments[i])
	{
		ft_putstr_fd(arguments[i], fd);
		if (arguments[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (newline == 1)
		write(fd, "\n", 1);
	data->exit_status = 0;
}
