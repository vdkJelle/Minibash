/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 15:38:40 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/11 11:11:49 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	destroy_entry(char ***our_env, int *env_size, int i)
{
	free((*our_env)[i]);
	while ((*our_env)[i])
	{
		(*our_env)[i] = (*our_env)[i + 1];
		i++;
	}
	(*env_size)--;
}

static void	check_for_entry(char *arg, char ***our_env, int *env_size)
{
	int		i;
	int 	j;

	i = 0;
	while ((*our_env)[i])
	{
		j = 0;
		while ((*our_env)[i][j] && (*our_env)[i][j] != '=')
			j++;
		if (!ft_strncmp((*our_env)[i], arg, j))
			return (destroy_entry(our_env, env_size, i));
		i++;
	}
	return ;
}

static int	check_if_valid(char *input)
{
	int		i;

	i = 0;
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (1);
	while (input[i])
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(t_data *data)
{
	char	**args;
	int		exit_stats;
	int		i;

	args = data->args;
	exit_stats = 0;
	i = 1;
	while (args[i])
	{
		if (check_if_valid(args[i]))
		{
			ft_putstr_fd("🐶 > unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_stats = 1;
		}
		else
			check_for_entry(args[i], &data->our_env, &data->env_size);
		i++;
	}
	data->exit_status = exit_stats;
}
