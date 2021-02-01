/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:54:49 by jelvan-d      #+#    #+#                 */
/*   Updated: 2019/11/07 17:08:35 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle,
					size_t len)
{
	size_t		i;
	size_t		n;
	size_t		tmp;
	const char	*p;

	i = 0;
	n = 0;
	if (needle[n] == '\0')
		return ((char *)&haystack[i]);
	while (haystack[i] && i < len)
	{
		p = &haystack[i];
		tmp = i;
		while (haystack[i] == needle[n] && i < len && needle[n])
		{
			n++;
			i++;
		}
		if (needle[n] == '\0')
			return ((char *)p);
		n = 0;
		i = tmp;
		i++;
	}
	return (0);
}
