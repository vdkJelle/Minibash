/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 16:06:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/11 10:52:02 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data)
{
	int 	fd;
	int 	i;

	fd = data->our_fd[1];
	i = 0;
	while (data->our_env[i])
	{
		ft_putstr_fd(data->our_env[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	data->exit_status = 0;
}
