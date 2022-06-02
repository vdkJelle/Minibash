/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:46:52 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/01 14:25:09 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Joins the word segments into a word
** Returns a malloced string with the word
*/

// char	*join_word(t_word *arg)
// {
// 	char	*word;
// 	int		size;
// 	t_list	*temp;

// 	temp = arg->word_segment;
// 	size = 0;
// 	while (temp)
// 	{
// 		size += ft_strlen(((char*)temp->content));
// 		temp = temp->next;
// 	}
// 	word = malloc_guard(ft_calloc(size + 1, sizeof(char)));
// 	temp = arg->word_segment;
// 	while (temp)
// 	{
// 		ft_strlcat(word, (char*)temp->content, size + 1);
// 		temp = temp->next;
// 	}
// 	return (word);
// }

/*
** Prints the contents of the expression
** No return value
*/

void	print_expression(void *content)
{
	int	i;

	i = 0;
	if (((t_expression*)content)->arg)
	{
		while (((t_expression*)content)->arg[i])
		{
			if (i == 0)
				printf("command\t\t\t= ");
			else
				printf("argument %d\t\t= ", i);
			printf("%s\n", ((t_expression*)content)->arg[i]->word);
			i++;
		}
	}
	if (!ft_strcmp(((t_expression*)content)->control_operator, "\0"))
		printf("control_operator\t= null terminator\n");
	else if (!ft_strcmp(((t_expression*)content)->control_operator, ";\0"))
		printf("control_operator\t= semi column\n");
	else if (!ft_strcmp(((t_expression*)content)->control_operator, "|\0"))
		printf("control_operator\t= pipe\n");
	else
		printf("illegal control_operator\t= %s\n", ((t_expression*)content)->control_operator);
	printf("\n");
}
