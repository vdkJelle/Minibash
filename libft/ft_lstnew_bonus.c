/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 13:30:05 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/18 16:47:09 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*p;

	p = malloc(sizeof(t_list));
	if (p == 0)
		return (0);
	p->content = content;
	p->next = NULL;
	return (p);
}
