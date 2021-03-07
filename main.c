/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/03/07 20:00:22 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum
{
		NONE = -1,
		CD = 0,
		ECHO = 1,
		// ENV,
		EXIT = 2,
		// EXPORT,
		PWD = 3,
		// UNSET,
}		builtin;

typedef void (*f_builtin)(t_data data);

//could maybe just make a function seperately and use ft_lstiter
static void	cody_catch(t_data data)
{
	t_list		*start;
	builtin		cmd;
	f_builtin	builtin[4];

	builtin[0] = ft_cd;
    builtin[1] = ft_echo;
    // builtin[2] = ft_env;
    builtin[2] = ft_exit;
    // builtin[4] = ft_export;
    builtin[3] = ft_pwd;
    // builtin[6] = ft_unset;

	start = data.token;
	while (data.token)
	{
		if (!ft_strcmp(((t_token*)data.token->content)->cmd, "cd"))
			cmd = CD;
		// cd(((t_token*)data.token->content)->arg);
		else if (!ft_strcmp(((t_token*)data.token->content)->cmd, "echo"))
			cmd = ECHO;
		// 	echo(((t_token*)data.token->content)->arg, data.our_env);
		// // else if (!ft_strcmp(((t_token*)data.token->content)->cmd, "env"))
		// // 	envstuff
		else if (!ft_strcmp(((t_token*)data.token->content)->cmd, "exit"))
			ft_exit(data);
		// // else if (!ft_strcmp(((t_token*)data.token->content)->cmd, "export"))
		// // 	exportstuff
		else if (!ft_strcmp(((t_token*)data.token->content)->cmd, "pwd"))
			cmd = PWD;
		// 	pwd();
		// // else if (!ft_strcmp(((t_token*)data.token->content)->cmd, "unset"))
		// // 	unsetstuff
		// else
		// 	execute(((t_token*)data.token->content)->cmd, data);
		else
			cmd = NONE;
		if (cmd != -1)
			builtin[cmd](data);
		else
			execute(data);
		data.token = data.token->next;
	}
	data.token = start;
}

static void	initialize_env(char ***our_env)
{
	int i;

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
}

int	main(void)
{
	t_data	data;
	int		i;

	ft_bzero(&data, sizeof(data));
	printf("Welcome to the amazing Codyshell!\n");
	initialize_env(&data.our_env);
	i = 0;
	while (1)
	{
		write(1, "🐶 > ", sizeof("🐶 > "));
		data.r = get_next_line(0, &data.input);
		if (data.r == -1)
			exit(1);
		data.fd_count = 0;
		get_token(&data, data.input);
		ft_lstiter(data.token, print_token);
		cody_catch(data);
		ft_lstclear(&data.token, free_token);
		free(data.input);
		data.input = NULL;
	}
}
