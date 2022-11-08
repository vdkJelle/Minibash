/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 14:16:18 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/11/08 15:58:49 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Checks if the arguments are valid
**	Codyshell only handles these metacharacters: > >> < << not ( ) &
**	A syntax error occurs if the argument after a redirection doesn't exist ...
**	... or is a metacharacter
**	Returns 0 if an argument is valid and there is no syntax error
**	Returns 1 if an argument is invalid or if there is a syntax error
*/

static int	check_argument(t_data *data, t_word **arg, char *control_operator,
int i)
{
	if (!is_redirection(arg[i]->word))
	{
		print_error(data, 2, make_array(SHELL, "Invalid metacharacter: ",
				arg[i]->word, NULL));
		return (1);
	}
	if (!arg[i + 1])
	{
		if (control_operator[0] == '\0')
			print_error(data, 2, make_array(SHELL,
					"syntax error near unexpected", " token `newline'", NULL));
		else
			print_error(data, 2, make_array(
					"codyshell: syntax error near unexpected", " token `",
					control_operator, "'"));
		return (1);
	}
	else if (arg[i + 1] && arg[i + 1]->metacharacter == 1)
	{
		print_error(data, 2, make_array(
				"codyshell: syntax error near unexpected", " token `",
				arg[i + 1]->word, "'"));
		return (1);
	}
	return (0);
}

/*
**	Checks if the control operator is valid
**	Codyshell only handles these control operators: \0 | ; not ( ) &
**	Returns 0 if the control operator is valid
**	Returns 1 if the control operator is invalid
*/

static int	check_control_operator(t_data *data, char *s)
{
	if (!(!ft_strcmp(s, "|\0") || !ft_strcmp(s, ";\0") || s[0] == '\0'))
	{
		print_error(data, 2, make_array(SHELL, "Invalid control operator: ", s,
				NULL));
		return (1);
	}
	return (0);
}

/*
**	Checks if the argument is valid in  case of a pipe
**	Returns 1 if the current expression doesn't have an argument
**		- for example: echo | | is a syntax error
**	Returns 1 if the next expression doesn't have an argument
**		- for example echo | or echo hi ; ; ; ; echo | is a multiline command
**	Returns 0 if there are no errors
*/

static int	check_argument_pipe(t_data *data, t_expression *cur, t_list *list)
{
	if (!ft_strcmp(cur->control_operator, "|"))
	{
		if (list->next && !((t_expression *)list->next->content)->arg)
		{
			print_error(data, 2,
				make_array(SHELL, "syntax error near unexpected token `",
					((t_expression *)list->next->content)->control_operator,
					"'"));
			return (1);
		}
		if (!list->next)
		{
			print_error(data, 2, make_array(SHELL, "Multiline command", NULL,
					NULL));
			return (1);
		}
	}
	return (0);
}

/*
**	Checks the token sets for validity and syntax errors
**	Calls check_control_operator to check for errors in the control operator
**	Calls check_argument to check for check for errors in the arguments
**	Returns 0 if the input was valid and there were no syntax errors
**	Returns 1 if the input was invalid or if there were syntax errors
*/

int	check_input(t_data *data)
{
	int				i;
	t_list			*temp;
	t_expression	*expression;

	parse_all(data);
	temp = data->expression;
	while (temp)
	{
		expression = temp->content;
		if (check_control_operator(data, expression->control_operator)
			|| check_argument_pipe(data, expression, temp))
			return (1);
		i = 0;
		while (expression->arg && expression->arg[i])
		{
			if (expression->arg[i]->metacharacter && check_argument(data,
					expression->arg, expression->control_operator, i))
				return (1);
			i++;
		}
		temp = temp->next;
	}
	ft_lstclear(&data->expression, free_expression);
	return (0);
}
