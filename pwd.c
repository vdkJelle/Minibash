/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:41:16 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/03 13:33:14 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints the working directory using getcwd
** If successful the working directory is printed
** Else the error is printed
** No return value
*/

void	ft_pwd(t_data data)
{
	char	*buf;

	(void)data;
	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
	{
		printf("%s\n", strerror(errno));
		return ;
	}
	printf("%s\n", buf);
	free(buf);
	return ;
}
