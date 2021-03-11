/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 13:46:24 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/10 15:51:01 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_entry(char *arg, char ***our_env, int i)
{
	free((*our_env)[i]);
	(*our_env)[i] = NULL;
	(*our_env)[i] = ft_strdup(arg);
}
