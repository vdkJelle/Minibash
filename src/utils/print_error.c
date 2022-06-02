/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/04 16:13:17 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/01 14:40:17 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Prints the error message to STDERR using strerror(errno)
** Returns -1
*/

int	print_errno_int(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

/*
** Prints the error message to STDERR using strerror(errno)
** No return value
*/

void	print_errno(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}


char	**make_array(char *s1, char *s2, char *s3, char *s4)
{
	char	**ret;
	int		count;

	count = 1;
	if (s2)
		count++;
	if (s3)
		count++;
	if (s4)
		count++;
	ret = ft_malloc(sizeof(char *) * (count + 1));
	ret[count] = NULL;
	ret[0] = malloc_guard(ft_strdup(s1));
	if (s2)
		ret[1] = malloc_guard(ft_strdup(s2));
	if (s3)
		ret[2] = malloc_guard(ft_strdup(s3));
	if (s4)
		ret[3] = malloc_guard(ft_strdup(s4));
	return (ret);
}

/*
** Prints the error message and exists the program
** No return value
*/

void	print_error_exit(int exit_status, char **messages)
{
	int	i;

	i = 0;
	while (messages[i])
	{
		ft_putstr_fd(messages[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	exit(exit_status);
}

/*
** Prints the error message to STDERR and sets the exit status
** No return value
*/

void	print_error(t_data *data, int exit_status, char **messages)
{
	int	i;

	i = 0;
	while (messages[i])
	{
		ft_putstr_fd(messages[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	data->exit_status = exit_status;
	free_array(messages);
}
