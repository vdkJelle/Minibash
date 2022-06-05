/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 16:30:26 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/05 15:34:00 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Terminates the calling process
** If there there are no arguments the process is terminated with exit code 0
** If there is one argument and it's numeric (n)
**		the process is terminated with exit code n
** If there is one argument and isn't numeric
**		the error is printed and the process is terminated with exit code 1
** If there is more than one argument the error is printed and the process is
**		not terminated
** No return value
*/

// exit 4 nope
// exit 4 4
// too many arguments
// exit status 1
// no actual exit

// exit nope 4
// numeric argument
// exit status 2
// actual exit

static e_bool	is_string_numeric(char *s)
{
	int i;

	if (ft_strlen(s))
	{
		i = skip_while_char(s, ft_isdigit_char);
		if (!s[i])
			return (TRUE);
	}
	return (FALSE);
}

void	ft_exit(t_data *data)
{
	char	**args;
	e_bool	numeric;

	args = data->args;
	ft_putstr_fd("exit\n", 1);
	if (!args[1])
		exit(data->exit_status);
	numeric = is_string_numeric(args[1]);
	if (numeric == FALSE)
	{
		print_error(data, 2, make_array("🐶 > exit: ", args[1], ": numeric argument required", NULL));
		exit(2);
	}
	if (args[2])
	{
		print_error(data, 1, make_array("🐶 > exit: too many arguments", NULL, NULL, NULL));
		return ;
	}
	exit(ft_atoi(args[1]));
}

// void	ft_exit(t_data *data)
// {
// 	char	**args;
// 	int		i;

// 	args = data->args;
// 	if (args[1] && args[2] != NULL)
// 	{
// 		print_error(data, 1, make_array("🐶 > exit: too many arguments", NULL, NULL, NULL));
// 		return ;
// 	}
// 	ft_putstr_fd("exit\n", data->our_fd[1]);
// 	if (args[1] && args[2] == NULL)
// 	{
// 		i = 0;
// 		while (args[1][i] && ft_isdigit(args[1][i]))
// 			i++;
// 		if (args[1][i] != '\0')
// 			print_error_exit(2, make_array("🐶 > exit: ", args[1], ": numeric argument required", NULL));
// 		data->exit_status = ft_atoi(args[1]);
// 	}
// 	exit(data->exit_status);
// }
