/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 10:24:32 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/20 13:12:06 by jelvan-d      ########   odam.nl         */
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

void		execute(t_data *data)
{
	char	*path;
	char	**args;
	int		ret;
	pid_t	pid;
	pid_t	wpid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		path = get_path_to_executable(*data);
		args = get_args(((t_token*)data->token->content)->arg, ((t_token*)data->token->content)->cmd);
		ret = execve(path, args, data->our_env);
		if (ret < 0)
		{
			printf("%s\n", strerror(errno));
			exit(1);
		}
	}
	if (pid < 0)
		printf("%s\n", strerror(errno));
	else
		wpid = waitpid(pid, &data->exit_status, WUNTRACED);
	if (wpid == -1)
		exit(-1);
}
