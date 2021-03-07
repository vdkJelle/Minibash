/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/03 13:24:46 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changes the directory according to path using chdir
** If chdir is successful the directory is changed to the path
** Else the error is printed
** No return value
*/

void	ft_cd(t_data data)
{
	int		ret;
	char	*argument;

	argument = ((t_token*)data.token->content)->arg[0];
	if (!argument)
		ret = chdir(get_env(data.our_env, "HOME"));
	else
		ret = chdir(argument);
	if (ret < 0)
		printf("%s\n", strerror(errno));
	return ;
}
