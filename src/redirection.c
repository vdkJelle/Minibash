/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 12:06:59 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/06 14:33:24 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Checks for errors that might have occured in redirection
** Returns 0 if opening a file was successful and no error occured with close
** Returns -1 if opening a file was unsuccessful or an error occured with close
*/

static int	redirection_check_error(t_data *data, char *s, int fd[2], int close)
{
	if (fd[READ] == -1 || fd[WRITE] == -1)
	{
		print_error(data, 1, make_array("🐶 > ", s, ": ", strerror(errno)));
		return (1);
	}
	if (close == 1)
	{
		print_error(data, 1, make_array(strerror(errno), NULL, NULL, NULL));
		return (1);
	}
	return (0);
}

static int	handle_heredoc(char *delimiter, int	rd)
{
	char *input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			print_error_exit(0, make_array("🐶 > warning:  here-document at line 1 delimited by end-of-file (wanted `", delimiter, "')", NULL));
		if (!ft_strcmp(input, delimiter))
			exit(0);
		write(rd, input, ft_strlen(input));
		write(rd, "\n", 1);
		free(input);
	}
}

static int	here_doc(t_data *data, char *delimiter, int fd[2])
{
	int	pid;
	int	tmp_fd;

	tmp_fd = open("/tmp/here_doc.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (tmp_fd == -1)
	{
		print_error(data, 1, make_array("🐶 > /tmp/here_doc.txt: ", strerror(errno), NULL, NULL));
		return (1);
	}
	pid = fork();
	if (pid == -1)
		print_error_exit(1, make_array("🐶 > ", strerror(errno), NULL, NULL));
	if (pid == 0)
		handle_heredoc(delimiter, tmp_fd);
	waitpid(pid, NULL, 0);
	if (close(tmp_fd) == -1)
	{
		print_error(data, 1, make_array("🐶 > /tmp/here_doc.txt: ", strerror(errno), NULL, NULL));
		return (1);
	}
	if (fd[READ] != NO_REDIRECTION && close(fd[READ]) == -1)
		return (redirection_check_error(data, "/tmp/here_doc.txt", fd, 1));
	fd[READ] = open("/tmp/here_doc.txt", O_RDONLY);
	return (0);
}

/*
** Handles redirections, assumes the argument after the redirection is valid
** If input has already been redircected the old file descriptor is closed
** Returns 0 if opening a file was successful and no error occured with close
** Returns -1 if opening a file was unsuccessful or an error occured with close
*/

int	redirection(t_data *data, t_word **arg, int i, int fd[2])
{
	if (!ft_strcmp(arg[i]->word, ">\0"))
	{
		if (fd[WRITE] != NO_REDIRECTION && close(fd[WRITE]) == -1)
			return (redirection_check_error(data, arg[i + 1]->word, fd, 1));
		fd[WRITE] = open(arg[i + 1]->word, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	else if (!ft_strcmp(arg[i]->word, ">>\0"))
	{
		if (fd[WRITE] != NO_REDIRECTION && close(fd[WRITE]) == -1)
			return (redirection_check_error(data, arg[i + 1]->word, fd, 1));
		fd[WRITE] = open(arg[i + 1]->word, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	else if (!ft_strcmp(arg[i]->word, "<\0"))
	{
		if (fd[READ] != NO_REDIRECTION && close(fd[READ]) == -1)
			return (redirection_check_error(data, arg[i + 1]->word, fd, 1));
		fd[READ] = open(arg[i + 1]->word, O_RDONLY);
	}
	else if (!ft_strcmp(arg[i]->word, "<<\0"))
	{
		here_doc(data, arg[i + 1]->word, fd);
		return (redirection_check_error(data, "/tmp/here_doc.txt", fd, 0));
	}	
	return (redirection_check_error(data, arg[i + 1]->word, fd, 0));
}
