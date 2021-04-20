/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 12:14:57 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/04/20 14:38:22 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	check_if_valid_dir(char *dir)
{
	struct dirent	*dir_s;
	DIR				*dir_p;

	dir_p = opendir(dir);
	if (!dir_p)
		return (-1);
	errno = 0;
	dir_s = readdir(dir_p);
	if (!dir_s && errno)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (-1);
	}
	if (dir)
		return (1);
	return (0);
}

static int	check_in_dir(char *s, char *dir)
{
	struct dirent	*dir_s;
	DIR				*dir_p;

	dir_p = opendir(dir);
	if (!dir_p)
		return (-1);
	errno = 0;
	dir_s = readdir(dir_p);
	if (!dir_s && errno)
		return (-1); // handle error
	while (dir_s)
	{
		if (!ft_strcmp(s, dir_s->d_name))
		{
			if (closedir(dir_p) == -1)
				return (-1); // handle error
			return (1);
		}
		dir_s = readdir(dir_p);
	}
	if (closedir(dir_p) == -1)
		return (-1); // handle error
	return (0);
}

int			check_command(t_data *data, char *s)
{
	command	cmd;
	
	if (check_in_dir(s, "/bin/") == 1)
		cmd = BIN;
	else if (check_in_dir(s, "/usr/bin/") == 1)
		cmd = USR_BIN;
	else if (s && s[ft_strlen(s) - 1] == '/' && check_if_valid_dir(s) == 1)
		cmd = DIRECTORY;
	else if (!ft_strchr(s, '/'))
		cmd = NOT_FOUND;
	else
		cmd = STANDARD;
	if (cmd == DIRECTORY)
	{
		ft_putstr_fd("🐶 > ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		(void)data; /*add exit status ? here */
		return (1);
	}
	if (cmd == NOT_FOUND)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": command not found\n", 2);
		(void)data; /*add exit status 127 here */
		return (1);
	}
	return (0);
}

// int			check_command(t_data *data, char *s)
// {
// 	int		ret;

// 	ret = 1;
// 	if (s && s[ft_strlen(s) - 1] == '/')
// 	{
// 		ft_putstr_fd("🐶 > ", 2);
// 		ft_putstr_fd(s, 2);
// 		ft_putstr_fd(": Is a directory\n", 2);
// 		(void)data; /*add exit status ? here */
// 		return (1);
// 	}
// 	if (ret == 1)
// 		ret = check_in_dir(s, "/bin");
// 	if (ret == 1)
// 		ret = check_in_dir(s, "/usr/bin/");
// 	if (ret == 1)
// 		ret = check_executable(s);
// 	if (ret == -1)
// 	{
// 		ft_putstr_fd(strerror(errno), 2);
// 		(void)data; /*add exit status 1 here */
// 		return (-1);
// 	}
// 	if (ret == 1)
// 	{
// 		ft_putstr_fd(s, 2);
// 		ft_putstr_fd(": command not found\n", 2);
// 		(void)data; /*add exit status 127 here */
// 		return (1);
// 	}
// 	return (0);
// }

// int			check_executable(char *s)
// {
// 	// char	*cmd;
// 	// char	*dir;
// 	int		end;
// 	int		start_cmd;

// 	end = ft_strlen(s);
// 	start_cmd = -1;
// 	while (end > 0)
// 	{
// 		if (s[end] == '/')
// 		{
// 			start_cmd = end + 1;
// 			break ;
// 		}
// 		end--;
// 	}
// 	// if (start_cmd > -1)
// 	// {
// 	// 	// cmd = ft_substr(s, start_cmd, ft_strlen(s) - start_cmd);
// 	// 	// dir = ft_substr(s, 0, start_cmd);
// 	// 	// printf("cmd = %s\tdir = %s\n", cmd, dir);
// 	// 	// if (!cmd || !dir)
// 	// 	// 	exit(1);
// 	// 	// return (check_in_dir(cmd, dir));
// 	// }
// 	if (start_cmd == -1)
// 		return (1);
// 	else
// 		return (0);
// }