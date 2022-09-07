/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 12:06:59 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/13 15:35:48 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Checks for errors that might have occured in redirection
**	Returns 0 if opening a file was successful
**	Returns 1 if opening a file was unsuccessful
*/

int	redirection_check_fd(t_data *data, char *s, int fd[2])
{
	if (fd[READ] == -1 || fd[WRITE] == -1)
	{
		print_error(data, 1, make_array("🐶 > ", s, ": ", strerror(errno)));
		return (1);
	}
	return (0);
}

/*
**	An error has occured while closing the file
**	Prints error message
**	Returns 1
*/

int	redirection_close_error(t_data *data, char *s)
{
	print_error(data, 1, make_array("🐶 > ", s, ": ", strerror(errno)));
	return (1);
}

/*
**	Handles a redirection
**	If input or output has already been redirected the old fd is closed
**	Returns 0 if opening a file was successful and no error occured with close
**	Returns 1 if opening a file was unsuccessful or an error occured with close
*/

static int	handle_redirection(t_data *data, t_word **arg, int i, int fd[2])
{
	if (!ft_strcmp(arg[i]->word, ">\0"))
	{
		if (fd[WRITE] != NO_REDIRECTION && close(fd[WRITE]) == -1)
			return (redirection_close_error(data, arg[i + 1]->word));
		fd[WRITE] = open(arg[i + 1]->word, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	else if (!ft_strcmp(arg[i]->word, ">>\0"))
	{
		if (fd[WRITE] != NO_REDIRECTION && close(fd[WRITE]) == -1)
			return (redirection_close_error(data, arg[i + 1]->word));
		fd[WRITE] = open(arg[i + 1]->word, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	else if (!ft_strcmp(arg[i]->word, "<\0"))
	{
		if (fd[READ] != NO_REDIRECTION && close(fd[READ]) == -1)
			return (redirection_close_error(data, arg[i + 1]->word));
		fd[READ] = open(arg[i + 1]->word, O_RDONLY);
	}
	else if (!ft_strcmp(arg[i]->word, "<<\0"))
	{
		if (here_doc(data, arg[i + 1]->word, fd))
			return (1);
		return (redirection_check_fd(data, "/tmp/here-document", fd));
	}	
	return (redirection_check_fd(data, arg[i + 1]->word, fd));
}

/*
**	Handles redirections
**	Assumes the argument after the redirection is valid
**	Returns 0 on success
**	Returns 1 if an error occured while handling a redirection
*/

int	handle_redirections(t_data *data, t_expression *expression, t_execute *exec)
{
	int	i;

	i = 0;
	while (expression->arg && expression->arg[i])
	{
		if (expression->arg[i]->metacharacter
			&& is_redirection(expression->arg[i]->word))
		{
			if (handle_redirection(data, expression->arg, i, exec->fd))
				return (1);
			i++;
		}
		i++;
	}
	return (0);
}
