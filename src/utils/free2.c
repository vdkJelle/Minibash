/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 12:02:09 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/09 12:07:18 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Frees cur, prev and expression in case of invalid configuration
** No return value
*/

void	free_cur_prev_expression(
		t_execute *cur,
		t_execute *prev,
		t_expression *expression)
{
	free(cur);
	free(prev);
	free_expression(expression);
	return ;
}
