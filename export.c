/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 11:55:58 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/06 14:54:15 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(char **our_env, int our_fd)
{
	int	i;
	int	j;

	i = 0;
	while (our_env[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (our_env[i][j])
		{
			ft_putchar_fd(our_env[i][j], our_fd);
			if (our_env[i][j] == '=')
				break ;
			j++;
		}
		if (our_env[i][j] == '=')
		{
			ft_putchar_fd('"', our_fd);
			ft_putstr_fd(our_env[i] + j + 1, our_fd);
			ft_putchar_fd('"', our_fd);
		}
		ft_putchar_fd('\n', our_fd);
		i++;
	}
}

static int	check_if_exists(char *arg, char ***our_env)
{
	int		i;
	int 	j;

	i = 0;
	j = 0;
	while ((*our_env)[i])
	{
		j = 0;
		while ((*our_env)[i][j] && (*our_env)[i][j] != '=')
			j++;
		if (!ft_strncmp((*our_env)[i], arg, skip_until_char_excl(arg, '=')))
		{
			if (ft_strchr(arg, '='))
			{
				free((*our_env)[i]);
				(*our_env)[i] = NULL;
				(*our_env)[i] = ft_strdup(arg);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

static void	append_key_value(char *arg, char ***our_env, int *env_size)
{
	char	**tmp;
	int		i;

	if (check_if_exists(arg, our_env))
		return ;
	i = 0;
	tmp = (char **)malloc(sizeof(char *) * ((*env_size) + 2));
	if (!tmp)
		exit(1);
	while ((*our_env)[i])
	{
		tmp[i] = ft_strdup((*our_env)[i]);
		if (!tmp[i])
			exit(1);
		i++;
	}
	tmp[i] = ft_strdup(arg);
	if (!tmp[i])
		exit(1);
	tmp[i + 1] = NULL;
	(*env_size)++;
	free_array(*our_env);
	(*our_env) = tmp;
}

static int	check_if_valid(char *input)
{
	int		i;

	i = 0;
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (1);
	while (input[i] && input[i] != '=')
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void		ft_export(t_data *data)
{
	int		i;
	char	**arg;

	arg = data->arg;
	if (!arg[1])
		print_export(data->our_env, data->our_fd[1]);
	else
	{
		i = 1;
		while (arg[i])
		{
			if (check_if_valid(arg[i]))
			{
				printf("🐶: export: `%s\': not a valid identifier\n", arg[i]);
				i++;
				continue ;
			}
			append_key_value(arg[i], &data->our_env, &data->env_size);
			i++;
		}
	}
}
