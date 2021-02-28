/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 10:24:32 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/28 12:51:41 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *path, t_data data)
{
	int		i;
	char	*execname;
	char	**args;
	pid_t	pid;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (path[i] != ' ' && path[i])
			i++;
		execname = malloc(sizeof(char) * i + 1);
		ft_strlcpy(execname, path, i + 1);
		args = ft_split(path, ' ');
		i = execve(execname, args, data.our_env);
		if (i < 0)
		{
			printf("%s\n", strerror(errno));
			exit(1);
		}
		free(execname);
	}
	else
		wait(NULL);
	return ;
}
