/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 11:55:58 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/03 13:28:01 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(char **our_env)
{
	int i;

	i = 0;
	while (our_env[i])
	{
		printf("declare -x %s\n", our_env[i]);
		i++;
	}
}

static void	append_key_value(char *arg, char ***our_env, int *env_size)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * ((*env_size) + 2));
	while ((*our_env)[i])
	{
		tmp[i] = ft_strdup((*our_env)[i]);
		i++;
	}
	tmp[i] = create_string(arg);
	tmp[i + 1] = NULL;
	// free_array(our_env);
	(*our_env) = tmp;
}

static int	check_if_valid(char *input, int *i)
{
	if (!ft_isalpha(input[*i]) || input[*i] != '_')
		return (1);
	while (input[*i] && input[*i] != '=')
	{
		if (!ft_isalnum(input[*i] || input[*i] != '_'))
			return (1);
		(*i)++;
	}
	return (0);
}

void		export(char **arg, char ***our_env, int *env_size)
{
	int	i;
	int	j;

	if (!arg[0])
		print_export(*our_env);
	else
	{
		j = 0;
		while (arg[j])
		{
			i = 0;
			if (check_if_valid(arg[j], &i))
			{
				printf("🐶: export: not a valid identifier: %s\n", arg[j]);
				j++;
				continue ;
			}
			if (arg[j][i] == '=')
				append_key_value(arg[j], our_env, env_size);
			// else
				// append_key(arg[j], our_env, env_size);
			j++;
		}
	}
}
