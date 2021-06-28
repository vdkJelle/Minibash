/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/04 16:13:17 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/18 19:08:17 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Prints the error message to STDERR using strerror(errno)
** Returns -1
*/

int		print_errno_int(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

/*
** Prints the error message to STDERR using strerror(errno)
** No return value
*/

void	print_errno(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

/*
** Prints the error message
** Prints all the strings to STDERR and sets the exit status
** No return value
*/

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
