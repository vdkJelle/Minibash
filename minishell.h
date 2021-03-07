/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/03 13:27:01 by jelvan-d      ########   odam.nl         */
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

/*
**-----------------------------------STRUCTS------------------------------------
*/
typedef struct	s_data
{
	char	**our_env;
	char	*input;
	char	*curdir;
	int		env_size;
	int		r;
}				t_data;

typedef struct	s_token
{
	char		*cmd;
	char		*arg;
}				t_token;

/*
**------------------------------------CD.C--------------------------------------
*/
void	cd(char *path, char **our_env);

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
void	execute(char *path, t_data data);

/*
**----------------------------------EXPORT.C------------------------------------
*/
void	export(char **arg, char ***our_env, int *env_size);

/*
**----------------------------------GET_ENV.C-----------------------------------
*/
char    *get_env(char **env, char *key);

/*
**------------------------------------MAIN.C------------------------------------
*/
int		main(void);

/*
**-----------------------------------TOKEN.C------------------------------------
*/
void	get_token(char *line, t_list **token);

/*
**--------------------------------UTILS_LIST.C----------------------------------
*/
char	*create_string(char *arg);

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

/*
**------------------------------------PWD.C-------------------------------------
*/
void	pwd(void);


#endif
