/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 16:30:26 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/10/31 14:10:29 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Checks if all characters in the string are digits
**	Returns TRUE if the string is numeric
**	Returns FALSE if the string is empty or if the string contains a ...
**	... character that is not a digit
*/

static enum e_bool	is_string_numeric(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s))
	{
		i += skip_while_char(s, is_whitespace);
		if (s[i] == '-' || s[i] == '+')
			i++;
		i += skip_while_char(s, ft_isdigit_char);
		i += skip_while_char(s, is_whitespace);
		if (!s[i])
			return (TRUE);
	}
	return (FALSE);
}

/*
**	Exits the program
**	If there are no arguments the exit status is equal to our exit status
**	If the first argument is not numeric
**		- example: exit nope or exit 42a
**		- an error message is printed
**		- the program exits with exit status 255
**	If the first argument is numeric but there are multiple arguments
**		- example: exit 42 nope or exit 42 42
**		- an error message is printed
**		- the program does not exit
**		- the exit status is unchanged
**	If the first argument is numeric and is the single argument exit is ...
**	... called with the value of the argument
**		- example: exit 42
**	Calling exit with a number smaller than 0 or bigger than 255 will result ...
**	... in undefined behavior
**	No return value
*/

void	ft_exit(t_data *data)
{
	enum e_bool	numeric;

	if (!data->args[1])
		exit(data->exit_status);
	numeric = is_string_numeric(data->args[1]);
	if (numeric == FALSE)
	{
		print_error(data, 255, make_array("🐶 > exit: ", data->args[1],
				": numeric argument required", NULL));
		exit(data->exit_status);
	}
	if (data->args[2])
	{
		print_error(data, 1, make_array("🐶 > exit: too many arguments",
				NULL, NULL, NULL));
		return ;
	}
	exit(ft_atoi(data->args[1]));
}
