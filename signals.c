/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 10:10:31 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/11 10:22:28 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_output(int sig)
{
	if (sig == SIGINT)
		write(1, "\n🐶 > ", sizeof("\n🐶 > "));
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\bexit\n", 11);
		exit(0);
	}
}

void	ft_signal_handler(void)
{
	if (signal(SIGINT, &signal_output) == SIG_ERR || signal(SIGQUIT, &signal_output) == SIG_ERR)
		exit(0);
}
