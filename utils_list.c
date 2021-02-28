/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:46:52 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/02/28 12:19:40 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *content)
{
	free(((t_token*)content)->cmd);
	free(((t_token*)content)->arg);
	free(content);
}

void	print_token(void *content)
{
	printf("cmd = |%s|\n", ((t_token*)content)->cmd);
	printf("arg = |%s|\n", ((t_token*)content)->arg);
}
