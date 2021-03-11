/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 15:38:40 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/10 16:04:47 by jelvan-d      ########   odam.nl         */
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
	int	i;
	int j;

	i = 0;
	j = 0;
	while ((*our_env)[i])
	{
		j = 0;
		while ((*our_env)[i][j] && (*our_env)[i][j] != '=')
			j++;
		if (!ft_strncmp((*our_env)[i], arg, j))
		{
			destroy_entry(our_env, env_size, i);
			return ;
		}
		i++;
	}
	return ;
}

static int	check_if_valid(char *input)
{
	int i;

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
	int		i;
	char	**arg;

	arg = ((t_token*)data->token->content)->arg;
	i = 0;
	while (arg[i])
	{
		if (check_if_valid(arg[i]))
		{
			printf("🐶: unset: `%s\': not a valid identifier\n", arg[i]);
			i++;
			continue ;
		}
		check_for_entry(arg[i], &data->our_env, &data->env_size);
		i++;
	}
}
