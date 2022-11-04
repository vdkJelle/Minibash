/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 10:00:51 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/09/07 12:19:22 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		wc++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (wc);
}

static int	word_length(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\0')
			return (len);
		i++;
		len++;
	}
	return (len);
}

static void	cleanup(char **p, int pi)
{
	int	i;

	i = 0;
	while (i < pi)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

static char	**write_malloc(char const *s, char c, char **p, int wc)
{
	int		m;
	int		i;

	i = 0;
	m = 0;
	while (wc > 0)
	{
		p[0] = (char *)malloc(sizeof(char) * (word_length(s, c, i) + 1));
		if (p[0] == 0)
			return (0);
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			p[0][m] = s[i];
			i++;
			m++;
		}
		p[0][m] = '\0';
		m = 0;
		p++;
		wc--;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		wc;
	char	**p;
	int		pi;

	if (s == 0)
		return (0);
	pi = 0;
	wc = count_words(s, c);
	p = (char **)malloc(sizeof(char *) * (wc + 1));
	if (p == 0)
		return (0);
	write_malloc(s, c, p, wc);
	while (pi < wc)
	{
		if (p[pi] == NULL)
		{
			cleanup(p, pi);
			return (NULL);
		}
		pi++;
	}
	p[wc] = NULL;
	return (p);
}
