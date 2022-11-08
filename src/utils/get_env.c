/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 16:23:09 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/11/08 11:54:57 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Finds the value of an environmental variable based on the key
**	Returns a pointer to a string where the value starts if it finds a match
**	Returns NULL if it doesn't find a match
**	Returns NULL if the environmental variable doesn't have a value
*/

char	*get_env(char **our_env, char *key)
{
	int		len;
	int		i;
	char	*tmp;

	tmp = malloc_guard(ft_strjoin_wrapper(key, "=", 0));
	len = ft_strlen(tmp);
	i = 0;
	while (our_env[i])
	{
		if (!ft_strncmp(our_env[i], tmp, len))
		{
			free (tmp);
			if (ft_strchr(our_env[i], '=') && our_env[i][len - 1] == '=')
				return (our_env[i] + len);
			else
				return (NULL);
		}
		i++;
	}
	free (tmp);
	return (NULL);
}
