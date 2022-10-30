/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_here_doc.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 15:18:13 by tessa         #+#    #+#                 */
/*   Updated: 2022/10/30 14:45:14 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Reads from the input with readline until the delimiter is encountered
**	Writes the input + a newline to the file descriptor
**	If interupted by CTRL + D prints an error message and exits
**	No return value
*/

static void	here_doc_read_input(char *delimiter, int rd)
{
	char	*input;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		input = readline("> ");
		if (!input)
			print_error_exit(0, make_array("warning: here-document at line",
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
**	Returns 0 on success
**	Returns 1 if an error occured
*/

int	here_doc(t_data *data, char *delimiter, int fd[2])
{
	int	pid;
	int	tmp_fd;

	tmp_fd = open("/tmp/here-document", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (tmp_fd == -1)
	{
		print_error(data, 1, make_array(PROMPT, "/tmp/here-document: ",
				strerror(errno), NULL));
		return (1);
	}
	pid = fork();
	if (pid == -1)
		print_error_exit(1, make_array(PROMPT, strerror(errno), NULL, NULL));
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
