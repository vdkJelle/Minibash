/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 12:22:34 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/03 13:04:08 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_string(char *arg)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(arg) + 3);
	while (arg[i] && arg[i] != '=')
	{
		ret[i] = arg[i];
		i++;
	}
	ret[i] = '=';
	ret[i + 1] = '"';
	while (arg[i + 1])
	{
		ret[i + 2] = arg[i + 1];
		i++;
	}
	ret[i + 2] = '"';
	ret[i + 3] = '\0';
	return (ret);
}
