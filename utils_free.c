/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_free.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/14 18:45:24 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/14 18:45:38 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int		i;
	int		size;

	size = 0;
	while (array[size])
		size++;
	i = 0;
	while (i <= size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_array_part(char **array, int i)
{
	i--;
	while (i < 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

void	free_exec(t_execute *exec)
{
	free_array(exec->args);
	free(exec->path);
	free(exec);
}

void	free_token(void *content)
{
	int		i;
	t_token	*token;

	i = 0;
	token = (t_token*)content;
	ft_lstclear(&token->cmd->word_segment, free);
	free(token->cmd->word);
	free(token->cmd);
	while (token->arg[i])
	{
		ft_lstclear(&token->arg[i]->word_segment, free);
		free(token->arg[i]->word);
		free(token->arg[i]);
		i++;
	}
	free(token->arg);
	free(token->cop);
	free(content);
	content = NULL;
}
