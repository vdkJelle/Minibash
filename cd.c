/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/04/01 17:22:34 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changes the directory according to path using chdir
** If chdir is successful the directory is changed to the path
** Else the error is printed
** No return value
*/

void	ft_cd(t_data *data)
{
	int		ret;
	char	*argument;

	// argument = ((t_token*)data->token->content)->arg[0];
	argument = data->arg[1];
	if (!argument && data->our_fd[1] != -1) 
		ret = chdir(get_env(data->our_env, "HOME"));
	else
		ret = chdir(argument);
	if (ret < 0)
	{	// printf("%s\n", strerror(errno));
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
	}
	return ;
}
