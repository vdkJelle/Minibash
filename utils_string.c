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

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while(s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - s2[i]);
}
