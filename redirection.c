/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 12:06:59 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/14 17:01:14 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks for errors that might have occured in redirection
** Returns 0 if opening a file was successful and no error occured with close
** Returns -1 if opening a file was unsuccessful or an error occured with close
*/
static int	redirection_check_error(t_data *data, char *s, int fd[2], int close)
{
	// printf("fd in = %d\n", fd[READ]);
	// printf("fd out = %d\n", fd[WRITE]);
	if (fd[READ] == -1 || fd[WRITE] == -1)
	{
		print_error(data, 1, 4, "🐶 > ", s, ": ", strerror(errno));
		return (-1);
	}
	if (close == -1)
	{
		print_error(data, 1, 1, strerror(errno));
		return (-1);
	}
	return (0);
}

/*
** Handles redirections, assumes the argument after the redirection is valid
** If input has already been redircected the old file descriptor is closed
** Returns 0 if opening a file was successful and no error occured with close
** Returns -1 if opening a file was unsuccessful or an error occured with close
** If chdir is successful the directory is changed to the path
*/
int			redirection(t_data *data, t_word **arg, int i, int fd[2])
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
	return (redirection_check_error(data, arg[i + 1]->word, fd, 0));
}
