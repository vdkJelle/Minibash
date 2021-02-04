/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/04 18:51:48 by jelvan-d      ########   odam.nl         */
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
	printf("%s\n", path + i);
	i = chdir(path + i);
	if (i < 0)
		exit (0);
	free(buf);
	return ;
}
