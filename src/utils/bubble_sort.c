/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bubble_sort.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/05 12:13:34 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/05 13:10:06 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **sort(char **sorted_env)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	while (sorted_env[i])
	{
		j = i + 1;
		while (sorted_env[j])
		{
			if (*sorted_env[i] > *sorted_env[j])
			{
				tmp = sorted_env[i];
				sorted_env[i] = sorted_env[j];
				sorted_env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (sorted_env);
}

char **bubble_sort(char **env, int *env_size)
{
	char **sorted_env;
	int	i;

	sorted_env = ft_malloc(((*env_size)+ 1) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		sorted_env[i] = malloc_guard(ft_strdup(env[i]));
		i++;
	}
	sorted_env[i] = NULL;
	return (sort(sorted_env));
}
