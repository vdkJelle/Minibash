/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/09 18:17:12 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
**----------------------------------INCLUDES------------------------------------
*/

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/*
**------------------------------GLOBAL_VARIABLES--------------------------------
*/

int	g_status_code;

/*
**-----------------------------------DEFINES------------------------------------
*/

# define READ 0
# define WRITE 1
# define NO_REDIRECTION -2

# define CHILD 0

# define PROMPT "codyshell-3.0$ "
# define SHELL "codyshell: "

/*
**------------------------------------ENUMS-------------------------------------
*/

enum e_command
{
	NON_BUILTIN = -1,
	CD = 0,
	ECHO = 1,
	ENV = 2,
	EXIT = 3,
	EXPORT = 4,
	PWD = 5,
	UNSET = 6,
	CMD_ERROR = -2,
};

enum e_file
{
	FILE_ERROR = -1,
	REGULAR = 0,
	BIN = 1,
	DIRECTORY = 2,
	NO_SUCH_FILE = 3,
	NOT_EXECUTABLE = 4,
	NOT_FOUND = 5,
	PERMISSION_DENIED = 6,
};

enum e_special_char
{
	CHAR = 0,
	DOUBLEQUOTE = 1,
	ENVIRONMENT_VARIABLE = 2,
	METACHARACTER = 3,
	SINGLEQUOTE = 4,
	BACKSLASH = 5,
};

enum e_bool
{
	FALSE = 0,
	TRUE = 1,
};

/*
**-----------------------------------STRUCTS------------------------------------
*/

typedef struct s_token
{
	char		*string;
	char		*control_operator;
}				t_token;

typedef struct s_word
{
	t_list		*word_segment;
	char		*word;
	int			metacharacter;
}				t_word;

typedef struct s_expression
{
	t_word		**arg;
	char		*control_operator;
}				t_expression;

typedef struct s_exec
{
	char		**args;
	char		*path;
	int			fd[2];
	int			p_fd[2];
	int			piped;
}				t_execute;

typedef struct s_data
{
	char		**args;
	char		**our_env;
	int			env_size;
	int			our_fd[2];
	int			pid;
	t_list		*token;
	t_list		*expression;
}				t_data;

/*
**----------------------------POINTERS TO FUNCTIONS-----------------------------
*/
typedef int		(*t_word_segment_handler)(t_data *data, t_word **word, char *s);
typedef void	(*t_builtin)(t_data *data);
/*
**------------------------------BUBBLE_SORT/CD.C--------------------------------
*/
char			**bubble_sort(char **env, int *env_size);

/*
**--------------------------------BUILTINS/CD.C---------------------------------
*/
void			ft_cd(t_data *data);
/*
**-------------------------------BUILTINS/ECHO.C--------------------------------
*/
void			ft_echo(t_data *data);
/*
**--------------------------------BUILTINS/ENV.C--------------------------------
*/
void			ft_env(t_data *data);
/*
**-------------------------------BUILTINS/EXIT.C--------------------------------
*/
void			ft_exit(t_data *data);
/*
**------------------------------BUILTINS/EXPORT.C-------------------------------
*/
void			append_key_value(char *arg, char ***our_env, int *env_size);
void			ft_export(t_data *data);
/*
**--------------------------------BUILTINS/PWD.C--------------------------------
*/
void			ft_pwd(t_data *data);
/*
**-------------------------------BUILTINS/UNSET.C-------------------------------
*/
void			ft_unset(t_data *data);

/*
**-----------------------EXECUTE/CHECK_FILE_INFORMATION.C-----------------------
*/
enum e_file		check_file_information(t_data *data, char *s);
int				check_in_dir(char *file, char *dir);

/*
**--------------------------EXECUTE/EXECUTE_BUILTIN.C---------------------------
*/
void			execute_builtin_pipe(t_data *data, enum e_command cmd,
					t_execute *exec);
void			execute_builtin_no_pipe(t_data *data, enum e_command cmd,
					t_execute *exec);
/*
**------------------------------EXECUTE/EXECUTE.C-------------------------------
*/
void			cody_catch(t_data *data);
/*
**-----------------------------EXECUTE/FINAL_ARGS.C-----------------------------
*/
void			get_final_args(t_expression *expression, t_execute *exec);
/*
**-----------------------------EXECUTE/PROCESSES.C------------------------------
*/
void			waiting_for_processes(t_data *data);
void			create_process(t_data *data, enum e_command cmd, t_execute *cur,
					t_execute *prev);
/*
**------------------------EXECUTE/REDIRECTION_HERE_DOC.C------------------------
*/
int				here_doc(char *delimiter, int fd[2]);
/*
**-----------------------------EXECUTE/REDIRECTION.C----------------------------
*/
int				redirection_check_fd(char *s, int fd[2]);
int				redirection_close_error(char *s);
int				handle_redirections(t_expression *expression,
					t_execute *exec);

/*
**----------------------TOKENIZER_AND_PARSER/CHECK_INPUT.C----------------------
*/
int				check_input(t_data *data);
/*
**---------------TOKENIZER_AND_PARSER/CHECK_MULTILINE_COMMANDS.C----------------
*/
int				check_multiline_command(char *s);
/*
**-----------------TOKENIZER_AND_PARSER/PARSER_WORD_SEGMENTS.C------------------
*/
int				handle_char(t_data *data, t_word **word, char *s);
int				handle_doublequotes(t_data *data, t_word **word, char *s);
int				handle_environment_variable(t_data *d, t_word **word, char *s);
int				handle_metacharacter(t_data *data, t_word **word, char *s);
int				handle_singlequotes(t_data *data, t_word **word, char *s);
/*
**----------------------TOKENIZER_AND_PARSER/PARSER_WORD.C----------------------
*/
int				get_word(t_data *data, t_word **word, char *s, char control_op);
/*
**------------------------TOKENIZER_AND_PARSER/PARSER.C-------------------------
*/
void			parse_all(t_data *data);
t_expression	*parse_one(t_data *data, t_token *token);

/*
**-----------------------TOKENIZER_AND_PARSER/TOKENIZER.C-----------------------
*/
void			get_token(t_data *data, char *s);

/*
**--------------------------UTILS/ENVIRONMENT_UTILS.C---------------------------
*/
void			initialize_env(char ***our_env, int *env_size);
/*
**---------------------------------UTILS/FREE2.C--------------------------------
*/
void			free_cur_prev_expression(
				t_execute *cur,
				t_execute *prev,
				t_expression *expression);
/*
**---------------------------------UTILS/FREE.C---------------------------------
*/
void			free_array(char **array);
void			free_array_part(char ***array, int i);
void			free_exec(t_execute *exec);
void			free_expression(void *content);
void			free_token(void *content);

/*
**-------------------------------UTILS/GET_ENV.C--------------------------------
*/
char			*get_env(char **env, char *key);
/*
**---------------------------------UTILS/LIST.C---------------------------------
*/
void			print_expression(void *content);
/*
**----------------------------UTILS/MALLOC_WRAPPER.C----------------------------
*/
void			*malloc_guard(void *ret);
void			*ft_malloc(size_t size);
/*
**-----------------------------UTILS/PRINT_ERROR.C------------------------------
*/
void			print_errno(void);
int				print_errno_int(void);
char			**make_array(char *s1, char *s2, char *s3, char *s4);
void			print_error_exit(int exit_status, char **messages);
void			print_error(int exit_status, char **messages);
/*
**-----------------------------UTILS/STRING_COUNT.C-----------------------------
*/
int				count_arguments(char *s, char c);
int				count_backslash(char *s, int loc);
/*
**----------------------------UTILS/STRING_IS_THIS.C----------------------------
*/
int				is_control_operator(char s);
int				is_metacharacter(char c);
int				is_redirection(char *s);
int				is_whitespace(char c);
int				ft_isdigit_char(char c);
/*
**------------------------UTILS/STRING_SKIP_CHARACTERS.C------------------------
*/
int				skip_until_next_doubleq(char *s);
int				skip_until_next_singleq(char *s);
int				skip_until_char(char *s, char c);
int				skip_while_char(char *s, int (*ft_isthis)(char c));
int				skip_while_not_char(char *s, int (*ft_isthis)(char c));
/*
**--------------------------------UTILS/STRING.C--------------------------------
*/
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strjoin_wrapper(char *s1, char *s2, int mode);
char			*get_path_from_bin(t_data *data, char *arg);

/*
**------------------------------------MAIN.C------------------------------------
*/
int				main(void);

/*
**----------------------------------SIGNALS.C-----------------------------------
*/
void			signal_output(int sig);
void			ft_signal_handler(void);

#endif
