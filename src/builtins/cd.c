/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 18:22:56 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/08 15:24:21 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_oldpwd_and_pwd(t_data *data, char *oldpwd)
{
	char	*pwd;
	int		i;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (print_error(data, 1,
				make_array("codyshell: cd: ",
					data->args[1], ": ", strerror(errno))));
	i = 0;
	while (data->our_env[i])
	{
		if ((!ft_strcmp("OLDPWD", data->our_env[i])
				|| !ft_strncmp("OLDPWD=", data->our_env[i], 7)))
			append_key_value(oldpwd, &data->our_env, &data->env_size);
		else if ((!ft_strcmp("PWD", data->our_env[i])
				|| !ft_strncmp("PWD=", data->our_env[i], 4)))
			append_key_value(pwd, &data->our_env, &data->env_size);
		i++;
	}
	free(pwd);
	data->exit_status = 0;
}

static void	handle_cd_home(t_data *data)
{
	int		ret;
	char	*home;
	char	*tmp_old_pwd;

	ret = 0;
	tmp_old_pwd = NULL;
	tmp_old_pwd = malloc_guard(getcwd(tmp_old_pwd, 0));
	home = get_env(data->our_env, "HOME");
	if (!home)
		return (print_error(data, 1,
				make_array("codyshell: cd: HOME not set", NULL, NULL, NULL)));
	ret = chdir(home);
	if (ret == -1)
		return (print_error(data, 1,
				make_array("codyshell: cd: ",
					data->args[1], ": ", strerror(errno))));
	update_oldpwd_and_pwd(data, tmp_old_pwd);
	free(tmp_old_pwd);
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
	int		ret;
	char	*tmp_old_pwd;

	if (!data->args[1])
		return (handle_cd_home(data));
	ret = 0;
	tmp_old_pwd = NULL;
	tmp_old_pwd = malloc_guard(getcwd(tmp_old_pwd, 0));
	ret = chdir(data->args[1]);
	if (ret == -1)
		return (print_error(data, 1,
				make_array("codyshell: cd: ",
					data->args[1], ": ", strerror(errno))));
	update_oldpwd_and_pwd(data, tmp_old_pwd);
	free(tmp_old_pwd);
}
