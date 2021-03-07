/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string_strjoin.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 11:36:03 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/03/07 19:58:20 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	*p;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	p = malloc(sizeof(char) * (len + 2));
	if (!p)
	{
		free(s);
		return (NULL);
	}
	ft_strlcpy(p, s, len + 1);
	free(s);
	p[len] = c;
	p[len + 1] = '\0';
	return (p);
}

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	char	*p;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	p = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!p)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_strlcpy(p, s1, len_s1 + 1);
	free(s1);
	ft_strlcpy(p + len_s1, s2, len_s2 + 1);
	free(s2);
	return (p);
}

char	*ft_strjoin_free_s1(char *s1, char const *s2)
{
	char	*p;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	p = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!p)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(p, s1, len_s1 + 1);
	free(s1);
	ft_strlcpy(p + len_s1, s2, len_s2 + 1);
	return (p);
}
