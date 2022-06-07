/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   final_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 23:45:16 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/07 18:41:29 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Gets the size of the new array
**	Assumes there is an argument after the redeirection arguments where ...
**	... checked for syntax errors in parser_check
**	Determines the original size of the array
**	Substracts 2 of the original size of the array if it spots a redirection
**	Returns an integer with the size of the new array
*/

static int	get_new_size(t_word **arg)
{
	int	i;
	int	size;

	size = 0;
	if (!arg)
		return (size);
	while (arg[size])
		size++;
	i = 0;
	while (arg[i])
	{
		if (arg[i]->metacharacter == 1 && is_redirection(arg[i]->word))
		{
			size -= 2;
			i++;
		}
		i++;
	}
	return (size);
}

/*
**	Puts all information needed to execute the command into a null-terminated ...
**	... array of strings and handles redirections
**	Calls get_new_size to get the correct size of the new array
**	There can be none, one or multiple arguments
**	In case of a redirection
**		- redirection is called
**		- the redirection and next argument are not added to the final array
**	No return value
*/

void	get_final_args_and_handle_redirections(t_data *data,
	t_expression *expression, t_execute *exec)
{
	int	i;
	int	j;
	int	size;

	size = get_new_size(expression->arg);
	exec->args = malloc_guard(ft_calloc(sizeof(char *), size + 1));
	i = 0;
	j = 0;
	while (expression->arg && expression->arg[i])
	{
		if (expression->arg[i]->metacharacter
			&& is_redirection(expression->arg[i]->word))
		{
			if (redirection(data, expression->arg, i, exec->fd))
				return (free_array_part(&exec->args, j));
			i++;
		}
		else
		{
			exec->args[j] = malloc_guard(ft_strdup(expression->arg[i]->word));
			j++;
		}
		i++;
	}
}
