/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_information.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 12:14:57 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/06 18:20:22 by tessa         ########   odam.nl         */
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

e_file	check_bin(t_data *data, char *s)
{
	int	bin;
	int	usr_bin;
	
	bin = check_in_dir(s, "/bin/");
	if (bin == -1)
		return (FILE_ERROR);
	else if (bin == 1)
		return (BIN);
	usr_bin = check_in_dir(s, "/usr/bin/");
	if (usr_bin == -1)
		return (FILE_ERROR);
	else if (usr_bin == 1)
		return (USR_BIN);
	print_error(data, 127, make_array(s, ": command not found", NULL, NULL));
	return (NOT_FOUND);
}

/*
** Checks if the file status of the executable
** Files in the /bin/ or /usr/bin/ directory and regular files can be executed
** Returns the type of file or an error
*/

e_file	check_file(t_data *data, char *s)
{
	struct stat sb;

	if (!ft_strchr(s, '/'))
		return (check_bin(data, s));
	if (stat(s, &sb) == -1)
	{
		if (ENOENT)
		{
			print_error(data, 127, make_array("🐶 > ", s,
				": No such file or directory", NULL));
			return (NOT_FOUND);
		}
		print_error(data, 126, make_array("🐶 > ", s, ": ", strerror(errno)));
		return (NOT_EXECUTABLE);
	}
	if (!(sb.st_mode & S_IXUSR))
	{
		print_error(data, 126, make_array("🐶 > ", s, ": Permission denied",
			NULL));
		return (NOT_EXECUTABLE);
	}
	if ((sb.st_mode & S_IFMT) == S_IFREG)
		return (REGULAR);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
	{
		print_error(data, 126, make_array("🐶 > ", s, ": Is a directory",
			NULL));
		return (DIRECTORY);
	}
	return (FILE_ERROR);
}
