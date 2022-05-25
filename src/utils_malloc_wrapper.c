/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_malloc_wrapper.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 18:44:20 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/05/24 18:50:14 by jelvan-d      ########   odam.nl         */
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
