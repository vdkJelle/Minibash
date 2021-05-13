/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 12:06:59 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/13 23:45:52 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	handle_redirection(t_data *data, t_word **arg, int i, int fd[2])
{
	if (!ft_strcmp(arg[i]->word, ">\0"))
	{
		if (fd[1] != -2)
		{
			if (close(fd[1]) == -1)
				return (print_errno_int());
		}
		fd[1] = open(arg[i + 1]->word, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	else if (!ft_strcmp(arg[i]->word, ">>\0"))
	{
		if (fd[1] != -2)
		{
			if (close(fd[1]) == -1)
				return (print_errno_int());
		}
		fd[1] = open(arg[i + 1]->word, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	else if (!ft_strcmp(arg[i]->word, "<\0"))
	{
		if (fd[0] != -2)
		{
			if (close(fd[0]) == -1)
				return (print_errno_int());
		}
		fd[0] = open(arg[i + 1]->word, O_RDONLY);
	}	
	if (fd[0] == -1 || fd[1] == -1)
	{
		data->exit_status = 1;
		ft_putstr_fd("🐶 > ", 2);
		ft_putstr_fd(arg[i + 1]->word, 2);
		ft_putstr_fd(": ", 2);
		return (print_errno_int());
	}
	printf("fd in = %d\n", fd[0]);
	printf("fd out = %d\n", fd[1]);
	return (0);
}

