/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/04/20 14:06:24 by tevan-de      ########   odam.nl         */
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

// # define STDIN 0
// # define STDOUT 1
// # define READ 0
// # define WRITE 1

/*
**------------------------------GLOBAL VARIABLES--------------------------------
*/

/*
**------------------------------------ENUMS-------------------------------------
*/

typedef			enum
{
				STANDARD = 0,
				BIN = 1,
				USR_BIN = 2,
				DIRECTORY = 3,
				NOT_FOUND = 4,
}				command;

typedef 		enum
{
				NORMAL = 0,
				DOUBLEQUOTE = 1,
				ENVIRONMENT_VARIABLE = 2,
				METACHARACTER = 3,
				SINGLEQUOTE = 4,
				BACKSLASH = 5,
}				arg_characters;

typedef 		enum
{
				NON_BUILTIN = -1,
				CD = 0,
				ECHO = 1,
				ENV = 2,
				EXIT = 3,
				EXPORT = 4,
				PWD = 5,
				UNSET = 6,
}				builtin;

/*
**-----------------------------------STRUCTS------------------------------------
*/

typedef struct	s_token
{
	char		*cmd;
	char		**arg;
	char		*cop;
}				t_token;

typedef struct	s_data
{
	char		**arg;
	char		**our_env;
	char		*input;
	int			env_size;
	int			our_fd[2];
	int			r;
	// t_list		*start;
	t_list		*token;
}				t_data;

/*
**----------------------------POINTERS TO FUNCTIONS-----------------------------
*/

typedef int		(*f_arg_handler)(t_data *data, char **ret, char *s);
typedef void	(*f_builtin)(t_data *data);

/*
**-------------------------------COUNT_QUOTES.C---------------------------------
*/
int		count_quotes(char *line);

/*
**-----------------------------------ENV.C--------------------------------------
*/
void	ft_env(t_data *data);

/*
**--------------------------------EXECUTABLE.C----------------------------------
*/
// void	execute(t_data data);

/*
**---------------------------------EXPORT.C-------------------------------------
*/
void	ft_export(t_data *data);

/*
**----------------------------------FT_CD.C-------------------------------------
*/
void	ft_cd(t_data *data);

/*
**---------------------------------FT_ECHO.C------------------------------------
*/
void	ft_echo(t_data *data);

/*
**---------------------------------FT_EXIT.C------------------------------------
*/
void	ft_exit(t_data *data);
void	free_array(char **array);

/*
**---------------------------------FT_PWD.C-------------------------------------
*/
void	ft_pwd(t_data *data);

/*
**---------------------------------GET_ENV.C------------------------------------
*/
char	*get_env(char **env, char *key);

/*
**-----------------------------HANDLE_ARG_CHARS.C-------------------------------
*/
int		handle_char(t_data *data, char **ret, char *s);
int		handle_doublequotes(t_data *data, char **ret, char *s);
int		handle_environment_variable(t_data *data, char **ret, char *s);
int		handle_metacharacter(t_data *data, char **ret, char *s);
int		handle_singlequotes(t_data *data, char **ret, char *s);

/*
**----------------------------------MAIN.C--------------------------------------
*/
int		main(void);

/*
**--------------------------------REDIRECTION.C---------------------------------
*/
char	**final_arg(t_data *data, t_token *token);

/*
**--------------------------------TOKEN_ARG.C-----------------------------------
*/
int		get_arg(t_data *data, char **ret, char *s, char control_op);

/*
**-------------------------------TOKEN_CHECK.C----------------------------------
*/
int		check_token(t_data *data);

/*
**----------------------------------TOKEN.C-------------------------------------
*/
void	get_token(t_data *data, char *s);

/*
**------------------------------------UNSET-------------------------------------
*/
void	ft_unset(t_data *data);

/*
**--------------------------------UTILS_EXPORT.C--------------------------------
*/
void	replace_entry(char *arg, char ***our_env, int i);

/*
**--------------------------------UTILS_LIST.C----------------------------------
*/
void	free_token(void *content);
void 	print_token(void *content);

/*
**-----------------------------UTILS_STRING_SKIP.C-------------------------------
*/
int		skip_doubleq(char *line);
int		skip_until_char_excl(char *s, char c);
int		skip_until_char_incl(char *s, char c);
int		skip_whitespaces_int(char *s);
int		skip_until_metacharacter_excl(char *s);
int		skip_until_char_function(char *s, int (*ft_isthis)(char c));
// int		skip_until_metacharacter_incl(char *s);
// int		skip_chars_int(char *s, char c);
// int		skip_metacharacters_int(char *s);
// int		skip_nonwhitespaces_int(char *s);
// void	skip_char(char **s, char c);
// void	skip_chars(char **s, char c);
// void	skip_whitespaces(char **s);
// void	skip_nonwhitespaces(char **s);

/*
**-----------------------------UTILS_STRING_COUNT.C------------------------------
*/
int		count_arguments(char *s, char c);
int		count_backslash(char *line, int loc);
// int		count_words(char const *s, char c);

/*
**-------------------------------UTILS_STRING.C---------------------------------
*/
int		ft_strcmp(const char *s1, const char *s2);
// char	*put_in_singlequotes(char *s);

/*
**--------------------------UTILS_STRING_STRJOIN.C------------------------------
*/
char	*ft_strjoin_char(char *s1, char c);
char	*ft_strjoin_free_both(char *s1, char *s2);
char	*ft_strjoin_free_s1(char *s1, char const *s2);

/*
**----------------------------UTILS_STRING_IS_THIS.C----------------------------
*/
int		is_control_operator(char s);
int		is_metacharacter(char c);
int		is_redirection(char *s);
int		is_whitespace(char c);

int		check_command(t_data *data, char *s);
void	execute(t_data *data, t_token *current);

#endif
