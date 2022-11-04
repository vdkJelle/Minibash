/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/11/04 19:26:28 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Adds the correct shell level to the array of environmental variables
**	If SHLVL is not set the value it is set to 1
**	If SHLVL is set but the value is not numeric the value is set to 1
**	If SHLVL is set correctly the value is incremented
**	Calls append_key_value to add the SHLVL to the array of env variables
**	No return value
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
		if (!shlvl[i])
			temp = malloc_guard(ft_strdup("SHLVL=1"));
		else
		{
			n = ft_atoi(shlvl) + 1;
			temp = malloc_guard(ft_strjoin_wrapper(malloc_guard(ft_strdup
							("SHLVL=")), malloc_guard(ft_itoa(n)), 3));
		}
	}
	append_key_value(temp, our_env, env_size);
	free(temp);
}

static void	handle_pwd(char ***our_env, int *env_size, t_data *data)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		print_error(data, 1, make_array("🐶 > ", strerror(errno), NULL, NULL));
		return ;
	}
	pwd = malloc_guard(ft_strjoin_wrapper(malloc_guard(ft_strdup
			("PWD=")), pwd, 3));
	append_key_value(pwd, our_env, env_size);
	free(pwd);
}

/*
**	Copies the environmental variables of the shell environment
**	Uses an external char **environ
**	Calls handle_shlvl to set the correct value of the key SHLVL
**	No return value
*/

static void	initialize_env(char ***our_env, int *env_size, t_data *data)
{
	extern char	**environ;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (environ[j])
		j++;
	*our_env = ft_malloc(sizeof(char *) * (j));
	j = 0;
	while (environ[j])
	{
		if (!ft_strncmp(environ[i], "OLDPWD", 6))
			j++;
		(*our_env)[i] = malloc_guard(ft_strdup(environ[j]));
		i++;
		j++;
	}
	(*our_env)[i] = NULL;
	(*env_size) = i;
	handle_pwd(our_env, env_size, data);
	handle_shlvl(our_env, env_size);
}

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
	initialize_env(&data.our_env, &data.env_size, &data);
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
