/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:41:16 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/20 13:12:07 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints the working directory using getcwd
** If successful the working directory is printed
** Else the error is printed
** No return value
*/

void	ft_pwd(t_data *data)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		printf("%s\n", strerror(errno));
		data->exit_status = 1;
		return ;
	}
	printf("%s\n", buf);
	free(buf);
	return ;
}
