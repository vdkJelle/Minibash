 /* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 12:23:16 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/13 20:58:19 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Compares two strings
** Returns 0 if the strings are identical
** Returns an integer not equal to 0 if they are different
*/

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while(s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - s2[i]);
}

/*
** Wrapper function for ft_strjoin
** Calls ft_strjoin which returns the malloc concatenated string
** Depending on the mode it frees nothing, string 1, string 2 or both
** Returns the malloced concatenated string
** Returns NULL if something went wrong in ft_strjoin
*/

char	*ft_strjoin_wrapper(char *s1, char *s2, int mode)
{
	char	*s;
	
	s = ft_strjoin(s1, s2);
	if (mode == 1)
		free(s1);
	else if (mode == 2)
		free(s2);
	else if (mode == 3)
	{
		free(s1);
		free(s2);
	}
	if (!s)
		return (NULL);
	return (s);
}
