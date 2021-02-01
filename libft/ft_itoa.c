/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 11:49:32 by jelvan-d      #+#    #+#                 */
/*   Updated: 2019/11/13 15:28:46 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*result(char *str, int nc, long num, int sign)
{
	str[nc] = '\0';
	while (nc > 0)
	{
		str[nc - 1] = (num % 10) + '0';
		num /= 10;
		nc--;
	}
	if (sign)
		str[nc] = '-';
	return (str);
}

static int	numcount(long n)
{
	int nc;

	nc = 1;
	if (n < 0)
	{
		nc++;
		n *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		nc++;
	}
	return (nc);
}

char		*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		sign;
	int		nc;

	num = n;
	nc = numcount(num);
	sign = 0;
	str = malloc(sizeof(char) * nc + 1);
	if (str == 0)
		return (0);
	if (num < 0)
	{
		num *= -1;
		sign = 1;
	}
	str = result(str, nc, num, sign);
	return (str);
}
