/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/14 15:01:20 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/11/09 18:07:21 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Calls the builtin function based on the command
**	No return value
*/

static void	execute_builtin(t_data *data, enum e_command cmd, t_execute *exec)
{
	t_builtin	builtin[7];

	builtin[CD] = ft_cd;
	builtin[ECHO] = ft_echo;
	builtin[ENV] = ft_env;
	builtin[EXIT] = ft_exit;
	builtin[EXPORT] = ft_export;
	builtin[PWD] = ft_pwd;
	builtin[UNSET] = ft_unset;
	data->args = exec->args;
	builtin[cmd](data);
}

/*
**	Executes the builtin command when there is no pipe
**	If there is no redirection the 
**		- fd read is set to STDIN_FILENO
**		- fd write is set to STDOUT_FILENO
**	If there is a redirection the fds are set to the fd in the exec struct
**	Calls execute_builtin
**	Closes the fd after execute_builtin in case of a redirection
**	No return value
*/

void	execute_builtin_no_pipe(t_data *data, enum e_command cmd,
	t_execute *exec)
{
	if (exec->fd[READ] == NO_REDIRECTION)
		data->our_fd[READ] = STDIN_FILENO;
	else
		data->our_fd[READ] = exec->fd[READ];
	if (exec->fd[WRITE] == NO_REDIRECTION)
		data->our_fd[WRITE] = STDOUT_FILENO;
	else
		data->our_fd[WRITE] = exec->fd[WRITE];
	if (cmd == EXIT)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	execute_builtin(data, cmd, exec);
	if (exec->fd[READ] != NO_REDIRECTION && close(exec->fd[READ]) == -1)
		return (print_error(1, make_array(SHELL, strerror(errno), NULL,
					NULL)));
	if (exec->fd[WRITE] != NO_REDIRECTION && close(exec->fd[WRITE]) == -1)
		return (print_error(1, make_array(SHELL, strerror(errno), NULL,
					NULL)));
}

/*
**	Executes the builtin command in case of a pipe
**	The fd read is set to STDIN_FILENO and the fd write is set to STDOUT_FILENO
**	Calls execute_builtin
**	The call to exit is necessary to exit the child process
**	No return value
*/

void	execute_builtin_pipe(t_data *data, enum e_command cmd, t_execute *exec)
{
	data->our_fd[READ] = STDIN_FILENO;
	data->our_fd[WRITE] = STDOUT_FILENO;
	execute_builtin(data, cmd, exec);
	exit(g_status_code);
}
