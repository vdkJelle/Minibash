/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:41:16 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/09 17:38:13 by jelvan-d      ########   odam.nl         */
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
	buf = malloc_guard(getcwd(buf, 0));
	ft_putstr_fd(buf, data->our_fd[WRITE]);
	ft_putchar_fd('\n', data->our_fd[WRITE]);
	free(buf);
	g_status_code = 0;
}
