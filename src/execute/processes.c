/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 12:28:46 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/11/09 18:42:59 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Waits for all processes to end, if they ended by signal, alters exit status
** No return value
*/

void	waiting_for_processes(t_data *data)
{
	int	wstatus;

	wstatus = -2;
	waitpid(data->pid, &wstatus, 0);
	while (wait(NULL) > 0)
		continue ;
	if (WIFEXITED(wstatus))
		g_status_code = WEXITSTATUS(wstatus);
	else if (WTERMSIG(wstatus) == SIGQUIT)
	{
		g_status_code = 128 + WTERMSIG(wstatus);
		write(1, "\b\b  \b\b^\\Quit: 3\n", 16);
	}
	else if (WTERMSIG(wstatus) == SIGINT)
	{
		g_status_code = 128 + WTERMSIG(wstatus);
		write(1, "\n", 1);
	}
}

/*
**	Handles pipes
**	If the current command is a pipe the fd of the write end of the current ...
**	... pipe is duplicated into STDOUT_FILENO
**	If the previous command is a pipe the fd of the read end of the previous ...
**	pipe is duplicated into STDIN_FILENO
**	No return value
*/

static void	child_pipes(t_execute *cur, t_execute *prev)
{
	if (cur->piped == 1)
	{
		if (dup2(cur->p_fd[WRITE], STDOUT_FILENO) == -1)
			print_error_exit(1, make_array(SHELL, strerror(errno), NULL,
					NULL));
		close(cur->p_fd[WRITE]);
	}
	if (prev && prev->piped == 1)
	{
		if (dup2(prev->p_fd[READ], STDIN_FILENO) == -1)
			print_error_exit(1, make_array(SHELL, strerror(errno), NULL,
					NULL));
		close(prev->p_fd[READ]);
	}
	if (cur->p_fd[READ] != 0)
		close(cur->p_fd[READ]);
}

/*
**	Executes the command
**	If the command is a non-builtin execve is called
**	If the command is a builtin execute_builtin_pipe is called
**	If the command is redirected the
**		- fd read is duplicated into STDIN_FILENO
**		- fd write is duplicated into STDOUT_FILENO
**	If there is a pipe and a redirection the redirection takes precedent
**		- dup2 automatically closes the piped fd
**		- dup2 duplicates the fd of the redirection
**	No return value
*/

static void	child_process(t_data *data, enum e_command cmd, t_execute *cur,
	t_execute *prev)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_pipes(cur, prev);
	if (cur->fd[READ] != NO_REDIRECTION)
	{
		if (dup2(cur->fd[READ], STDIN_FILENO) == -1)
			print_error_exit(1, make_array(SHELL, strerror(errno), NULL,
					NULL));
	}
	if (cur->fd[WRITE] != NO_REDIRECTION)
	{
		if (dup2(cur->fd[WRITE], STDOUT_FILENO) == -1)
			print_error_exit(1, make_array(SHELL, strerror(errno), NULL,
					NULL));
	}
	if (cmd != NON_BUILTIN)
		execute_builtin_pipe(data, cmd, cur);
	else if (execve(cur->path, cur->args, data->our_env) == -1)
		print_error_exit(1, make_array(SHELL, cur->path, ": ",
				strerror(errno)));
}

/*
**	If the current command is a pipe the fd of the write end of the current ...
**	... pipe is closed
**	If the previous command is a pipe the fd of the read end of the previous ...
**	... pipe is closed
**	If the command is redirected the file descriptors are closed
**	No return value
*/

static void	parent_process(t_data *data, pid_t pid, t_execute *cur,
	t_execute *prev)
{
	signal(SIGINT, SIG_IGN);
	if (cur->piped == 1 && close(cur->p_fd[WRITE]) == -1)
		print_error_exit(1, make_array(SHELL, strerror(errno), NULL, NULL));
	if (prev && prev->piped == 1 && close(prev->p_fd[READ]) == -1)
		print_error_exit(1, make_array(SHELL, strerror(errno), NULL, NULL));
	if (cur->fd[READ] != NO_REDIRECTION && cur->fd[READ] != -1
		&& close(cur->fd[READ]) == -1)
		print_error_exit(1, make_array(SHELL, strerror(errno), NULL, NULL));
	if (cur->fd[WRITE] != NO_REDIRECTION && cur->fd[WRITE] != -1
		&& close(cur->fd[WRITE]) == -1)
		print_error_exit(1, make_array(SHELL, strerror(errno), NULL, NULL));
	(void)data;
	(void)pid;
}

/*
** 	Uses fork to create a child process in which the command is executed
** 	Used when command is a non builtin or when there is a pipe
**	Exit is immediately called in the child process in case of a CMD_ERROR
**	No return value
*/

void	create_process(t_data *data, enum e_command cmd, t_execute *cur,
	t_execute *prev)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error_exit(1, make_array(SHELL, "fork: ", strerror(errno), NULL));
	else if (pid == CHILD)
	{
		if (cmd == CMD_ERROR)
			exit(g_status_code);
		child_process(data, cmd, cur, prev);
	}
	else
	{
		parent_process(data, pid, cur, prev);
		data->pid = pid;
	}
}
