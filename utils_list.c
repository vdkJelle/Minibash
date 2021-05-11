/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:46:52 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/07 18:05:11 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


void	print_token(void *content)
{
	int		i;

	i = 0;
	printf("cmd = %s\n", ((t_token*)content)->cmd->word);
	while (((t_token*)content)->arg[i])
	{
		printf("arg = %s\n", ((t_token*)content)->arg[i]->word);
		i++;
	}
	if (!ft_strcmp(((t_token*)content)->cop, "\0"))
		printf("cop = null terminator\n");
	else if (!ft_strcmp(((t_token*)content)->cop, ";\0"))
		printf("cop = semi column\n");
	else if (!ft_strcmp(((t_token*)content)->cop, "|\0"))
		printf("cop = pipe\n");
	else
		printf("illegal cop = %s\n", ((t_token*)content)->cop);
}
