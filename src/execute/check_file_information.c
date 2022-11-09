/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_information.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 12:14:57 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/11/09 18:09:19 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Utility function that closes the directory opened with opendir
**	Called when something went wrong with readdir
**	Returns -1 and prints errno
*/

static int	closedir_error(DIR **dir_p)
{
	if (closedir(*dir_p) == -1)
		return (print_errno_int());
	return (print_errno_int());
}

/*
**	Checks if the file is present in the directory
**	Opens the directory and compares the files in the directory to our file
**	Returns 0 if the file was not found in the directory
**	Returns 1 if the file was found in the directory
**	Returns -1 if an error occured
*/

int	check_in_dir(char *file, char *dir)
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
		if (!ft_strcmp(file, dir_s->d_name))
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
**	Checks if the file is present in the /bin/ or /usr/bin/ directory
**	Uses check_in_dir
**	If a command doesn't have a / and is not present in /bin/ or /usr/bin/
**		it cannot be found
**	Returns an enum with the type of file or an error
*/

static enum e_file	check_bin_and_usr_bin(t_data *data, char *file)
{
	char	**splitted_path;
	int		i;

	if (!get_env(data->our_env, "PATH"))
		return (NO_SUCH_FILE);
	splitted_path = malloc_guard(ft_split(get_env(data->our_env, "PATH"), ':'));
	i = 0;
	while (splitted_path && splitted_path[i])
	{
		if (check_in_dir(file, splitted_path[i]))
		{
			free_array(splitted_path);
			return (BIN);
		}
		i++;
	}
	free_array(splitted_path);
	return (NOT_FOUND);
}

/*
**	Checks the file status of the executable
**	Files in the /bin/ or /usr/bin/ directory and regular files can be executed
**	Prints error messages and sets exit status if a file cannot be executed
**	Returns an enum with file information
*/

static enum e_file	handle_file_status(enum e_file file_status,
	char *file)
{
	if (file_status == FILE_ERROR)
		print_error(1, make_array(SHELL, file, ": ", strerror(errno)));
	else if (file_status == DIRECTORY)
		print_error(126, make_array(SHELL, file,
				": Is a directory", NULL));
	else if (file_status == NO_SUCH_FILE)
		print_error(127, make_array(SHELL, file,
				": No such file or directory", NULL));
	else if (file_status == NOT_EXECUTABLE)
		print_error(126, make_array(SHELL, file, ": ", strerror(errno)));
	else if (file_status == NOT_FOUND)
		print_error(127, make_array(SHELL, file, ": command not found",
				NULL));
	else if (file_status == PERMISSION_DENIED)
		print_error(126, make_array(SHELL, file,
				": Permission denied", NULL));
	return (file_status);
}

/*
**	Checks the file status of the executable
**	Checks if the file can be found in /bin/ or /usr/bin/
**	Uses stat and mode_t to get more information about the file
**	Returns an enum with file information
*/

enum e_file	check_file_information(t_data *data, char *file)
{
	struct stat	sb;
	enum e_file	file_status;

	if (!ft_strchr(file, '/'))
		file_status = check_bin_and_usr_bin(data, file);
	else
	{
		if (stat(file, &sb) == -1)
		{
			if (ENOENT)
				file_status = NO_SUCH_FILE;
			else
				file_status = NOT_EXECUTABLE;
		}
		else if (!(sb.st_mode & S_IXUSR))
			file_status = PERMISSION_DENIED;
		else if ((sb.st_mode & S_IFMT) == S_IFREG)
			file_status = REGULAR;
		else if ((sb.st_mode & S_IFMT) == S_IFDIR)
			file_status = DIRECTORY;
		else
			file_status = FILE_ERROR;
	}
	return (handle_file_status(file_status, file));
}
