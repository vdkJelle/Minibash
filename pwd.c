/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:41:16 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/13 21:25:45 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints the working directory using getcwd
** If getcwd is successful the working directory is printed
** If getcwd is unsuccessful the error is printed
** No return value
*/
void	ft_pwd(t_data *data)
{
	char	*buf;
	int		fd;

	buf = NULL;
	buf = getcwd(buf, 0);
	fd = data->our_fd[1];
	if (!buf)
	{
		print_error(data, 1, 1, strerror(errno));
		return ;
	}
	ft_putstr_fd(buf, fd);
	ft_putchar_fd('\n', fd);	
	free(buf);
	data->exit_status = 0;
}
