/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/03/22 12:01:32 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Changes the directory according to the path using chdir
** If no arguments are provided path is set to the home directory
** If chdir is successful the directory is changed to the path
** If chdir is unsuccessful
**		the directory is unchanged
**		the error is printed
** If there is more than one argument the error is printed and the directory is
**		not changed
** No return value
*/

void			ft_cd(t_data *data)
{
	char	**args;
	int		ret;

	args = data->args;
	ret = 0;
	if (!args[1])
		ret = chdir(get_env(data->our_env, "HOME"));
	else if (args[1] && args[2] == NULL)
		ret = chdir(args[1]);
	else if (args[1] && args[2] != NULL)
	{
		print_error(data, 1, 1, "🐶 > cd: too many arguments");
		return ;
	}
	if (ret < 0)
	{
		print_error(data, 2, 4, "🐶 > cd: ", args[1], ": ", strerror(errno));
		return ;
	}
	data->exit_status = 0;
}
