/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:41:16 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/04 18:09:44 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_data data)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(data.curdir, 0);
	// free(buf);
	if (!buf)
	{
		printf("A whoopsie doopsie happened\n");
		exit (0);
	}
	printf("%s\n", buf);
	free(buf);
	return ;
}
