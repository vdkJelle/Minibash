/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 10:24:32 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/10/19 15:54:30 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Gets the path to the executable based on file status
**	Returns a malloced string to the path of the executable
*/

static char	*get_path(t_data *data, char *arg, enum e_file file)
{
	char	*ret;

	ret = NULL;
	if (file == BIN)
		ret = get_path_from_bin(data, arg);
	else
	{
		if (arg[0] == '.' || arg[0] == '/')
			ret = malloc_guard(ft_strdup(arg));
		else
			ret = malloc_guard(ft_strjoin("./", arg));
	}
	return (ret);
}

/*
**	Look up table for builtin command
**	Returns an enum with the type of command
*/

static enum e_command	identify_command(char *s)
{
	int					i;
	static const char	*builtins[7] = {
	[CD] = "cd",
	[ECHO] = "echo",
	[ENV] = "env",
	[EXIT] = "exit",
	[EXPORT] = "export",
	[PWD] = "pwd",
	[UNSET] = "unset"
	};

	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(s, builtins[i]))
			return (i);
		i++;
	}
	return (NON_BUILTIN);
}

/*
**	Executes a command
**	If something went wrong with redirections or if there are no arguments ...
**	... create process is called with CMD_ERROR and will exit the child ...
**	... process immediately after starting, no command will be executed
**	Calls identify_command to check if the command is a builtin
**	If command is not a builtin
**		- the file status is checked with check_file
**		- the path to the executable is obtained with get_path
**		- calls create process
**	If command is a builtin
**		- calls execute_builtin_no_pipe if there is no pipe
**		- calls create process if there is a pipe
**	No return value
*/

static void	execute(t_data *data, t_execute *cur, t_execute *prev)
{
	enum e_command	cmd;
	enum e_file		file;

	if (!cur->args || !cur->args[0])
		return (create_process(data, CMD_ERROR, cur, prev));
	cmd = identify_command(cur->args[0]);
	if (cmd == NON_BUILTIN)
	{
		file = check_file_information(data, cur->args[0]);
		if (file == FILE_ERROR)
			data->exit_status = 1;
		if (file != BIN && file != REGULAR)
			cmd = CMD_ERROR;
		cur->path = get_path(data, cur->args[0], file);
		create_process(data, cmd, cur, prev);
	}
	else if (cmd != NON_BUILTIN && (cur->piped == 1 || (prev
				&& prev->piped == 1)))
		create_process(data, cmd, cur, prev);
	else
		execute_builtin_no_pipe(data, cmd, cur);
}

/*
**	Initializes the execute struct
**	Sets the initial value of the file descriptors to no redirection
**	Calls handle_redirections to handle redirections, if an error occurs no ...
**	... arguments will be set
**	Calls get_final_args to create the final array
**	Creates a pipe if the control operator is a pipe
**	Returns a malloced execute struct
*/

static t_execute	*get_exec(t_data *data, t_expression *expression)
{
	t_execute	*exec;

	exec = malloc_guard(ft_calloc(sizeof(t_execute), 1));
	exec->fd[READ] = NO_REDIRECTION;
	exec->fd[WRITE] = NO_REDIRECTION;
	if (!handle_redirections(data, expression, exec))
		get_final_args(expression, exec);
	if (expression->control_operator[0] == '|')
	{
		if (pipe(exec->p_fd) == -1)
			print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL,
					NULL));
		exec->piped = 1;
	}
	return (exec);
}

/*
**	Iterates over the linked list with tokens, parses them and executes them
**	Saves a pointer to the previous t_execute struct to use in case of a pipe
**	No return value
*/

void	cody_catch(t_data *data)
{
	t_list			*temp;
	t_expression	*expression;
	t_execute		*cur;
	t_execute		*prev;
	int				wstatus;

	prev = NULL;
	temp = data->token;
	while (temp)
	{
		expression = parse_one(data, (t_token *)temp->content);
		cur = get_exec(data, expression);
		free_expression(expression);
		execute(data, cur, prev);
		if (prev)
			free_exec(prev);
		prev = cur;
		temp = temp->next;
		if (!temp)
			free_exec(cur);
	}
	waitpid(data->pid, &wstatus, 0);
	while (wait(NULL) > 0) {
		continue ;
	}
	if (WIFEXITED(wstatus))
		data->exit_status = WEXITSTATUS(wstatus);
	else if (WTERMSIG(wstatus) == SIGQUIT)
	{
		data->exit_status = 128 + WTERMSIG(wstatus);
		write(1, "\b\b  \b\b^\\Quit\n", 13);
	}
	else if (WTERMSIG(wstatus) == SIGINT)
		data->exit_status = 128 + WTERMSIG(wstatus);
}
