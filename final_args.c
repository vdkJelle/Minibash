/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   final_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 23:45:16 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/13 23:45:39 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_arg(char *arg, char **ret)
{
	*ret = ft_strdup(arg);
	if (!(*ret))
		exit(1);
	return (1);
}


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

void		final_args(t_data *data, t_token *token, t_execute *exec)
{
	int		i;
	int		j;

	exec->args = malloc(sizeof(char *) * (get_new_size(token->arg) + 2));
	if (!exec->args)
		exit(1);
	i = 0;
	j = append_arg(token->cmd->word, &exec->args[0]);
	while (token->arg[i])
	{
		if (is_redirection(token->arg[i]->word) && token->arg[i]->metacharacter == 1)
		{
			if (handle_redirection(data, token->arg, i, exec->fd) == -1)
				return (free_array_part(exec->args, j));
			i++;
		}
		else
			j += append_arg(token->arg[i]->word, &exec->args[j]);
		i++;
	}
	exec->args[j] = NULL;
}
