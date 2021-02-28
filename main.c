/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/28 12:57:46 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cody_catch(t_list *token, t_data data)
{
	t_list			*temp;

	temp = token;
	while (temp)
	{
		if (!ft_strncmp(((t_token*)temp->content)->cmd, "exit", 4))
			exit(0);
		else if (!ft_strncmp(((t_token*)temp->content)->cmd, "pwd", 3))
			pwd();
		else if (!ft_strncmp(((t_token*)temp->content)->cmd, "cd ", 2))
			cd(((t_token*)temp->content)->arg);
		else if (!ft_strncmp(((t_token*)temp->content)->cmd, "./", 2) || !ft_strncmp(((t_token*)temp->content)->cmd, "/", 1) || !ft_strncmp(((t_token*)temp->content)->cmd, "..", 2))
			execute(((t_token*)temp->content)->cmd, data);
		else if (!ft_strncmp(((t_token*)temp->content)->cmd, "echo", 4))
			ft_echo(((t_token*)temp->content)->arg);
		temp = temp->next;
	}
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
	t_data		data;
	t_list		*token;	
	int			i;

	token = NULL;
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
		get_token(data.input, &token);
		cody_catch(token, data);
		ft_lstclear(&token, free_token);
		free(data.input);
		data.input = NULL;
	}
}
