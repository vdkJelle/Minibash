/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:46:52 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/14 18:45:16 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
