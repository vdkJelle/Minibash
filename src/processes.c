/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 12:28:46 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/03 13:55:50 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Handles pipes
** If the current command is a pipe the
**		fd of the write end of the current pipe is duplicated into STDOUT_FILENO
** If the previous command is a pipe the
**		fd of the read end of the previous pipe is duplicated into STDIN_FILENO
** No return value
*/

static void	child_pipes(t_execute *cur, t_execute *prev)
{
	if (cur->piped == 1)
	{
		if (dup2(cur->p_fd[WRITE], STDOUT_FILENO) == -1)
			print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL, NULL));
	}
	if (prev && prev->piped == 1)
	{
		if (dup2(prev->p_fd[READ], STDIN_FILENO) == -1)
			print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL, NULL));
	}
}

/*
** Executes the command
** If the command is a non-builtin execve is called
** If the command is a builtin execute_builtin_pipe is called
** If the command is redirected the
**		fd read is duplicated into STDIN_FILENO
**		fd write is duplicated into STDOUT_FILENO
** If there is a pipe and a redirection the redirection takes precedent
**		dup2 closes the STDIN_FILENO/STDOUT_FILENO of the piped fd
**		the fd of the redirection is duplicated into STDIN_FILENO/STDOUT_FILENO
** No return value
*/

static void	child_process
(t_data *data, e_command cmd, t_execute *cur, t_execute *prev)
{
	signal(SIGINT, SIG_DFL);
	child_pipes(cur, prev);
	if (cur->fd[READ] != NO_REDIRECTION)
	{
		if (dup2(cur->fd[READ], STDIN_FILENO) == -1)
			print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL, NULL));
	}
	if (cur->fd[WRITE] != NO_REDIRECTION)
	{
		if (dup2(cur->fd[WRITE], STDOUT_FILENO) == -1)
			print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL, NULL));
	}
	if (cmd != NON_BUILTIN)
		execute_builtin_pipe(data, cmd, cur);
	else if (execve(cur->path, cur->args, data->our_env) == -1)
		print_error_exit(1, make_array("🐶 > ", cur->path, ": ", strerror(errno)));
}

/*
** Waits for the child process to change state
** The child process can be terminated
**		normally (calling exit or returning from main())
**		by a signal
** If the current command is a pipe the
**		fd of the write end of the current pipe is closed
** If the previous command is a pipe the
**		fd of the read end of the previous pipe is closed
** If the command is redirected the file descriptors are closed
** No return value
*/

static void	parent_process
(t_data *data, pid_t pid, t_execute *cur, t_execute *prev)
{
	int		wstatus;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		data->exit_status = WEXITSTATUS(wstatus);
	else if (WTERMSIG(wstatus) == SIGQUIT)
	{
		data->exit_status = 128 + WTERMSIG(wstatus);
		write(1, "\b\b  \b\b^\\Quit\n", 13);
	}
	else if (WTERMSIG(wstatus) == SIGINT)
		data->exit_status = 128 + WTERMSIG(wstatus);
	if (cur->piped == 1 && close(cur->p_fd[WRITE]) == -1)
		print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL, NULL));
	if (prev && prev->piped == 1 && close(prev->p_fd[READ]) == -1)
		print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL, NULL));
	if (cur->fd[READ] != NO_REDIRECTION && cur->fd[READ] != -1 && close(cur->fd[READ]) == -1)
		print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL, NULL));
	if (cur->fd[WRITE] != NO_REDIRECTION && cur->fd[WRITE] != -1 && close(cur->fd[WRITE]) == -1)
		print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL, NULL));
}

/*
** Uses fork to create a child process in which the command is executed
** Used when command is a non builtin or when there is a pipe
** If there is an error (file has no permissions) or the command is empty exit is called
** No return value
*/

void	create_process
(t_data *data, e_command cmd, t_execute *cur, t_execute *prev)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL, NULL));
	else if (pid == CHILD)
	{
		if (cmd == CMD_ERROR)
			exit(data->exit_status);
		child_process(data, cmd, cur, prev);
	}
	else
		parent_process(data, pid, cur, prev);
}
