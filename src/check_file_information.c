/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_information.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 12:14:57 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/07 18:19:29 by tessa         ########   odam.nl         */
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

static int	check_in_dir(char *file, char *dir)
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

e_file	check_bin_and_usr_bin(char *file)
{
	int	bin;
	int	usr_bin;

	bin = check_in_dir(file, "/bin/");
	if (bin == -1)
		return (FILE_ERROR);
	else if (bin == 1)
		return (BIN);
	usr_bin = check_in_dir(file, "/usr/bin/");
	if (usr_bin == -1)
		return (FILE_ERROR);
	else if (usr_bin == 1)
		return (USR_BIN);
	return (NOT_FOUND);
}

/*
**	Checks the file status of the executable
**	Files in the /bin/ or /usr/bin/ directory and regular files can be executed
**	Prints error messages and sets exit status if a file cannot be executed
**	Returns an enum with file information
*/

static e_file	handle_file_status(t_data *data, e_file file_status, char *file)
{
	if (file_status == FILE_ERROR)
		print_error(data, 1, make_array("🐶 > ", file, ": ", strerror(errno)));
	else if (file_status == DIRECTORY)
		print_error(data, 126, make_array("🐶 > ", file,
				": Is a directory", NULL));
	else if (file_status == NO_SUCH_FILE)
		print_error(data, 127, make_array("🐶 > ", file,
				": No such file or directory", NULL));
	else if (file_status == NOT_EXECUTABLE)
		print_error(data, 126, make_array("🐶 > ", file, ": ", strerror(errno)));
	else if (file_status == NOT_FOUND)
		print_error(data, 127, make_array(file, ": command not found", NULL,
				NULL));
	else if (file_status == PERMISSION_DENIED)
		print_error(data, 126, make_array("🐶 > ", file,
				": Permission denied", NULL));
	return (file_status);
}

/*
**	Checks the file status of the executable
**	Checks if the file can be found in /bin/ or /usr/bin/
**	Uses stat and mode_t to get more information about the file
**	Returns an enum with file information
*/

e_file	check_file_information(t_data *data, char *file)
{
	struct stat	sb;
	e_file		file_status;

	if (!ft_strchr(file, '/'))
		file_status = check_bin_and_usr_bin(file);
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
	return (handle_file_status(data, file_status, file));
}
