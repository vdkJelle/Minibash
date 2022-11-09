/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 10:10:31 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/11/09 18:40:57 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

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
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status_code = 1;
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
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
	if (signal(SIGINT, &signal_output) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);
}
