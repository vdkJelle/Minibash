/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 14:16:18 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/17 14:48:58 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_argument(t_data *data, t_word **arg, char *control_op, int i)
{
	if (!is_redirection(arg[i]->word))
	{
		print_error(data, 2, 1, "🐶 > Parser error");
		return (1);
	}
	if (!arg[i + 1])
	{
		if (control_op[0] == '\0')
			print_error(data, 2, 1,
			"🐶 > syntax error near unexpected token `newline'");
		else
			print_error(data, 2, 3,
			"🐶 > syntax error near unexpected token `", control_op, "'");
		return (1);
	}
	else if (arg[i + 1] && arg[i + 1]->metacharacter == 1)
	{
		print_error(data, 2, 3,
		"🐶 > syntax error near unexpected token `", arg[i + 1]->word, "'");
		return (1);
	}
	return (0);
}

static int	check_control_operator(t_data *data, char *s)
{
	if (!(!ft_strcmp(s, "|\0") || !ft_strcmp(s, ";\0") || s[0] == '\0'))
	{
		print_error(data, 2, 1, "🐶 > Parser error");
		return (1);
	}
	return (0);
}

int			check_token(t_data *data)
{
	int		i;
	t_list	*temp;
	t_token *token;

	temp = data->token;
	while (temp)
	{
		token = temp->content;
		if (check_control_operator(data, token->cop))
			return (1);
		i = 0;
		while (token->arg[i])
		{
			if (token->arg[i]->metacharacter == 1
			&& check_argument(data, token->arg, token->cop, i))
				return (1);
			i++;
		}
		temp = temp->next;
	}
	return (0);
}

// int		check_token(t_data *data)
// {
// 	int		i;
// 	t_list	*temp;

// 	temp = data->token;
// 	while (temp)
// 	{
// 		if (check_control_op(((t_token*)temp->content)->cop))
// 			return (1);
// 		i = 0;
// 		while ( ((t_token*)temp->content)->arg[i])
// 		{
// 			if (check_argument( ((t_token*)temp->content)->arg,
// 				((t_token*)temp->content)->cop, i))
// 				return (1);
// 			i++;
// 		}
// 		temp = temp->next;
// 	}
// 	return (0);
// }

// static int	check_argument(char **arg, char *control_op, int i)
// {
// 	if (arg[i][0] && is_metacharacter(arg[i][0]))
// 	{
// 		if (!is_redirection(arg[i]))
// 		{
// 			ft_putstr_fd("Parser error\n", 2); /*exit status 1*/
// 			return (1);
// 		}
// 		if (!arg[i + 1])
// 		{
// 			if (control_op[0] == '\0')
// 				print_syntax_error('\0');
// 			else
// 				print_syntax_error(control_op[0]);
// 			return (1);
// 		}
// 		if (arg[i + 1] && is_metacharacter(arg[i + 1][0]))
// 		{
// 			print_syntax_error(arg[i + 1][0]);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }
