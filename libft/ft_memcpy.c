/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 16:12:41 by jelvan-d      #+#    #+#                 */
/*   Updated: 2019/10/31 16:27:52 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int i;

	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	while (n > 0)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
		n--;
	}
	return (dst);
}
