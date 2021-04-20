/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:41:16 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/04/01 14:00:37 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints the working directory using getcwd
** If successful the working directory is printed
** Else the error is printed
** No return value
*/

/*add exit status*/
void	ft_pwd(t_data *data)
{
	char	*buf;
	int		fd;

	buf = NULL;
	buf = getcwd(buf, 0);
	fd = data->our_fd[1];
	if (!buf)
	{
		// printf("%s\n", strerror(errno));
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
	// printf("%s\n", buf);
	ft_putstr_fd(buf, fd);
	ft_putchar_fd('\n', fd);	
	free(buf);
	return ;
}
