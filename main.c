/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/28 12:26:34 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** T
** added tokens so I think we can remove the stuff commented out below our main
*/

#include "minishell.h"

static void	cody_catch(t_list *token)
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
			execute(((t_token*)temp->content)->cmd);
		else if (!ft_strncmp(((t_token*)temp->content)->cmd, "echo", 4))
			ft_echo(((t_token*)temp->content)->arg);
		temp = temp->next;
	}
}

int			main(void)
{
	t_data	data;
	t_list	*token;

	token = NULL;
	ft_bzero(&data, sizeof(data));
	printf("Welcome to the amazing Codyshell!\n");
	while (1)
	{
		write(1, "🐶 > ", sizeof("🐶 > "));
		data.r = get_next_line(0, &data.input);
		if (data.r == -1)
			exit(1);		
		get_token(data.input, &token);
		cody_catch(token);
		ft_lstclear(&token, free_token);
		free(data.input);
		data.input = NULL;
	}
}




		// if (!ft_strncmp(data.input, "exit", 4) && ft_strlen(data.input) == 4)
		// 	exit(0);
		// if (!ft_strncmp(data.input, "pwd", 3) && ft_strlen(data.input) == 3)
		// 	pwd();
		// if (!ft_strncmp(data.input, "cd ", 3) && count_words(data.input, ' ') == 2)
		// 	cd(data.input);
		// if (!ft_strncmp(data.input, "./", 2) || !ft_strncmp(data.input, "/", 1) || !ft_strncmp(data.input, "..", 2))
		// 	execute(data.input);
		// if (!ft_strncmp(data.input, "echo", 4))
		// 	ft_echo(data.input);