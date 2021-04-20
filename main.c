/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/24 13:26:57 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**TO DO:
**	- Make command history
**	- Make signal handler
*/

#include "minishell.h"

typedef enum
{
		NONE = -1,
		CD = 0,
		ECHO = 1,
		ENV = 2,
		EXIT = 3,
		EXPORT = 4,
		PWD = 5,
		UNSET = 6,
}		builtin;

typedef void (*f_builtin)(t_data *data);

static void	signal_output(int sig)
{
	if (sig == SIGINT)
		write(1, "\n🐶 > ", sizeof("\n🐶 > "));
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\bexit\n", 11);
		exit(0);
	}
}

static void	ft_signal_handler(void)
{
	if (signal(SIGINT, &signal_output) == SIG_ERR || signal(SIGQUIT, &signal_output) == SIG_ERR)
		exit(0);
}

//could maybe just make a function seperately and use ft_lstiter
static void	cody_catch(t_data *data)
{
	builtin		cmd;
	f_builtin	builtin[7];

	builtin[0] = ft_cd;
    builtin[1] = ft_echo;
    builtin[2] = ft_env;
    builtin[3] = ft_exit;
    builtin[4] = ft_export;
    builtin[5] = ft_pwd;
    builtin[6] = ft_unset;

	data->start = data->token;
	while (data->token)
	{
		if (!ft_strcmp(((t_token*)data->token->content)->cmd, "cd"))
			cmd = CD;
		else if (!ft_strcmp(((t_token*)data->token->content)->cmd, "echo"))
			cmd = ECHO;
		else if (!ft_strcmp(((t_token*)data->token->content)->cmd, "env"))
			cmd = ENV;
		else if (!ft_strcmp(((t_token*)data->token->content)->cmd, "exit"))
			cmd = EXIT;
		else if (!ft_strcmp(((t_token*)data->token->content)->cmd, "export"))
			cmd = EXPORT;
		else if (!ft_strcmp(((t_token*)data->token->content)->cmd, "pwd"))
			cmd = PWD;
		else if (!ft_strcmp(((t_token*)data->token->content)->cmd, "unset"))
			cmd = UNSET;
		else
			cmd = NONE;
		if (cmd != NONE)
			builtin[cmd](data);
		else
			execute(data);
		data->token = data->token->next;
	}
}

static void	initialize_env(char ***our_env, int *env_size)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	*our_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		(*our_env)[i] = ft_strdup(environ[i]);
		i++;
	}
	(*our_env)[i] = NULL;
	(*env_size) = i;
}

int	main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	printf("Welcome to the amazing Codyshell!\n");
	initialize_env(&data.our_env, &data.env_size);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		write(1, "🐶 > ", sizeof("🐶 > "));
		ft_signal_handler();
		data.r = get_next_line(0, &data.input);
		if (data.r == -1)
			exit(1);
		data.fd_count = 0;
		get_token(&data, data.input);
		ft_lstiter(data.token, print_token);
		cody_catch(&data);
		ft_lstclear(&data.start, free_token);
		free(data.input);
		data.input = NULL;
	}
}
