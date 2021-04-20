/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 12:06:59 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/04/12 15:37:47 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_export_edgecase(char *arg, char **ret)
{
	int		i;

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

static int	handle_redirection(t_data *data, char **arg, int i)
{
	char	*filename;
	int		fd;

	filename = arg[i + 1];
	if (!ft_strcmp(arg[i], ">\0"))
		fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else if (!ft_strcmp(arg[i], ">>\0"))
		fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0644);
	else if (!ft_strcmp(arg[i], "<\0"))
		fd = open(filename, O_RDONLY);
	else if (!ft_strcmp(arg[i], "<>\0"))
	{
		fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			exit(1);
		close(fd);
		fd = 0;
	}
	if (fd == -1)
		exit(1);
	data->our_fd[1] = fd;
	printf("our fd = %d\n", data->our_fd[1]);
	return (1);
}

static int	get_new_size(char **arg)
{
	int		i;
	int		size;

	size = 0;
	while (arg[size])
		size++;
	i = 0;	
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "<\0") || !ft_strcmp(arg[i], ">\0") || !ft_strcmp(arg[i], ">>\0") || !ft_strcmp(arg[i], "<>\0"))
		{
			size -= 2;
			i++;
		}
		i++;
	}
	return (size);
}

char		**final_arg(t_data *data, t_token *token)
{
	char	**ret;
	int		i;
	int		size;

	size = get_new_size(token->arg);
	ret = malloc(sizeof(char*) * (size + 2));
	if (!ret)
		exit(1);
	ret[0] = ft_strdup(token->cmd);
	i = 0;
	while (token->arg[i])
	{
		if (!ft_strcmp(token->arg[i], "<\0") || !ft_strcmp(token->arg[i], ">\0") || !ft_strcmp(token->arg[i], ">>\0") || !ft_strcmp(token->arg[i], "<>\0"))
			i += handle_redirection(data, token->arg, i);
		else
		{
			if (!ft_strcmp(ret[0], "export"))
				handle_export_edgecase(token->arg[i], &ret[i + 1]);
			else
				ret[i + 1] = ft_strdup(token->arg[i]);
		}
		i++;
	}
	ret[size + 1] = NULL;
	return (ret);
}
