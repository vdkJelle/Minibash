/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_wrapper.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 18:44:20 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/06/01 14:25:04 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*malloc_guard(void *ret)
{
	if (ret == NULL)
		print_error_exit(1, make_array(strerror(errno), NULL, NULL, NULL));
	return (ret);
}

void	*ft_malloc(size_t size)
{
	return (malloc_guard(malloc(size)));
}
