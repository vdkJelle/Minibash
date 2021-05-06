/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/04 16:13:17 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/04 17:05:01 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_errno_int(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

void	print_errno(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}
