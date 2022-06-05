/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/06/05 17:46:44 by tessa         ########   odam.nl         */
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

void	ft_cd(t_data *data)
{
	int		ret;

	ret = 0;
	if (!data->args[1])
		ret = chdir(get_env(data->our_env, "HOME"));
	else if (!data->args[2])
		ret = chdir(data->args[1]);
	else if (data->args[2])
		return (print_error(data, 1,
			make_array("🐶 > cd: too many arguments", NULL, NULL, NULL)));
	if (ret == -1)
		return (print_error(data, 2,
			make_array("🐶 > cd: ", data->args[1], ": ", strerror(errno))));
	data->exit_status = 0;
}
