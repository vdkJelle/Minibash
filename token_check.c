/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 14:16:18 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/11 11:18:40 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_syntax_error(char *s)
{
	ft_putstr_fd("🐶 > syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

static int	check_argument(t_word **arg, char *control_op, int i)
{
	if (!is_redirection(arg[i]->word))
	{
		ft_putstr_fd("Parser error\n", 2);
		return (1);
	}
	if (!arg[i + 1])
	{
		if (control_op[0] == '\0')
			return (print_syntax_error("newline"));
		else
			return (print_syntax_error(control_op));
	}
	else if (arg[i + 1] && arg[i + 1]->metacharacter == 1)
		return (print_syntax_error(arg[i + 1]->word));
	return (0);
}

static int	check_control_operator(char *s)
{
	if (!(!ft_strcmp(s, "|\0") || !ft_strcmp(s, ";\0") || s[0] == '\0'))
	{
		ft_putstr_fd("Parser error\n", 2);
		return (1);
	}
	return (0);
}

int		check_token(t_data *data)
{
	int		i;
	t_list	*temp;
	t_token *token;

	temp = data->token;
	while (temp)
	{
		token = (t_token*)data->token->content;
		if (check_control_operator(token->cop))
			return (1);
		i = 0;
		while (token->arg[i])
		{
			if (token->arg[i]->metacharacter == 1
			&& check_argument(token->arg, token->cop, i))
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
