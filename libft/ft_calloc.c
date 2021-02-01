/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 12:50:50 by jelvan-d      #+#    #+#                 */
/*   Updated: 2019/11/12 22:32:48 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*p;

	i = 0;
	p = malloc(size * count);
	if (p == 0)
		return (0);
	while (i < (count * size))
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}
