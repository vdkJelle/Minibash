/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/14 18:45:24 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/10/31 12:29:41 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Frees an array of strings
**	No return value
*/

void	free_array(char **array)
{
	int	i;
	int	size;

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
	array = NULL;
}

/*
**	Partly frees an array of strings
**	No return value
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
**	Frees a t_execute struct
**	No return value
*/

void	free_exec(t_execute *exec)
{
	free_array(exec->args);
	free(exec->path);
	free(exec);
	exec = NULL;
}

/*
**	Frees a t_expression struct
**	No return value
*/

void	free_expression(void *content)
{
	int				i;
	t_expression	*expression;

	i = 0;
	expression = (t_expression *)content;
	if (expression->arg)
	{
		while (expression->arg[i])
		{
			ft_lstclear(&expression->arg[i]->word_segment, free);
			free(expression->arg[i]->word);
			free(expression->arg[i]);
			i++;
		}
	}
	free(expression->arg);
	free(expression->control_operator);
	free(content);
	content = NULL;
}

/*
**	Frees a t_token struct
**	No return value
*/

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->string);
	free(token->control_operator);
	free(content);
	content = NULL;
}
