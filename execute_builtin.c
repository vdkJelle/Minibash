/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/14 15:01:20 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/14 19:54:12 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin_no_pipe(t_data *data, e_command cmd, t_execute *exec)
{
	f_builtin	builtin[7];

	builtin[0] = ft_cd;
	builtin[1] = ft_echo;
	builtin[2] = ft_env;
	builtin[3] = ft_exit;
	builtin[4] = ft_export;
	builtin[5] = ft_pwd;
	builtin[6] = ft_unset;
	data->args = exec->args;
	if (exec->fd[READ] == NO_REDIRECTION)
		data->our_fd[READ] = STDIN_FILENO;
	else
		data->our_fd[READ] = exec->fd[READ];
	if (exec->fd[WRITE] == NO_REDIRECTION)
		data->our_fd[WRITE] = STDOUT_FILENO;
	else
		data->our_fd[WRITE] = exec->fd[WRITE];
	builtin[cmd](data);
	if (exec->fd[READ] != NO_REDIRECTION && close(exec->fd[READ]) == -1)
		return (print_errno());
	if (exec->fd[WRITE] != NO_REDIRECTION && close(exec->fd[WRITE]) == -1)
		return (print_errno());
}
 
void	execute_builtin_pipe(t_data *data, e_command cmd, t_execute *exec)
{
	f_builtin	builtin[7];

	builtin[0] = ft_cd;
	builtin[1] = ft_echo;
	builtin[2] = ft_env;
	builtin[3] = ft_exit;
	builtin[4] = ft_export;
	builtin[5] = ft_pwd;
	builtin[6] = ft_unset;
	data->args = exec->args;
	data->our_fd[READ] = STDIN_FILENO;
	data->our_fd[WRITE] = STDOUT_FILENO;
	builtin[cmd](data);
	exit(data->exit_status);
}
