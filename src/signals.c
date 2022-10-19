/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 10:10:31 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/10/19 11:55:48 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	CTRL + C == SIGINT
**	When the function receives a SIGINT signal, it will print the signal ...
**	... and write a new prompt
**	CTRL + \ == SIGQUIT
**	When the function receives a SIGQUIT signal, it will remove the ^\ print ...
**	... and not do anything the parent process
**	No return value
*/

void	signal_output(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n🐶 > ", sizeof("\n🐶 > "));
		rl_replace_line("", 0);
	}
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
	}
}

/*
**	Calls the signal function with signal_output as signal handler 
**	If signal returned an error something drastically went wrong and we ...
**	... exit the program
**	No return value
*/

void	ft_signal_handler(void)
{
	if (signal(SIGINT, &signal_output) == SIG_ERR
		|| signal(SIGQUIT, &signal_output) == SIG_ERR)
		exit(1);
}
