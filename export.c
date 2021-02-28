/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 11:55:58 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/28 12:25:21 by jelvan-d      ########   odam.nl         */
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

static int	check_if_valid(char *input)
{
	int i;

	i = 0;
	if ((input[i] <= 'A' || input[i] >= 'Z') && (input[i] <= 'a' && input[i] >= 'z'))
		return (1);
	while (input[i] && input[i] != '=')
	{
		if ((input[i] <= 'A' || input[i] >= 'Z') && (input[i] <= 'a' || input[i] >= 'z') && (input[i] <= '0' || input[i] >= '9'));
		return (2);
		i++;
	}
}

void		export(char *input, t_data *data, char ***our_env)
{
	int			i;

	(void)data;
	if (ft_strlen(input) == 6)
		print_export(*our_env);
	else
	{
		i = 6;
		while (input[i] == ' ')
			i++;
		if (check_if_valid(input + i) == 1)
			return (printf("export: not an identifier: %s\n", input + i));
		if (check_if_valid(input + i) == 2)
			return (printf("export: not valid in this context: %s\n", input + i));
		// i = append_env(input + i);
	}
}
