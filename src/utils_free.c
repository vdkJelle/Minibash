/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_free.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/14 18:45:24 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/05/24 13:39:47 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Frees an array of strings
** No return value
*/

void	free_array(char **array)
{
	int		i;
	int		size;

	if (!array)
		return ;
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

/*
** Frees an array of strings starting from a specific string
** No return value
*/

void	free_array_part(char ***array, int i)
{
	while (i > 0)
	{
		i--;
		free((*array)[i]);
	}
	free(*array);
	*array = NULL;
}

/*
** Frees a t_execute struct
** No return value
*/

void	free_exec(t_execute *exec)
{
	free_array(exec->args);
	free(exec->path);
	free(exec);
}

/*
** Frees a t_token struct
** No return value
*/

void	free_token(void *content)
{
	int		i;
	t_token	*token;

	i = 0;
	token = (t_token*)content;
	if (token->cmd)
	{
		ft_lstclear(&token->cmd->word_segment, free);
		free(token->cmd->word);
		free(token->cmd);
	}
	if (token->arg)
	{
		while (token->arg[i])
		{
			ft_lstclear(&token->arg[i]->word_segment, free);
			free(token->arg[i]->word);
			free(token->arg[i]);
			i++;
		}
	}
	free(token->arg);
	free(token->cop);
	free(content);
	content = NULL;
}
