/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 10:37:48 by jelvan-d      #+#    #+#                 */
/*   Updated: 2019/11/20 16:06:40 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*p;

	if (s == 0)
		return (0);
	i = 0;
	p = malloc(ft_strlen(s) + 1);
	if (p == 0)
		return (0);
	while (s[i])
	{
		p[i] = (*f)(i, s[i]);
		i -= -1;
	}
	p[i] = '\0';
	return (p);
}
