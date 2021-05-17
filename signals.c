/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 10:10:31 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/17 15:57:15 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** CTRL + C == SIGINT
** CTRL + \ == SIGQUIT
** No return value
*/
void	signal_output(int sig)
{
	if (sig == SIGINT)
		write(1, "\n🐶 > ", sizeof("\n🐶 > "));
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		// write(1, "\b\b  \b\b^\\Quit\n", 13);
		// exit(0);
	}
}

/*
** CTRL + C == SIGINT
** CTRL + \ == SIGQUIT
** No return value
*/
void	ft_signal_handler(void)
{
	if (signal(SIGINT, &signal_output) == SIG_ERR
	|| signal(SIGQUIT, &signal_output) == SIG_ERR)
		exit(0);
}
