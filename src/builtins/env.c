/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 16:06:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/09 17:37:57 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Prints all environmetal variables with a newline in between
**	No return value
*/

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->our_env[i])
	{
		if (strchr(data->our_env[i], '='))
		{
			ft_putstr_fd(data->our_env[i], data->our_fd[WRITE]);
			ft_putchar_fd('\n', data->our_fd[WRITE]);
		}
		i++;
	}
	g_status_code = 0;
}
