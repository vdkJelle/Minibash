/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/04 19:11:25 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *path)
{
	char	*buf;
	int		i;

	i = 2;
	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
		exit (0);
	while (path[i] == ' ')
		i++;
	i = chdir(path + i);
	if (i < 0)
		printf("Path does not exist\n");
	free(buf);
	return ;
}
