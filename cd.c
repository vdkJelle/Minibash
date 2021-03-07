/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/03 13:23:41 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *path, char **our_env)
{
	int		i;
	int		ret;

	i = 0;
	while (path[i] == ' ')
		i++;
	if (path[i] == '\0')
		ret = chdir(get_env(our_env, "HOME"));
	else
		ret = chdir(path + i);
	if (ret < 0)
		printf("%s\n", strerror(errno));
	return ;
}
