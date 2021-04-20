/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 12:23:16 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/04/12 15:54:43 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while(s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - s2[i]);
}

// char	*put_in_singlequotes(char *s)
// {
// 	char	*ret;
// 	int		i;
// 	int		len;

// 	if (!s || s[0] == '\0')
// 		return (NULL);
// 	len = ft_strlen(s);
// 	ret = malloc(sizeof(char) * len + 3);
// 	if (!ret)
// 		return (NULL);
// 	ret[0] = '\'';
// 	i = 0;
// 	while (i < len)
// 	{
// 		ret[i + 1] = s[i];
// 		i++;
// 	}
// 	ret[i + 1] = '\'';
// 	ret[i + 2] = '\0';
// 	return (ret);
// }
