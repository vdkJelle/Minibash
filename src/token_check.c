/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 14:16:18 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/05/25 16:13:29 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Checks if the arguments are valid
** Codyshell only handles these metacharacters: > >> < not ( ) &
** A syntax error occurs if
**		the argument after a redirection doesn't exist or is a metacharacter
** Returns 0 if an argument is valid and there is no syntax error
** Returns 1 if an argument is invalid or if there is a syntax error
*/

static int	check_argument(t_data *data, t_word **arg, char *control_op, int i)
{
	if (!is_redirection(arg[i]->word))
	{
		print_error(data, 2, make_array("🐶 > Invalid metacharacter: ", arg[i]->word, NULL, NULL));
		return (1);
	}
	if (!arg[i + 1])
	{
		if (control_op[0] == '\0')
			print_error(data, 2, make_array("🐶 > syntax error near unexpected token `newline'", NULL, NULL, NULL));
		else
			print_error(data, 2, make_array("🐶 > syntax error near unexpected token `", control_op, "'", NULL));
		return (1);
	}
	else if (arg[i + 1] && arg[i + 1]->metacharacter == 1)
	{
		print_error(data, 2, make_array("🐶 > syntax error near unexpected token `", arg[i + 1]->word, "'", NULL));
		return (1);
	}
	return (0);
}

/*
** Checks if the control operator is valid
** Codyshell only handles these control operators: \0 | ; not ( ) &
** Returns 0 if the control operator is valid
** Returns 1 if the control operator is invalid
*/

static int	check_control_operator(t_data *data, char *s)
{
	if (!(!ft_strcmp(s, "|\0") || !ft_strcmp(s, ";\0") || s[0] == '\0'))
	{
		print_error(data, 2, make_array("🐶 > Invalid control operator: ", s, NULL, NULL));
		return (1);
	}
	return (0);
}

static int	check_next_control_operator(t_data *data, t_token *cur, t_token *next)
{
	if (!ft_strcmp(cur->cop, "|") && !cur->arg)
	{
		print_error(data, 2, make_array("🐶 > syntax error near unexpected token `", cur->cop, "'", NULL));
		return (1);
	}
	if (!ft_strcmp(cur->cop, "|") && !next->arg)
	{
		print_error(data, 2, make_array("🐶 > syntax error near unexpected token `", cur->cop, "'", NULL));
		return (1);
	}
	return (0);
}

/*
** Checks the token sets for validity and syntax errors
** Calls check_control_operator to check for errors in the control operator
** Calls check_argument to check for check for errors in the arguments
** Returns 0 if the input was valid and there were no syntax errors
** Returns 1 if the input was invalid or if there were syntax errors
*/

int			check_token(t_data *data)
{
	int		i;
	t_list	*temp;
	t_token *token;

	temp = data->token;
	while (temp)
	{
		token = temp->content;
		if (check_control_operator(data, token->cop) || (temp->next &&
			check_next_control_operator(data, token, temp->next->content)))
			return (1);
		i = 0;
		if (token->arg)
		{
			while (token->arg[i])
			{
				if (token->arg[i]->metacharacter == 1
				&& check_argument(data, token->arg, token->cop, i))
					return (1);
				i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}
