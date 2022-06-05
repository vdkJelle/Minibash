/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 16:30:26 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/05 17:37:35 by tessa         ########   odam.nl         */
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

/*
** Checks if all characters in the string are digits
** Returns TRUE if the string is numeric
** Returns FALSE if the string is empty or if the argument contains characters that are not digits
*/

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

/*
** Exits the program
** If there are no arguments the exit status is equal to our exit status
** If the first argument is not numeric (for example: exit nope)
**		an error message is printed
**		the program exits with exit status 2
** If the first argument is numeric but there are multiple arguments (for example: exit 4 nope ; exit 4 4)
**		an error message is printed
**		the program does not exit
**		the exit status is unchanged
** If the first argument is numeric and is the single argument exit is called with the value of the argument
** No return value
*/

void	ft_exit(t_data *data)
{
	e_bool	numeric;

	if (!data->args[1])
		exit(data->exit_status);
	numeric = is_string_numeric(data->args[1]);
	if (numeric == FALSE)
	{
		print_error(data, 2, make_array("🐶 > exit: ", data->args[1],
			": numeric argument required", NULL));
		exit(2);
	}
	if (data->args[2])
	{
		print_error(data, 1, make_array("🐶 > exit: too many arguments",
			NULL, NULL, NULL));
		return ;
	}
	exit(ft_atoi(data->args[1]));
}

// void	ft_exit(t_data *data)
// {
// 	char	**data->args;
// 	int		i;

// 	data->args = data->data->args;
// 	if (data->args[1] && data->args[2] != NULL)
// 	{
// 		print_error(data, 1, make_array("🐶 > exit: too many arguments", NULL, NULL, NULL));
// 		return ;
// 	}
// 	ft_putstr_fd("exit\n", data->our_fd[1]);
// 	if (data->args[1] && data->args[2] == NULL)
// 	{
// 		i = 0;
// 		while (data->args[1][i] && ft_isdigit(data->args[1][i]))
// 			i++;
// 		if (data->args[1][i] != '\0')
// 			print_error_exit(2, make_array("🐶 > exit: ", data->args[1], ": numeric argument required", NULL));
// 		data->exit_status = ft_atoi(data->args[1]);
// 	}
// 	exit(data->exit_status);
// }
