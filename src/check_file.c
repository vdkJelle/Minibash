/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 12:14:57 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/18 19:07:21 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Utility function that closes the directory opened with opendir
** Called when something went wrong with readdir
** Returns -1 and prints errno
*/

static int	closedir_error(DIR **dir_p)
{
	if (closedir(*dir_p) == -1)
		return (print_errno_int());
	return (print_errno_int());
}

/*
** Checks if the file is present in the directory
** Opens the directory and compares the filenames in the directory to our file
** Returns 0 if the file was not found in the directory
** Returns 1 if the file was found in the directory
** Returns -1 if an error occured
*/

static int	check_in_dir(char *s, char *dir)
{
	struct dirent	*dir_s;
	DIR				*dir_p;

	dir_p = opendir(dir);
	if (!dir_p)
		return (print_errno_int());
	errno = 0;
	dir_s = readdir(dir_p);
	if (!dir_s && errno)
		closedir_error(&dir_p);
	while (dir_s)
	{
		if (!ft_strcmp(s, dir_s->d_name))
		{
			if (closedir(dir_p) == -1)
				return (print_errno_int());
			return (1);
		}
		dir_s = readdir(dir_p);
		if (!dir_s && errno)
			closedir_error(&dir_p);
	}
	if (closedir(dir_p) == -1)
		return (print_errno_int());
	return (0);
}

/*
** Checks if the file is present in the /bin/ or /usr/bin/ directory exists
** Uses check_in_dir
** If a command doesn't have a '/' and is not present in /bin/ or /usr/bin
**		it cannot be found
** Returns an enum with the type of file or an error
*/

e_file		check_bin(t_data *data, char *s)
{
	int		bin;
	int		usr_bin;
	
	bin = check_in_dir(s, "/bin/");
	if (bin == -1)
		return (ERROR);
	else if (bin == 1)
		return (BIN);
	usr_bin = check_in_dir(s, "/usr/bin/");
	if (usr_bin == -1)
		return (ERROR);
	else if (usr_bin == 1)
		return (USR_BIN);
	print_error(data, 127, 2, s, ": command not found");
	return (NOT_FOUND);
}

/*
** Checks if the file status of the executable
** Files in the /bin/ or /usr/bin/ directory and regular files can be executed
** Returns the type of file or an error
*/

e_file		check_file(t_data *data, char *s)
{
	struct stat sb;

	if (!ft_strchr(s, '/'))
		return (check_bin(data, s));
	if (stat(s, &sb) == -1)
	{
		if (ENOENT)
		{
			print_error(data, 127, 3, "🐶 > ", s, ": No such file or directory");
			return (NOT_FOUND);
		}
		print_error(data, 126, 4, "🐶 > ", s, ": ", strerror(errno));
		return (NOT_EXECUTABLE);
	}
	if (!(sb.st_mode & S_IXUSR))
	{
		print_error(data, 126, 3, "🐶 > ", s, ": Permission denied");
		return (NOT_EXECUTABLE);
	}
	if ((sb.st_mode & S_IFMT) == S_IFREG)
		return (REGULAR);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
	{
		print_error(data, 126, 3, "🐶 > ", s, ": Is a directory");
		return (DIRECTORY);
	}
	return (ERROR);
}


// e_file		check_file(t_data *data, char *s)
// {
// 	int		len;
// 	e_file	file;

// 	len = ft_strlen(s);	
// 	if (check_in_dir(s, "/bin/") == 1)
// 		file = BIN;
// 	else if (check_in_dir(s, "/usr/bin/") == 1)
// 		file = USR_BIN;
// 	else if (s && len > 0 && s[len - 1] == '/' && check_if_valid_dir(s) == 1)
// 		file = DIRECTORY;
// 	else if (s && len > 0 && s[len - 1] == '/' && check_if_valid_dir(s) == -1)
// 		file = NO_FILE;
// 	else if (!ft_strchr(s, '/'))
// 		file = NOT_FOUND;
// 	else
// 		file = STANDARD;
// 	if (file == DIRECTORY)
// 		print_error(data, 126, 3, "🐶 > ", s, ": Is a directory");
// 	else if (file == NO_FILE)
// 		print_error(data, 126, 3, "🐶 > ", s, ": No such file or directory");
// 	else if (file == NOT_FOUND)
// 		print_error(data, 126, 2, s, ": command not found");
// 	return (file);
// }

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
// 	// char	*file;
// 	// char	*dir;
// 	int		end;
// 	int		start_file;

// 	end = ft_strlen(s);
// 	start_file = -1;
// 	while (end > 0)
// 	{
// 		if (s[end] == '/')
// 		{
// 			start_file = end + 1;
// 			break ;
// 		}
// 		end--;
// 	}
// 	// if (start_file > -1)
// 	// {
// 	// 	// file = ft_substr(s, start_file, ft_strlen(s) - start_file);
// 	// 	// dir = ft_substr(s, 0, start_file);
// 	// 	// printf("file = %s\tdir = %s\n", file, dir);
// 	// 	// if (!file || !dir)
// 	// 	// 	exit(1);
// 	// 	// return (check_in_dir(file, dir));
// 	// }
// 	if (start_file == -1)
// 		return (1);
// 	else
// 		return (0);
// }