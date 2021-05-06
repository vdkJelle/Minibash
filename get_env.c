/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 16:23:09 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/04 13:44:29 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Finds the value of our environmental variables based on the key
** If the key matches the key in our enviromental variables the value is returned
** Else the function returns NULL
*/

char	*get_env(char **our_env, char *key)
{
	int		len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (our_env[i])
	{
		if (!ft_strncmp(our_env[i], key, len))
		{
			if (ft_strchr(our_env[i], '=') && our_env[i][len] == '=')
				return (our_env[i] + len + 1);
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
