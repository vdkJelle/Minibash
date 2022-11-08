/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/08 12:20:15 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_cd_home(t_data *data)
{
	int		ret;
	char	*home;

	ret = 0;
	home = get_env(data->our_env, "HOME");
	if (!home)
	{
		return (print_error(data, 1,
				make_array("codyshell: cd: HOME not set", NULL, NULL, NULL)));
	}
	ret = chdir(home);
	if (ret == -1)
		return (print_error(data, 1,
				make_array("codyshell: cd: ",
					data->args[1], ": ", strerror(errno))));
	data->exit_status = 0;
}

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
		return (handle_cd_home(data));
	ret = chdir(data->args[1]);
	if (ret == -1)
		return (print_error(data, 1,
				make_array("codyshell: cd: ",
					data->args[1], ": ", strerror(errno))));
	data->exit_status = 0;
}
