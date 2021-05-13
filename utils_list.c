/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:46:52 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/13 17:13:46 by tevan-de      ########   odam.nl         */
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

char	*join_word(t_word *arg)
{
	char	*word;
	int		size;
	t_list	*temp;

	temp = arg->word_segment;
	size = 0;
	while (temp)
	{
		size += ft_strlen(((char*)temp->content));
		temp = temp->next;
	}
	word = ft_calloc(size + 1, sizeof(char));
	if (!word)
		exit(1);
	temp = arg->word_segment;
	while (temp)
	{
		ft_strlcat(word, (char*)temp->content, size + 1);
		temp = temp->next;
	}
	return (word);
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
