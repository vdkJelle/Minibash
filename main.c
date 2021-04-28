/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/04/28 14:51:38 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**TO DO:
**	- Make command history
**	- Make signal handler
*/

#include "minishell.h"

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

static void	cody_catch(t_data *data)
{
	t_list		*cur;
	t_list		*prev;
	t_list		*next;

	prev = NULL;
	cur = data->token;
	if (cur)
		next = cur->next;
	while (cur)
	{
		if (((t_token*)cur->content)->cop[0] == '|')
			printf("cur is pipe\n");
		if (prev && ((t_token*)prev->content)->cop[0] == '|')
			printf("prev is pipe\n");
		if (next && ((t_token*)next->content)->cop[0] == '|')
			printf("next is pipe\n");
		execute(data, ((t_token*)cur->content));
		prev = cur;
		cur = cur->next;
		if (cur)
			next = cur->next;
	}
}

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
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		write(1, "🐶 > ", sizeof("🐶 > "));
		ft_signal_handler();
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
