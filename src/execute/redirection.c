/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 12:06:59 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/07 19:26:35 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	An error has occured while closing the file
**	Prints error message
**	Returns 1
*/

static int	redirection_close_error(t_data *data, char *s)
{
	print_error(data, 1, make_array("🐶 > ", s, ": ", strerror(errno)));
	return (1);
}

/*
**	Checks for errors that might have occured in redirection
**	Returns 0 if opening a file was successful
**	Returns 1 if opening a file was unsuccessful
*/

static int	redirection_check_fd(t_data *data, char *s, int fd[2])
{
	if (fd[READ] == -1 || fd[WRITE] == -1)
	{
		print_error(data, 1, make_array("🐶 > ", s, ": ", strerror(errno)));
		return (1);
	}
	return (0);
}

/*
**	Reads from the input with readline until the delimiter is encountered
**	Writes the input + a newline to the file descriptor
**	If interupted by CTRL + D prints an error message and exits
**	No return value
*/

static void	here_doc_read_input(char *delimiter, int rd)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			print_error_exit(0, make_array("🐶 > warning: here-document at line",
					"1 delimited by end-of-file (wanted `", delimiter, "')"));
		if (!ft_strcmp(input, delimiter))
			exit(0);
		write(rd, input, ft_strlen(input));
		write(rd, "\n", 1);
		free(input);
	}
}

/*
**	Handles >> redirection by creating a here-document
**	A here-document contains multiline strings and can be redirected to a ...
**	... command (such as cat)
**	Opens a here-document
**	Calls here_doc_read_input to start reading input and writes said input ...
**	... to the here-document
**	If input has already been redirected the old fd of fd[READ] is closed
**	fd[READ] opens the here-document
*/

static int	here_doc(t_data *data, char *delimiter, int fd[2])
{
	int	pid;
	int	tmp_fd;

	tmp_fd = open("/tmp/here-document", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (tmp_fd == -1)
	{
		print_error(data, 1, make_array("🐶 > /tmp/here-document: ",
				strerror(errno), NULL, NULL));
		return (1);
	}
	pid = fork();
	if (pid == -1)
		print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL, NULL));
	if (pid == CHILD)
		here_doc_read_input(delimiter, tmp_fd);
	waitpid(pid, NULL, 0);
	if (close(tmp_fd) == -1)
		return (redirection_close_error(data, "/tmp/here-document"));
	if (fd[READ] != NO_REDIRECTION && close(fd[READ]) == -1)
		return (redirection_close_error(data, "/tmp/here-document"));
	fd[READ] = open("/tmp/here-document", O_RDONLY);
	return (0);
}

/*
**	Handles redirections
**	Assumes the argument after the redirection is valid
**	If input or output has already been redirected the old fd is closed
**	Returns 0 if opening a file was successful and no error occured with close
**	Returns 1 if opening a file was unsuccessful or an error occured with close
*/

int	redirection(t_data *data, t_word **arg, int i, int fd[2])
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
