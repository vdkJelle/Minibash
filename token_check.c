/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 14:16:18 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/04/13 12:51:43 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//exit status should be 2 if there is a syntax error
static void	print_syntax_error(char c)
{
	ft_putstr_fd("🐶 > syntax error near unexpected token `", 2);
	if (c == '\0')
		ft_putstr_fd("newline", 2);
	else
		write(2, &c, 1);
	ft_putstr_fd("'\n", 2);
}

static int	check_argument(char **arg, char *control_op, int i)
{
	if (arg[i][0] && is_metacharacter(arg[i][0]))
	{
		if (!is_redirection(arg[i]))
		{
			ft_putstr_fd("Parser error\n", 2); /*exit status 1*/
			return (1);
		}
		if (!arg[i + 1])
		{
			if (control_op[0] == '\0')
				print_syntax_error('\0');
			else
				print_syntax_error(control_op[0]);
			return (1);
		}
		if (arg[i + 1] && is_metacharacter(arg[i + 1][0]))
		{
			print_syntax_error(arg[i + 1][0]);
			return (1);
		}
	}
	return (0);
}

//exit status 1
static int	check_control_op(char *s)
{
	if (!(!ft_strcmp(s, "|\0") || !ft_strcmp(s, ";\0") || s[0] == '\0'))
	{
		ft_putstr_fd("Parser error\n", 2);
		return (1);
	}
	return (0);
}

//try to get rid off data->start, will make it possible for everything to fit
int		check_token(t_data *data)
{
	int		i;
	t_list	*temp;

	temp = data->token;
	while (temp)
	{
		if (check_control_op(((t_token*)temp->content)->cop))
			return (1);
		i = 0;
		while ( ((t_token*)temp->content)->arg[i])
		{
			if (check_argument( ((t_token*)temp->content)->arg,
				((t_token*)temp->content)->cop, i))
				return (1);
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
