/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hello_world.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 11:33:09 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/08 15:40:30 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char **argv)
{
	int i = 1;

	argc--;
	while (argc)
	{
		printf("%s\n", argv[i]);
		i++;
		argc--;
	}
	return (0);
}
