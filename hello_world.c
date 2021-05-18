/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hello_world.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 11:33:09 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/14 16:18:02 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	argc--;
	while (argc)
	{
		printf("%s\n", argv[i]);
		i++;
		argc--;
	}
	while (1) {}
	return (0);
}
