/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 10:24:32 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/08 15:43:21 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (i < 0)
		{
			printf("no such file or directory\n");
			exit (0);
		}
		free(execname);
	}
	else
		wait(NULL);
	return ;
}
