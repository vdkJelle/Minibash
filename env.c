/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 16:06:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/10 16:07:29 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data)
{
	int i;

	i = 0;
	while (data->our_env[i])
	{
		printf("%s\n", data->our_env[i]);
		i++;
	}
}
