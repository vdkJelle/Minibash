/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:41:16 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/06/07 15:40:12 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Prints the working directory using getcwd
**	If getcwd is successful the working directory is printed
**	If getcwd is unsuccessful an error message is printed
**	No return value
*/

void	ft_pwd(t_data *data)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
	{
		print_error(data, 1, make_array("🐶 > ", strerror(errno), NULL, NULL));
		return ;
	}
	ft_putstr_fd(buf, data->our_fd[WRITE]);
	ft_putchar_fd('\n', data->our_fd[WRITE]);
	free(buf);
	data->exit_status = 0;
}
