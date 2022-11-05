/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 11:55:58 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/05 12:27:24 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Prints all environmental variables with newlines in between
**	Prints declare -x before every environmental variable
**	Places double quotes around the value
**	Prints baskslashes of the value double
**	No return value
*/

static void	print_export(char *our_env, int our_fd)
{
	int	i;

	ft_putstr_fd("declare -x ", 1);
	i = 0;
	while (our_env[i])
	{
		ft_putchar_fd(our_env[i], our_fd);
		i++;
		if (our_env[i] == '=')
		{
			ft_putstr_fd("=\"", our_fd);
			i++;
			while (our_env[i])
			{
				if (our_env[i] == '\\')
					ft_putchar_fd('\\', our_fd);
				ft_putchar_fd(our_env[i], our_fd);
				i++;
			}
			ft_putchar_fd('"', our_fd);
		}
	}
	ft_putchar_fd('\n', our_fd);
}

/*
** Checks if the environmental variable already exists
** If the environmental variable already exists the value is replaced
** If the environmental variable already exists, but the new argument has no
**		value, nothing is changed
** Returns 0 if the variable is new
** Returns 1 if the variable already existed
*/

static int	check_if_exists(char *arg, char ***our_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*our_env)[i])
	{
		j = 0;
		while ((*our_env)[i][j] && (*our_env)[i][j] != '=')
			j++;
		if (!ft_strncmp((*our_env)[i], arg, skip_until_char(arg, '=')))
		{
			if (ft_strchr(arg, '='))
			{
				free((*our_env)[i]);
				(*our_env)[i] = NULL;
				(*our_env)[i] = malloc_guard(ft_strdup(arg));
			}
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** Adds a variable to the array of environmental variables
** If the variable key already exists it is chanegd in place
** If the variable key is new the value is appended to the array
** No return value
*/

void	append_key_value(char *arg, char ***our_env, int *env_size)
{
	char	**tmp;
	int		i;

	if (check_if_exists(arg, our_env))
		return ;
	i = 0;
	tmp = ft_malloc(sizeof(char *) * ((*env_size) + 2));
	if (!tmp)
		exit(1);
	while ((*our_env)[i])
	{
		tmp[i] = malloc_guard(ft_strdup((*our_env)[i]));
		i++;
	}
	tmp[i] = malloc_guard(ft_strdup(arg));
	tmp[i + 1] = NULL;
	(*env_size)++;
	free_array(*our_env);
	(*our_env) = tmp;
}

/*
** Check if the identifier is valid
** An argument is invalid if 
**		the first character is not a letter or '_'
** 		the following characters up to the '=' are not alphanumerical or '_'
** Returns 0 if the argument is valid
** Returns 1 if the argument is invalid
*/
static int	check_if_valid(t_data *data, char *s)
{
	int		i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
	{
		print_error(data, 1, make_array("🐶 > export: `", s,
				"': not a valid identifier", NULL));
		return (1);
	}
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			print_error(data, 1, make_array("🐶 > export: `", s,
					"': not a valid identifier", NULL));
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** Adds or prints environmental variables
** If no arguments are provided all environmental variables are printed
** If arguments are provided and identifiers are valid arguments are appended
** No return value
*/

void	ft_export(t_data *data)
{
	int	i;
	char	**sorted_env;

	data->exit_status = 0;
	i = 0;
	if (!data->args[1])
	{
		sorted_env = bubble_sort(data->our_env, &data->env_size);
		while (sorted_env[i])
		{
			print_export(sorted_env[i], data->our_fd[1]);
			i++;
		}
		free_array(sorted_env);
	}
	i = 1;
	while (data->args[i])
	{
		if (!check_if_valid(data, data->args[i]))
			append_key_value(data->args[i], &data->our_env, &data->env_size);
		i++;
	}
}
