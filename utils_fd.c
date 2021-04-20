/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_fd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 14:18:04 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/03/29 14:47:57 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_set_to_stdout(int *fd)
{
	int		i;
	int		n;
	
	if (*fd != STDOUT)
		n = *fd - 2;
	else
		n = 0;
	i = 0;
	while (i < n)
	{
		close(*fd);
		(*fd)--;
		i++;
	}
	*fd = STDOUT;
}

void	close_fd(int fd)
{
	int		i;
	int		n;
	
	if (fd != STDOUT)
		n = fd - 2;
	else
		n = 0;
	i = 0;
	while (i < n)
	{
		close(fd);
		fd--;
		i++;
	}
}

void	open_failed(char *filename)
{
	ft_putstr_fd("🐶 > ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	exit(1);
}
