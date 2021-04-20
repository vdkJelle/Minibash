/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 16:06:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/29 14:26:13 by tevan-de      ########   odam.nl         */
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
		// printf("%s\n", data->our_env[i]);
		ft_putstr_fd(data->our_env[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
}
