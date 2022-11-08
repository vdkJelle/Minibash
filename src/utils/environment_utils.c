/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 12:17:17 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/08 14:55:05 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Adds the correct shell level to the array of environmental variables
**	If SHLVL is not set the value it is set to 1
**	If SHLVL is set but the value is not numeric the value is set to 1
**	If SHLVL is set correctly the value is incremented
**	Calls append_key_value to add the SHLVL to the array of env variables
**	No return value
*/

static void	handle_shlvl(char ***our_env, int *env_size)
{
	char	*shlvl;
	char	*temp;
	int		i;
	int		n;

	shlvl = get_env(*our_env, "SHLVL");
	if (!shlvl)
		temp = malloc_guard(ft_strdup("SHLVL=1"));
	else
	{
		i = skip_while_not_char(shlvl, ft_isdigit_char);
		if (!shlvl[i])
			temp = malloc_guard(ft_strdup("SHLVL=1"));
		else
		{
			n = ft_atoi(shlvl) + 1;
			temp = malloc_guard(ft_strjoin_wrapper(malloc_guard(ft_strdup
							("SHLVL=")), malloc_guard(ft_itoa(n)), 3));
		}
	}
	append_key_value(temp, our_env, env_size);
	free(temp);
}

/*
** Always sets the PWD environment variable to the current working directory, 
** regardless of whether it exists upon creation or not.
** Always sets the OLDPWD environment variable to have an empty value, regardless
** of whether it exists upon creation or not.
** No return value.
*/

static void	handle_pwd_and_oldpwd(char ***our_env, int *env_size)
{
	int		i;
	char	*pwd;

	pwd = NULL;
	pwd = malloc_guard(getcwd(pwd, 0));
	pwd = malloc_guard(ft_strjoin_wrapper(malloc_guard(
					ft_strdup("PWD=")), pwd, 3));
	append_key_value(pwd, our_env, env_size);
	free(pwd);
	i = 0;
	while ((*our_env)[i])
	{
		if (!ft_strncmp((*our_env)[i], "OLDPWD=", 7))
		{
			free((*our_env)[i]);
			(*our_env)[i] = malloc_guard(ft_strdup("OLDPWD"));
			return ;
		}
		i++;
	}
	append_key_value("OLDPWD", our_env, env_size);
}

/*
** Determines the environ size without empty values as they are not to be
** copied over.
** returns the size of the environment to be created.
*/

static int	determine_environ_size(char	**environ)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (environ[i])
	{
		if (ft_strchr(environ[i], '='))
			ret++;
		i++;
	}
	return (ret);
}

/*
**	Copies the environmental variables of the shell environment
**	Uses an external char **environ
**	Calls handle_shlvl to set the correct value of the key SHLVL
**	No return value
*/

void	initialize_env(char ***our_env, int *env_size)
{
	extern char	**environ;
	int			i;
	int			j;

	i = determine_environ_size(environ);
	*our_env = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	j = 0;
	while (environ[j])
	{
		if (ft_strchr(environ[j], '='))
		{
			(*our_env)[i] = malloc_guard(ft_strdup(environ[j]));
			i++;
		}
		j++;
	}
	(*our_env)[i] = NULL;
	(*env_size) = i;
	handle_pwd_and_oldpwd(our_env, env_size);
	handle_shlvl(our_env, env_size);
}
