/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 16:23:09 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/02/28 12:14:38 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char **env, char *key)
{
	int	lenkey;
	int	lenenv;
	int	i;

	lenkey = 0;
	while (key[lenkey] && key[lenkey] != '=')
		lenkey++;
	i = 0;
	while (env[i])
	{
		lenenv = skip_until_char(env[i], '=');
		if (lenenv == lenkey && !ft_strncmp(env[i], key, lenenv))
			return (env[i] + lenkey + 1);
		i++;
	}
	return (NULL);
}

// int main(void)
// {
//     char    **env;
//     char    *value;

//     env = malloc(sizeof(char*) * (3 + 1));
//     env[0] = "key=value";
//     env[1] = "snoep=lekker";
//     env[2] = "zuurkool=vies";
//     value = get_env(env, "key");
//     printf("%s\n", value);
//     return (0);
// }
