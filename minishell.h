/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/07 20:10:37 by tevan-de      ########   odam.nl         */
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

typedef struct	s_token
{
	char		*cmd;
	char		**arg;
}				t_token;

typedef struct	s_data
{
	char		**our_env;
	char		*input;
	int			env_size;
	int			fd_count;
	int			r;
	t_list		*token;
}				t_data;

/*
**-------------------------------COUNT_QUOTES.C---------------------------------
*/
int		count_quotes(char *line);

/*
**--------------------------------EXECUTABLE.C----------------------------------
*/
void	execute(t_data data);

/*
**----------------------------------EXPORT.C------------------------------------
*/
void	export(char **arg, char ***our_env, int *env_size);

/*
**----------------------------------FT_CD.C-------------------------------------
*/
void	ft_cd(t_data data);

/*
**----------------------------------FT_ECHO.C-----------------------------------
*/
void	ft_echo(t_data data);

/*
**----------------------------------FT_EXIT.C-----------------------------------
*/
void	ft_exit(t_data data);

/*
**---------------------------------FT_PWD.C-------------------------------------
*/
void	ft_pwd(t_data data);

/*
**----------------------------------GET_ENV.C-----------------------------------
*/
char	*get_env(char **env, char *key);

/*
**------------------------------------MAIN.C------------------------------------
*/
int		main(void);

/*
**--------------------------------REDIRECTIONS.C--------------------------------
*/
int		redirection(t_data *data, char *s, char c);

/*
**-----------------------------------TOKEN.C------------------------------------
*/
void	get_token(t_data *data, char *s);

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
int		skip_doubleq(char *line);
int		skip_until_char(char *s, char c);

/*
**-------------------------------UTILS_STRING2.C--------------------------------
*/
int		count_arguments(char *s, char c);
int		count_backslash(char *line, int loc);
int		count_words(char const *s, char c);

/*
**-------------------------------UTILS_STRING3.C--------------------------------
*/
int		ft_strcmp(const char *s1, const char *s2);

/*
**--------------------------UTILS_STRING_STRJOIN.C------------------------------
*/
char	*ft_strjoin_char(char *s1, char c);
char	*ft_strjoin_free_both(char *s1, char *s2);
char	*ft_strjoin_free_s1(char *s1, char const *s2);

/*
**--------------------------UTILS_STRING_WHITESPACES.C--------------------------
*/
int		is_whitespace(char c);
void	skip_whitespaces(char **s);
int		skip_whitespaces_int(char *s);
void	skip_nonwhitespaces(char **s);
int		skip_nonwhitespaces_int(char *s);

#endif
