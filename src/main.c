/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/05/29 12:50:00 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Adds the correct shell level to the array of environmental variables
** If SHLVL is not set the value it is set to 1
** If SHLVL is set but the value is not numeric the value is set to 1
** If SHLVL is set correctly the value is incremented
** Calls append_key_value to add the key and value to the array of env variables
** No return value
*/

static void	handle_shlvl(char ***our_env, int *env_size)
{
	char	*shlvl;
	char	*temp;
	int		i;
	int		n;
	
	shlvl = get_env(*our_env, "SHLVL");
	if (!shlvl)
		temp = malloc_guard(ft_strdup("SHLVL=1"));
	else
	{
		i = skip_while_not_char(shlvl, ft_isdigit_char);
		if (shlvl[i] != '\0')
			temp = malloc_guard(ft_strdup("SHLVL=1"));
		else
		{
			n = ft_atoi(shlvl) + 1;
			temp = malloc_guard(ft_strjoin_wrapper(malloc_guard(ft_strdup("SHLVL=")), malloc_guard(ft_itoa(n)), 3));
		}
	}
	if (!temp)
		exit(1);
	append_key_value(temp, our_env, env_size);
	free(temp);
}

/*
** Copies the environmental variables of the shell environment
** Uses an external char **environ
** Calls handle_shlvl to set the correct value of the key SHLVL
** No return value
*/

static void	initialize_env(char ***our_env, int *env_size)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	*our_env = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		(*our_env)[i] = malloc_guard(ft_strdup(environ[i]));
		i++;
	}
	(*our_env)[i] = NULL;
	(*env_size) = i;
	handle_shlvl(our_env, env_size);
}

/*
** Calls check_multiline_command to make sure there are no multiline commands
** Calls get_token to tokenize the input
** Calls parser to build expressions from the tokens
** Calls check_expression to make sure the expression is valid
** Calls cody_catch where the commands are executed
** No return value
*/

static void	tokenize_parse_execute(t_data *data, char *input)
{
	if (check_multiline_command(data, input))
		return ;
	get_token(data, input);
	parser(data);
	ft_lstclear(&data->token, free_token);
	ft_lstiter(data->expression, print_expression);
	if (check_expressions(data))
	{
		ft_lstclear(&data->expression, free_expression);
		return ;
	}
	cody_catch(data);
	ft_lstclear(&data->expression, free_expression);
}

/*
** Main of the amazing Codyshell 🐶
** Prints prompt
** Reads from the terminal with readline
** Sends the input to tokenize_parse_execute
** Returns 0
*/

int	main(void)
{
	t_data	data;
	char	*input;

	ft_bzero(&data, sizeof(data));
	ft_putstr_fd("Welcome to the amazing Codyshell!\n", 1);
	initialize_env(&data.our_env, &data.env_size);
	while (1)
	{
		ft_signal_handler();
		input = readline("🐶 > ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		if (*input)
			add_history(input);
		tokenize_parse_execute(&data, input);
		free(input);
	}
	return (0);
}
