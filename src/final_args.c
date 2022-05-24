/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   final_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 23:45:16 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/05/23 21:52:20 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Appends the command or argument to the array of strings
** Returns 1
*/

static int	append_arg(char *arg, char **ret)
{
	*ret = ft_strdup(arg);
	if (!(*ret))
		exit(1);
	return (1);
}

/*
** Gets the size of the new array
** Determines the original size of the array
** Substracts 2 of the original size of the array if it spots a redirection
** Returns an integer with the size of the new array
*/

static int	get_new_size(t_word **arg)
{
	int		i;
	int		size;

	size = 0;
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
** Puts all information needed to execute the command into an array of strings
** Calls get_new_size to get the correct size of the new array
** The first string of the array is always the command
** There can be none, one or multiple arguments following
** If I/O is redirected
**		the redirection and next argument not added
**		redirection is called
** Else the argument is appended to the array of strings
** No return value
*/

void	get_final_args_and_handle_redirections(t_data *data,
	t_token *token, t_execute *exec)
{
	int		i;
	int		j;

	(void)data;
	exec->args = malloc(sizeof(char *) * (get_new_size(token->arg) + 2));
	if (!exec->args)
		exit(1);
	i = 0;
	j = append_arg(token->cmd->word, &exec->args[0]);
	while (token->arg[i])
	{
		if (is_redirection(token->arg[i]->word) && token->arg[i]->metacharacter == 1)
		{
			if (redirection(data, token->arg, i, exec->fd) == -1)
				return (free_array_part(&exec->args, j));
			i++;
		}
		else
			j += append_arg(token->arg[i]->word, &exec->args[j]);
		i++;
	}
	exec->args[j] = NULL;
}
