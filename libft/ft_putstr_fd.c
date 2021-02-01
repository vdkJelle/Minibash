/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 10:36:08 by jelvan-d      #+#    #+#                 */
/*   Updated: 2019/11/05 10:36:27 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstr_fd(char *s, int fd)
{
	int i;

	if (s == 0)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
