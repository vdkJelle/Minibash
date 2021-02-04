/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/04 17:44:02 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"

typedef struct	s_data
{
	char	*input;
	char	*curdir;
	int		r;
}				t_data;

/*
**------------------------------------MAIN.C------------------------------------
*/
int		main(void);

/*
**------------------------------------PWD.C-------------------------------------
*/
void	pwd(t_data data);

#endif
