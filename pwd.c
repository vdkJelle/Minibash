/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:41:16 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/17 11:07:16 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*buf;

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
