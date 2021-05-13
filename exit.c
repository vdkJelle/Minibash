/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 16:30:26 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/13 16:04:17 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data)
{
	free_array(data->our_env);
	free(data->input);
	ft_lstclear(&data->token, free_token);
	exit(0);
}
