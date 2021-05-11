/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/11 10:32:31 by tevan-de      ########   odam.nl         */
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
	char	**args;

	args = data->args;
	if (!args[1])
		ret = chdir(get_env(data->our_env, "HOME"));
	else if (args[1] && args[2] == NULL)
		ret = chdir(args[1]);
	else if (args[1] && args[2] != NULL)
	{
		ft_putstr_fd("🐶 > cd: too many arguments\n", 2);
		data->exit_status = 1;
		return ;
	}
	if (ret < 0)
	{
		print_errno();
		data->exit_status = 1;
		return ;
	}
	data->exit_status = 0;
}
