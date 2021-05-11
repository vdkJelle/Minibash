/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 12:06:59 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/10 20:02:27 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup(char **p, int pi)
{
	int	i;

	i = 0;
	while (i < pi)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

static int	append_arg(char *arg, char **ret, char *cmd)
{
	int		i;

	if (!ft_strcmp(cmd, "export"))
	{
		i = skip_until_char_incl(arg, '=');
		*ret = ft_substr(arg, 0, i);
		while (arg[i])
		{
			if (arg[i] == '\\')
				*ret = ft_strjoin_free_s1(*ret, "\\\\");
			else
				*ret = ft_strjoin_char(*ret, arg[i]);
			i++;
		}
	}
	else
	{
		*ret = ft_strdup(arg);
		if (!(*ret))
			exit (1);
	}
	return (1);
}

static int	handle_redirection(t_data *data, t_word **arg, int i, int fd[2])
{
	if (!ft_strcmp(arg[i]->word, ">\0"))
	{
		if (fd[1] != -2)
		{
			if (close(fd[1]) == -1)
				return (print_errno_int());
		}
		fd[1] = open(arg[i + 1]->word, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	else if (!ft_strcmp(arg[i]->word, ">>\0"))
	{
		if (fd[1] != -2)
		{
			if (close(fd[1]) == -1)
				return (print_errno_int());
		}
		fd[1] = open(arg[i + 1]->word, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	else if (!ft_strcmp(arg[i]->word, "<\0"))
	{
		if (fd[0] != -2)
		{
			if (close(fd[0]) == -1)
				return (print_errno_int());
		}
		fd[0] = open(arg[i + 1]->word, O_RDONLY);
	}	
	if (fd[0] == -1 || fd[1] == -1)
	{
		data->exit_status = 1;
		ft_putstr_fd("🐶 > ", 2);
		ft_putstr_fd(arg[i + 1]->word, 2);
		ft_putstr_fd(": ", 2);
		return (print_errno_int());
	}
	printf("fd in = %d\n", fd[0]);
	printf("fd out = %d\n", fd[1]);
	return (0);
}

static int	get_new_size(t_word **arg)
{
	int		i;
	int		size;

	size = 0;
	while (arg[size])
		size++;
	i = 0;	
	while (arg[i])
	{
		if (is_redirection(arg[i]->word) && arg[i]->metacharacter == 1)
		{
			size -= 2;
			i++;
		}
		i++;
	}
	return (size);
}

void		final_args(t_data *data, t_token *token, t_execute *exec)
{
	int		i;
	int		j;

	exec->args = malloc(sizeof(char *) * (get_new_size(token->arg) + 2));
	if (!exec->args)
		exit(1);
	exec->args[0] = ft_strdup(token->cmd->word);
	if (!exec->args[0])
		exit(1);
	i = 0;
	j = 1;
	while (token->arg[i])
	{
		if (is_redirection(token->arg[i]->word) && token->arg[i]->metacharacter == 1)
		{
			if (handle_redirection(data, token->arg, i, exec->fd) == -1)
				return (cleanup(exec->args, j));
			i++;
		}
		else
			j += append_arg(token->arg[i]->word, &exec->args[j], exec->args[0]);
		i++;
	}
	exec->args[j] = NULL;
}
