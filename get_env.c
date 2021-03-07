/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 16:23:09 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/02/28 13:34:28 by tevan-de      ########   odam.nl         */
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
	int	len_key;
	int	len_our_key;
	int	i;

	len_key = 0;
	while (key[len_key] && key[len_key] != '=')
		len_key++;
	i = 0;
	while (our_env[i])
	{
		len_our_key = skip_until_char(our_env[i], '=');
		if (len_our_key == len_key && !ft_strncmp(our_env[i], key, len_our_key))
			return (our_env[i] + len_key + 1);
		i++;
	}
	return (NULL);
}
