/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 13:07:34 by jelvan-d      #+#    #+#                 */
/*   Updated: 2019/11/20 15:53:29 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	i = 0;
	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	p = malloc(sizeof(*s) * (len + 1));
	if (p == 0)
		return (NULL);
	while (len > i)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}
