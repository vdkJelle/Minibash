/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/08 17:24:54 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Input is tokenized, checked for syntax errors and executed
**	Calls check_multiline_command to make sure there are no multiline commands
**	Calls get_token to tokenize the input
**	Calls check_input to make sure there are no syntax errors
**	Calls cody_catch where the commands are executed
**	No return value
*/

static void	tokenize_parse_execute(t_data *data, char *input)
{
	if (check_multiline_command(data, input))
		return ;
	get_token(data, input);
	if (check_input(data))
	{
		ft_lstclear(&data->token, free_token);
		ft_lstclear(&data->expression, free_expression);
		return ;
	}
	cody_catch(data);
	ft_lstclear(&data->token, free_token);
}

/*
**	Main of the amazing Codyshell 🐶
**	Prints prompt
**	Reads from the terminal with readline
**	Sends the input to tokenize_parse_execute
**	Returns 0
*/

int	main(void)
{
	t_data	data;
	char	*input;

	rl_catch_signals = 0;
	ft_bzero(&data, sizeof(data));
	ft_putstr_fd("Welcome to the amazing Codyshell!\n", 1);
	initialize_env(&data.our_env, &data.env_size);
	while (1)
	{
		ft_signal_handler();
		input = readline(PROMPT);
		if (!input)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit(0);
		}
		if (*input)
			add_history(input);
		tokenize_parse_execute(&data, input);
		free(input);
	}
	return (0);
}
