/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:46:52 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/04/28 15:06:03 by tevan-de      ########   odam.nl         */
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
	printf("cmd = %s\n", ((t_token*)content)->cmd);
	while (((t_token*)content)->arg[i])
	{
		printf("arg = %s\n", ((t_token*)content)->arg[i]);
		i++;
	}
	if (!ft_strcmp(((t_token*)content)->cop, "\0"))
		printf("cop = null terminator\n");
	else if (!ft_strcmp(((t_token*)content)->cop, ";\0"))
		printf("cop = semi column\n");
	else if (!ft_strcmp(((t_token*)content)->cop, "|\0"))
		printf("cop = pipe\n");
	else
		printf("illegal cop = %s\n", ((t_token*)content)->cop);
}
