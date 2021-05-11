/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/11 23:23:21 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_execute	*initialize_exec(t_data *data, t_token *token)
{
	t_execute	*exec;

	exec = malloc(sizeof(t_execute));
	if (!exec)
		exit(1);	
	ft_bzero(exec, sizeof(*exec));
	if (token->cop[0] == '|')
	{
		if (pipe(exec->p_fd) == -1)
		{
			data->exit_status = 1;
			print_errno_int();
			return (NULL);
		}
		printf("pipe read = %d\tpipe write = %d\n", exec->p_fd[0], exec->p_fd[1]);
		exec->piped = 1;
	}
	exec->fd[0] = -2;
	exec->fd[1] = -2;
	final_args(data, token, exec);
	if (!exec->args)
		return (NULL);
	return (exec);
}

static void	cody_catch(t_data *data)
{
	t_list		*temp;
	t_execute	*cur;
	t_execute	*prev;
	t_execute	*temp_exec;

	prev = NULL;
	temp = data->token;
	while (temp)
	{
		cur = initialize_exec(data, (t_token*)temp->content);
		if (!cur)
			return ;
		if (execute(data, cur, prev) == -1)
			return ;
		temp_exec = prev;
		prev = cur;
		if (temp_exec)
		{
			free_array(temp_exec->args);
			free(temp_exec);
		}
		temp = temp->next;
		if (!temp)
		{
			free_array(cur->args);
			free(cur);
		}
	}
}

static void		handle_shlvl(char ***our_env, int *env_size)
{
	char 	*shlvl;
	char	*temp;
	int		i;
	int		n;
	
	shlvl = get_env(*our_env, "SHLVL");
	if (!shlvl)
		temp = ft_strdup("SHLVL=1");
	else
	{
		i = 0;
		while (shlvl[i] && ft_isdigit(shlvl[i]))
			i++;
		if (shlvl[i] != '\0')
			temp = ft_strdup("SHLVL=1");
		else
		{
			n = ft_atoi(shlvl) + 1;
			temp = ft_strjoin_free_both(ft_strdup("SHLVL="), ft_itoa(n));
		}
	}
	if (!temp)
		exit(1);
	append_key_value(temp, our_env, env_size);
	free(temp);
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
	handle_shlvl(our_env, env_size);
}

int				main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	ft_putstr_fd("Welcome to the amazing Codyshell!\n", 1);
	initialize_env(&data.our_env, &data.env_size);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		write(1, "🐶 > ", sizeof("🐶 > "));
		ft_signal_handler();
		data.r = get_next_line(0, &data.input);
		if (data.r == -1)
			exit(1);
		get_token(&data, data.input);
		// ft_lstiter(data.token, print_token);
		if (!check_token(&data))
			cody_catch(&data);
		else
			data.exit_status = 1;
		ft_lstclear(&data.token, free_token);
		free(data.input);
		data.input = NULL;
	}
	return (0);
}
