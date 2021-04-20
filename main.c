/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/04/13 12:52:29 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static builtin	cody_catch_cmd(char *s)
// {
// 	builtin	cmd;

// 	if (!ft_strcmp(s, "cd") || !ft_strcmp(s, "/usr/bin/cd"))
// 		cmd = CD;
// 	else if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "/usr/bin/echo"))
// 		cmd = ECHO;
// 	else if (!ft_strcmp(s, "env") || !ft_strcmp(s, "/usr/bin/env"))
// 		cmd = ENV;
// 	else if (!ft_strcmp(s, "exit") || !ft_strcmp(s, "/usr/bin/exit"))
// 		cmd = EXIT;
// 	else if (!ft_strcmp(s, "export") || !ft_strcmp(s, "/usr/bin/export"))
// 		cmd = EXPORT;
// 	else if (!ft_strcmp(s, "pwd") || !ft_strcmp(s, "/usr/bin/pwd"))
// 		cmd = PWD;
// 	else if (!ft_strcmp(s, "unset") || !ft_strcmp(s, "/usr/bin/unset"))
// 		cmd = UNSET;
// 	else
// 		cmd = NONE;
// 	return (cmd);
// }

//send arg to execute and f_builtin?
static void		cody_catch(t_data *data)
{
	// builtin		cmd;
	// f_builtin	builtin[7];
	t_list		*cur;
	t_list		*prev;

	// builtin[0] = ft_cd;
    // builtin[1] = ft_echo;
    // builtin[2] = ft_env;
    // builtin[3] = ft_exit;
    // builtin[4] = ft_export;
    // builtin[5] = ft_pwd;
    // builtin[6] = ft_unset;
	cur = data->token;
	prev = NULL;
	while (cur)
	{
		if ((((t_token*)cur->content)->cop[0] == '|'))
			printf("cur is pipe\n");
		if (prev && ((t_token*)prev->content)->cop[0] == '|')
			printf("prev is pipe\n");
		// data->arg = final_arg(data, ((t_token*)cur->content));
		// cmd = cody_catch_cmd(data->arg[0]);
		// if (cmd == NONE && !check_command(data, data->arg[0]))
		// 	execute(*data);
		// else if (cmd != NONE)
		// 	builtin[cmd](data);
		execute(data, ((t_token*)cur->content));
		prev = cur;
		// free_array(data->arg);
		cur = cur->next;
	}
}

//malloc needs to be protected
static void		initialize_env(char ***our_env, int *env_size)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	*our_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*our_env))
		exit(1);
	i = 0;
	while (environ[i])
	{
		(*our_env)[i] = ft_strdup(environ[i]);
		if (!((*our_env)[i]))
			exit(1);
		i++;
	}
	(*our_env)[i] = NULL;
	(*env_size) = i;
}

int				main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	printf("Welcome to the amazing Codyshell!\n");
	initialize_env(&data.our_env, &data.env_size);
	while (1)
	{
		write(1, "🐶 > ", sizeof("🐶 > "));
		data.r = get_next_line(0, &data.input);
		if (data.r == -1)
			exit(1);
		data.our_fd[0] = 0;
		data.our_fd[1] = 1;
		get_token(&data, data.input);
		ft_lstiter(data.token, print_token);
		if (!check_token(&data))
			cody_catch(&data);
		ft_lstclear(&data.token, free_token);
		free(data.input);
		data.input = NULL;
	}
}
