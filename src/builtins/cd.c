/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/07 14:20:16 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Changes the directory according to the path using chdir
**	If no arguments are provided path is set to the home directory
**	If chdir is successful the directory is changed to the path
**	If chdir is unsuccessful or if there is more than one argument
**		- the directory remains unchanged
**		- an error message is printed
**	No return value
*/

void	ft_cd(t_data *data)
{
	int	ret;

	ret = 0;
	if (!data->args[1])
		ret = chdir(get_env(data->our_env, "HOME")); //NEED TO CHECK IF UNSET HOME WHAT MAC DO
	else if (!data->args[2])
		ret = chdir(data->args[1]);
	else if (data->args[2])
		return (print_error(data, 1,
				make_array("🐶 > cd: too many arguments", NULL, NULL, NULL)));
	if (ret == -1)
		return (print_error(data, 1,
				make_array("🐶 > cd: ", data->args[1], ": ", strerror(errno))));
	data->exit_status = 0;
}
