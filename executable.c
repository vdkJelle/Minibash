/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 10:24:32 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/04/20 15:08:43 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			execute_builtin(t_data *data, builtin cmd, char **args)
{
	f_builtin	builtin[7];

	builtin[0] = ft_cd;
    builtin[1] = ft_echo;
    builtin[2] = ft_env;
    builtin[3] = ft_exit;
    builtin[4] = ft_export;
    builtin[5] = ft_pwd;
    builtin[6] = ft_unset;
	data->arg = args;
	builtin[cmd](data);
}

static char		*get_path_to_executable(char *arg)
{
	char	*ret;
	
	if (!ft_strncmp(arg, "./", 2) || !ft_strncmp(arg, "/", 1) || !ft_strncmp(arg, "..", 2))
		ret = ft_strdup(arg);
	else
		ret = ft_strjoin("/bin/", arg);
	if (!ret)
		exit(1);
	return (ret);
}

void			execute_nonbuiltin(t_data *data, char **args)
{
	char	*path;
	int		ret;

	if (!args[0])
		return ;
	path = get_path_to_executable(args[0]);
	if (!path)
		exit(1);
	ret = execve(path, args, data->our_env);
	if (ret < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 1);
		exit(1);
	}
	free(path);
}

static builtin	identify_command(char *s)
{
	builtin	cmd;

	if (!ft_strcmp(s, "cd") || !ft_strcmp(s, "/bin/cd") || !ft_strcmp(s, "/usr/bin/cd"))
		cmd = CD;
	else if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "/bin/echo") || !ft_strcmp(s, "/usr/bin/echo"))
		cmd = ECHO;
	else if (!ft_strcmp(s, "env") || !ft_strcmp(s, "/bin/env") || !ft_strcmp(s, "/usr/bin/env"))
		cmd = ENV;
	else if (!ft_strcmp(s, "exit") || !ft_strcmp(s, "/bin/exit") || !ft_strcmp(s, "/usr/bin/exit"))
		cmd = EXIT;
	else if (!ft_strcmp(s, "export") || !ft_strcmp(s, "/bin/export") || !ft_strcmp(s, "/usr/bin/export"))
		cmd = EXPORT;
	else if (!ft_strcmp(s, "pwd") || !ft_strcmp(s, "/bin/pwd") || !ft_strcmp(s, "/usr/bin/pwd"))
		cmd = PWD;
	else if (!ft_strcmp(s, "unset") || !ft_strcmp(s, "/bin/unset") || !ft_strcmp(s, "/usr/bin/unset"))
		cmd = UNSET;
	else
		cmd = NON_BUILTIN;
	return (cmd);
}

//ft_exit no longer works because we are exiting from the child
void			execute(t_data *data, t_token *current)
{
	char	**args;
	builtin	cmd;
	pid_t	pid;
	pid_t	wpid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); //siginterupt, sigdefault
		args = final_arg(data, current);
		if (!args)
			exit(1);
		if (!args[0])
			exit(0);
		cmd = identify_command(args[0]);
		if (cmd == NON_BUILTIN && !check_command(data, args[0]))
			execute_nonbuiltin(data, args);
		else if (cmd != NON_BUILTIN)
			execute_builtin(data, cmd, args);
		free_array(args);
	}
	else
		wpid = waitpid(pid, &data->exit_status, WUNTRACED);
	if (wpid == -1)
		exit(-1);
}

// void		execute(t_data data)
// {
// 	char	*path;
// 	char	**args;
// 	int		ret;
// 	pid_t	pid;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		path = get_path_to_executable(data);
// 		args = data.arg;
// 		ret = execve(path, args, data.our_env);
// 		if (ret < 0)
// 		{
// 			printf("%s\n", strerror(errno));
// 			exit(1);
// 		}
// 	}
// 	if (pid < 0)
// 		printf("%s\n", strerror(errno));
// 	else
// 		wait(NULL);
// }