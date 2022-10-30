/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 10:10:31 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/10/30 16:44:03 by jelvan-d      ########   odam.nl         */
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
		rl_replace_line("", 1);
		write(STDOUT_FILENO, "\n", 1);
	}
	rl_on_new_line();
	rl_redisplay();
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
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);
}
