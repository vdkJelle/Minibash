/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 11:55:58 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/04 13:54:34 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(char **our_env, int our_fd, int i, int j)
{
	int		fd;

	fd = our_fd;
	while (our_env[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (our_env[i][j])
		{
			ft_putchar_fd(our_env[i][j], fd);
			if (our_env[i][j] == '=')
				break ;
			j++;
		}
		if (our_env[i][j] == '=')
		{
			ft_putchar_fd('"', fd);
			j++;
			while (our_env[i][j])
			{
				ft_putchar_fd(our_env[i][j], fd);
				j++;
			}
			ft_putchar_fd('"', fd);
		}
		ft_putchar_fd('\n', fd);
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
		if (!ft_strncmp((*our_env)[i], arg, j))
		{
			if (ft_strchr(arg, '='))
				replace_entry(arg, our_env, i);
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
	while ((*our_env)[i])
	{
		tmp[i] = ft_strdup((*our_env)[i]);
		i++;
	}
	tmp[i] = ft_strdup(arg);
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
		print_export(data->our_env, data->our_fd[1], 0, 0);
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
