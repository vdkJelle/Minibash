/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 16:30:26 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/03/03 16:58:36 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_array(char **array)
{
	int		i;
	int		size;

	size = 0;
	while (array[size])
		size++;
	i = 0;
	while (i <= size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_exit(t_data data)
{
	free_array(data.our_env);
	free(data.input);
	ft_lstclear(&data.token, free_token);
	exit(0);
}
