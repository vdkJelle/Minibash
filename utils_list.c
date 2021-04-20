/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:46:52 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/03/23 21:45:52 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *content)
{
	int		i;

	i = 0;
	free(((t_token*)content)->cmd);
	while (((t_token*)content)->arg[i])
	{
		free(((t_token*)content)->arg[i]);
		i++;
	}
	free(((t_token*)content)->arg);
	free(((t_token*)content)->cop);
	free(content);
}

void	print_token(void *content)
{
	int		i;

	i = 0;
	printf("cmd = |%s|\n", ((t_token*)content)->cmd);
	while (((t_token*)content)->arg[i])
	{
		printf("arg = |%s|\n", ((t_token*)content)->arg[i]);
		i++;
	}
	printf("cop = |%s|\n", ((t_token*)content)->cop);
}
