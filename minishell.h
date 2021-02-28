/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/28 11:20:00 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"

/*
**------------------------------GLOBAL VARIABLES--------------------------------
*/
extern char	**environ;

/*
**-----------------------------------STRUCTS------------------------------------
*/
typedef struct	s_data
{
	char	**our_env;
	char	*input;
	char	*curdir;
	int		r;
}				t_data;

/*
**------------------------------------MAIN.C------------------------------------
*/
int		main(void);

/*
**------------------------------------CD.C--------------------------------------
*/
void	cd(char *path);

/*
**-------------------------------COUNT_QUOTES.C---------------------------------
*/
int		count_quotes(char *line);

/*
**------------------------------------ECHO.C------------------------------------
*/
void	ft_echo(char *line);
int		count_backslash(char *line, int loc);

/*
**--------------------------------EXECUTABLE.C----------------------------------
*/
void	execute(char *path, t_data data);

/*
**----------------------------------EXPORT.C------------------------------------
*/
void	export(char *input, t_data *data, char ***our_env);

/*
**------------------------------------PWD.C-------------------------------------
*/
void	pwd(void);

/*
**-------------------------------STRING_UTILS.C---------------------------------
*/
int		count_words(char const *s, char c);

#endif
