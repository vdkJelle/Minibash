/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/28 12:18:52 by tevan-de      ########   odam.nl         */
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

typedef struct	s_token
{
	char		*cmd;
	char		*arg;
}				t_token;

typedef struct	s_data
{
	char		*input;
	char		*curdir;
	int			r;
}				t_data;

extern char 	**environ;

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

/*
**--------------------------------EXECUTABLE.C----------------------------------
*/
void	execute(char *path);

/*
**----------------------------------GET_ENV.C-----------------------------------
*/
char    *get_env(char **env, char *key);

/*
**------------------------------------MAIN.C------------------------------------
*/
int		main(void);

/*
**------------------------------------PWD.C-------------------------------------
*/
void	pwd(void);

/*
**-----------------------------------TOKEN.C------------------------------------
*/
void	get_token(char *line, t_list **token);

/*
**--------------------------------UTILS_LIST.C----------------------------------
*/
void	free_token(void *content);
void 	print_token(void *content);

/*
**-------------------------------UTILS_STRING1.C--------------------------------
*/
void	skip_char(char **s, char c);
void	skip_chars(char **s, char c);
int		skip_chars_int(char *s, char c);
int		skip_until_char(char *s, char c);

/*
**-------------------------------UTILS_STRING2.C--------------------------------
*/
int		count_backslash(char *line, int loc);
int		count_words(char const *s, char c);

/*
**--------------------------UTILS_STRING_WHITESPACES.C--------------------------
*/
int		is_whitespace(char c);
void	skip_whitespaces(char **s);
int		skip_whitespaces_int(char *s);
void	skip_nonwhitespaces(char **s);
int		skip_nonwhitespaces_int(char *s);

#endif
