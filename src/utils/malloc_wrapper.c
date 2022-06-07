/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_wrapper.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 18:44:20 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/06/07 16:05:41 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Checks the return value of a function which used malloc
**	If the memory allocation was unsuccessful
**		- an error message is printed
**		- the program exits with exit status 1
**	Returns the return value of the function which used malloc as a void * ...
**	... if memory allocation was successful
*/

void	*malloc_guard(void *ret)
{
	if (ret == NULL)
		print_error_exit(1, make_array(strerror(errno), NULL, NULL, NULL));
	return (ret);
}

/*
**	Memory allocation that is checked for failure
**	Checks the return value of malloc by calling malloc guard
**	Returns a void * to the address on which "size" amount of bytes was ...
**	... allocated by malloc in case memory allocation was successful
**	Exits the program in malloc guard if memory allocation was unsuccessful
*/

void	*ft_malloc(size_t size)
{
	return (malloc_guard(malloc(size)));
}
