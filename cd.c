/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/05 15:08:59 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changes the directory according to path using chdir
** If chdir is successful the directory is changed to the path
** Else the error is printed
** No return value
** Exit status is set in accordance to success or failure
*/

void			ft_cd(t_data *data)
{
	int		ret;
	char	*argument;

	argument = data->arg[1];
	if (!argument && data->our_fd[1] != -1) // could remove data->our_fd[1] != -1
		ret = chdir(get_env(data->our_env, "HOME"));
	else if (argument[0] == '~') // remove tilde expansion
	{
		argument = ft_strjoin((get_env(data->our_env, "HOME")), argument + 1);
		ret = chdir(argument);
		free(argument);
	}
	else
		ret = chdir(argument);
	if (ret < 0)
	{
		print_errno();
		data->exit_status = 1;
	}
	return ;
}
