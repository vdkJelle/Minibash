/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:46:52 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/03/09 15:55:31 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *content)
{
	int i;

	i = 0;
	free(((t_token*)content)->cmd);
	while (((t_token*)content)->arg[i])
	{
		free(((t_token*)content)->arg[i]);
		i++;
	}
	free(((t_token*)content)->arg);
	free(content);
}

void	print_token(void *content)
{
	int i;

	i = 0;
	printf("cmd = |%s|\n", ((t_token*)content)->cmd);
	while (((t_token*)content)->arg[i])
	{
		printf("arg = |%s|\n", ((t_token*)content)->arg[i]);
		i++;
	}
}
