/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 13:37:39 by jelvan-d      #+#    #+#                 */
/*   Updated: 2019/11/14 09:27:05 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*begin_location(const char *s1, const char *set)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (set[n])
	{
		if (s1[i] == set[n])
		{
			i++;
			n = -1;
		}
		n++;
	}
	return (&s1[i]);
}

static const char	*end_location(const char *s1, const char *set)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (s1[i])
		i++;
	i--;
	while (set[n])
	{
		if (s1[i] == set[n] && i > 0)
		{
			i--;
			n = -1;
		}
		n++;
	}
	return (&s1[i]);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	int			i;
	char		*p;
	const char	*beginchar;
	const char	*endchar;

	if (s1 == 0)
		return (0);
	i = 0;
	beginchar = begin_location(s1, set);
	endchar = end_location(s1, set);
	if (endchar - beginchar < 0)
	{
		p = malloc(sizeof(char));
		if (p == 0)
			return (0);
		p[i] = '\0';
	}
	else
	{
		p = malloc(endchar - beginchar + 2);
		if (p == 0)
			return (0);
		ft_strlcpy(p, beginchar, endchar - beginchar + 2);
	}
	return (p);
}
