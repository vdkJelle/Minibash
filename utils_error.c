/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/04 16:13:17 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/13 21:28:06 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdarg.h>

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

void	print_error(t_data *data, int exit_status, int n, ...)
{
	char	*s;
	int		i;
	va_list	strings;

	va_start(strings, n);
	i = 0;
	while (i < n)
	{
		s = va_arg(strings, char *);
		ft_putstr_fd(s, 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	data->exit_status = exit_status;
	va_end(strings);
}

// void	print_error_message(t_data *data, int exit_status, char *s1, char *s2)
// {
// 	ft_putstr_fd("🐶 > ", 2);
// 	if (s1)
// 		ft_putstr_fd(s1, 2);
// 	if (s2)
// 		ft_putstr_fd(s2, 2);
// 	data->exit_status = exit_status;
// }