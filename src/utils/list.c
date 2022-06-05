/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 11:46:52 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/03 14:16:24 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
