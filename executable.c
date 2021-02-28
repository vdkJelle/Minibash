/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 10:24:32 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/28 12:26:02 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** T
** Should include what happens if fork goes wrong, so add else if pid < 0
** I think execve doesn't return anything? So I think we can remove i = execve and the 4 lines after that
*/

void	execute(char *path)
{
	int		i;
	char	*execname;
	char	**env;
	char	**args;
	pid_t	pid;

	i = 0;
	env = NULL;
	pid = fork();
	if (pid == 0)
	{
		while (path[i] != ' ' && path[i])
			i++;
		execname = malloc(sizeof(char) * i + 1);
		ft_strlcpy(execname, path, i + 1);
		args = ft_split(path, ' ');
		i = execve(execname, args, env);
		// if (i < 0)
		// {
		// 	printf("no such file or directory\n");
		// 	exit(0);
		// }
		free(execname);
	}
	else
		wait(NULL);
	return ;
}
