/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 10:24:32 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/14 18:43:40 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		child_process(t_data *data, e_command cmd, t_execute *cur, t_execute *prev)
{
	signal(SIGINT, SIG_DFL);
	if (cur->piped == 1)
	{
		dup2(cur->p_fd[WRITE], STDOUT_FILENO);
		close(cur->p_fd[READ]);
	}
	if (prev && prev->piped == 1)
	{
		dup2(prev->p_fd[READ], STDIN_FILENO);
		close(prev->p_fd[WRITE]);
	}
	if (cur->fd[READ] != NO_REDIRECTION)
		dup2(cur->fd[READ], STDIN_FILENO);
	if (cur->fd[WRITE] != NO_REDIRECTION)
		dup2(cur->fd[WRITE], STDOUT_FILENO);
	if (cmd != NON_BUILTIN)
		execute_builtin_pipe(data, cmd, cur);
	else if (execve(cur->path, cur->args, data->our_env) == -1)
	{
		print_error(data, 1, 4, "🐶 > ", cur->path, ": ", strerror(errno));
		exit(1);
	}
}

static void		parent_process(t_data *data, pid_t pid)
{
	int		wstatus;
	pid_t	wpid;

	wpid = waitpid(pid, &wstatus, WUNTRACED);
	data->exit_status = WEXITSTATUS(wstatus);
	if (wpid == -1)
		print_error(data, 1, 1, strerror(errno));
}

static void		create_process(t_data *data, e_command cmd, t_execute *cur, t_execute *prev)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (print_error(data, 1, 1, strerror(errno)));
	else if (pid == CHILD)
		child_process(data, cmd, cur, prev);
	else
		parent_process(data, pid);
	if (cur->piped == 1 && close(cur->p_fd[WRITE]) == -1)
		return (print_error(data, 1, 1, strerror(errno)));
	if (prev && prev->piped == 1 && close(prev->p_fd[READ]) == -1)
		return (print_error(data, 1, 1, strerror(errno)));
	if (cur->fd[READ] != NO_REDIRECTION && close(cur->fd[READ]) == -1)
		return (print_error(data, 1, 1, strerror(errno)));
	if (cur->fd[WRITE] != NO_REDIRECTION && close(cur->fd[WRITE]) == -1)
		return (print_error(data, 1, 1, strerror(errno)));
}

static char		*get_path(char *arg, e_path path)
{
	char	*ret;
	
	if (path == BIN)
		ret = ft_strjoin("/bin/", arg);
	else if (path == USR_BIN)
		ret = ft_strjoin("/usr/bin/", arg);
	else
	{
		if (arg[0] == '.' || arg[0] == '/')
			ret = ft_strdup(arg);
		else
			ret = ft_strjoin("./", arg);
	}
	if (!ret)
		exit(1);
	return (ret);
}

static e_command	identify_command(char *s)
{
	e_command	cmd;

	if (!ft_strcmp(s, "cd"))
		cmd = CD;
	else if (!ft_strcmp(s, "echo"))
		cmd = ECHO;
	else if (!ft_strcmp(s, "env"))
		cmd = ENV;
	else if (!ft_strcmp(s, "exit"))
		cmd = EXIT;
	else if (!ft_strcmp(s, "export"))
		cmd = EXPORT;
	else if (!ft_strcmp(s, "pwd"))
		cmd = PWD;
	else if (!ft_strcmp(s, "unset"))
		cmd = UNSET;
	else
		cmd = NON_BUILTIN;
	return (cmd);
}

int			execute(t_data *data, t_execute *cur, t_execute *prev)
{
	e_command	cmd;
	e_path		path;

	cmd = identify_command(cur->args[0]);
	if (cmd == NON_BUILTIN)
	{
		path = check_path(data, cur->args[0]);
		if (path == DIRECTORY || path == NOT_FOUND || path == NO_FILE)
			return (1);
		cur->path = get_path(cur->args[0], path);
		if (!cur->path)
			exit(1);
		create_process(data, cmd, cur, prev);
	}
	else if (cmd != NON_BUILTIN && (cur->piped == 1 || (prev && prev->piped == 1)))
		create_process(data, cmd, cur, prev);
	else
		execute_builtin_no_pipe(data, cmd, cur);
	return (0);
}

// int			execute(t_data *data, t_execute *cur, t_execute *prev)
// {
// 	e_command	cmd;
// 	e_path		path;

// 	cmd = identify_command(cur->args[0]);
// 	if (cmd == NON_BUILTIN)
// 	{
// 		path = check_path(data, cur->args[0]);
// 		if (path == DIRECTORY || path == NOT_FOUND || path == NO_FILE)
// 			return (1);
// 		cur->path = get_path(cur->args[0], path);
// 		if (!cur->path)
// 			exit(1);
// 		execute_nonbuiltin(data, cur, prev);
// 		free(cur->path);
// 	}
// 	else
// 		execute_builtin(data, cmd, cur);
// 	return (0);
// }

// void			execute(t_data *data, t_token *cur, t_token *prev)
// {
// 	builtin		cmd;
// 	t_execute	exec;

// 	ft_bzero(&exec, sizeof(exec));
// 	exec->fd[0] = -2;
// 	exec->fd[1] = -2;
// 	if (cur->cop[0] == '|' || (prev && prev->cop[0] == '|'))
// 	{
// 		if (pipe(exec->p_fd) == -1)
// 		{
// 			data->exit_status = 1;
// 			return (print_errno());
// 		}
// 		printf("read = %d\twrite = %d\n", exec->p_fd[0], exec->p_fd[1]);
// 		exec->piped = 1;
// 	}
// 	final_args(data, cur, &exec);
// 	if (!exec->args)
// 		return ;
// 	cmd = identify_command(exec->args[0]);
// 	if (cmd == NON_BUILTIN)
// 		execute_nonbuiltin(data, exec);
// 	else
// 		execute_builtin(data, cmd, exec);
// 	free_array(exec->args);
// }

// void			execute(t_data *data, t_token *current)
// {
// 	char	**args;
// 	builtin	cmd;
// 	pid_t	pid;
// 	pid_t	wpid;

// 	pid = fork();
// 	if (pid < 0)
// 		return ;
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL); //siginterupt, sigdefault
// 		args = final_arg(data, current);
// 		if (!args)
// 			exit(1);
// 		if (!args[0])
// 			exit(0);
// 		cmd = identify_command(args[0]);
// 		if (cmd == NON_BUILTIN && !check_command(data, args[0]))
// 			execute_nonbuiltin(data, args);
// 		else if (cmd != NON_BUILTIN)
// 			execute_builtin(data, cmd, args);
// 		free_array(args);
// 	}
// 	else
// 		wpid = waitpid(pid, &data->exit_status, WUNTRACED);
// 	if (wpid == -1)
// 		exit(-1);
// }

// void			execute_nonbuiltin(t_data *data, char **args)
// {
// 	char	*path;
// 	int		ret;

// 	if (!args[0])
// 		return ;
// 	path = get_path_to_executable(args[0]);
// 	if (!path)
// 		exit(1);
// 	ret = execve(path, args, data->our_env);
// 	if (ret < 0)
// 	{
// 		ft_putstr_fd(strerror(errno), 2);
// 		ft_putchar_fd('\n', 1);
// 		exit(1);
// 	}
// 	free(path);
// }

// static void		parent_process()

// void			execute_nonbuiltin(t_data *data, t_execute exec)
// {
// 	char	*path;
// 	command	cmd;
// 	// int		ret;
// 	pid_t	pid;
// 	pid_t	wpid;

// 	cmd = check_command(data, exec->args[0]);
// 	if (cmd == DIRECTORY || cmd == NOT_FOUND)
// 		return ;
// 	path = get_path_to_executable(exec->args[0], cmd);
// 	if (!path)
// 		exit(1);
// 	wpid = 0;
// 	pid = fork();
// 	if (pid < 0)
// 		return (print_errno());
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL); //siginterupt, sigdefault
// 		if (exec->fd[0] == -2)
// 			dup(STDIN_FILENO);
// 		else
// 			dup2(exec->fd[0], STDIN_FILENO);
// 		if (exec->fd[1] == -2)
// 			dup(STDOUT_FILENO);
// 		else
// 			dup2(exec->fd[1], STDOUT_FILENO);
// 		// ret = execve(path, exec->args, data->our_env);
// 		// if (ret < 0)
// 		if (execve(path, exec->args, data->our_env) == -1)
// 		{
// 			ft_putstr_fd("🐶 > ", 2);
// 			ft_putstr_fd(path, 2);
// 			ft_putstr_fd(": ", 2);
// 			print_errno();
// 			exit(1);
// 		}
// 	}
// 	else
// 		wpid = waitpid(pid, &data->exit_status, WUNTRACED);
// 	if (wpid == -1)
// 		exit(1);
// 	free(path);
// 	close_fd(data, exec->fd);
// }

// void			execute_nonbuiltin(t_data *data, t_execute *cur, t_execute *prev)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		return (print_errno());
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		if (cur->piped == 1)
// 		{
// 			dup2(cur->p_fd[WRITE], STDOUT_FILENO);
// 			close(cur->p_fd[READ]);
// 		}
// 		if (prev && prev->piped == 1)
// 		{
// 			dup2(prev->p_fd[READ], STDIN_FILENO);
// 			close(prev->p_fd[WRITE]);
// 		}
// 		if (cur->fd[0] != -2)
// 		{
// 			dup2(cur->fd[READ], STDIN_FILENO);
// 		}
// 		if (cur->fd[1] != -2)
// 		{
// 			dup2(cur->fd[WRITE], STDOUT_FILENO);
// 		}
// 		if (execve(cur->path, cur->args, data->our_env) == -1)
// 		{
// 			print_error(data, 1, 4, "🐶 > ", cur->path, ": ", strerror(errno));
// 			exit(1);
// 		}
// 	}
// 	else
// 		parent_process(data, pid, cur, prev);
// }