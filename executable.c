/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 10:24:32 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/03 16:23:22 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **get_args(char **arguments, char *cmd)
{
	char	**arg;
	int		i;
	int		size;

	size = 0;
	while (arguments[size])
		size++;
	arg = malloc(sizeof(char*) * (size + 2));
	arg[0] = ft_strdup(cmd);
	i = 0;
	while (i < size)
	{
		arg[i + 1] = ft_strdup(arguments[i]);
		i++;
	}
	arg[i + 1] = NULL;
	return (arg);
}

static char	*get_path_to_executable(t_data data)
{
	char	*temp;

	temp = ((t_token*)data.token->content)->cmd;
	if (!ft_strncmp(temp, "./", 2) || !ft_strncmp(temp, "/", 1) || !ft_strncmp(temp, "..", 2))
		return (temp);
	else
		return (ft_strjoin("/bin/", temp));
}

void		execute(t_data data)
{
	char	*path;
	char	**args;
	int		ret;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		path = get_path_to_executable(data);
		args = get_args(((t_token*)data.token->content)->arg, ((t_token*)data.token->content)->cmd);
		ret = execve(path, args, data.our_env);
		if (ret < 0)
		{
			printf("%s\n", strerror(errno));
			exit(1);
		}
		free(path);
	}
	if (pid < 0)
		printf("%s\n", strerror(errno));
	else
		wait(NULL);
}
