/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 13:49:21 by jelvan-d      #+#    #+#                 */
/*   Updated: 2019/11/11 11:33:54 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int i;

	i = 0;
	while (len > 0)
	{
		((unsigned char *)b)[i] = ((unsigned char)c);
		len--;
		i++;
	}
	return (b);
}
