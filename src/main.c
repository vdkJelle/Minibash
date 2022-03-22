/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2022/03/22 12:14:48 by jelvan-d      ########   odam.nl         */
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

static void		handle_shlvl(char ***our_env, int *env_size)
{
	char 	*shlvl;
	char	*temp;
	int		i;
	int		n;
	
	shlvl = get_env(*our_env, "SHLVL");
	if (!shlvl)
		temp = ft_strdup("SHLVL=1");
	else
	{
		i = 0;
		while (shlvl[i] && ft_isdigit(shlvl[i]))
			i++;
		if (shlvl[i] != '\0')
			temp = ft_strdup("SHLVL=1");
		else
		{
			n = ft_atoi(shlvl) + 1;
			temp = ft_strjoin_wrapper(ft_strdup("SHLVL="), ft_itoa(n), 3);
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

static void		initialize_env(char ***our_env, int *env_size)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	*our_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*our_env))
		exit(1);
	i = 0;
	while (environ[i])
	{
		(*our_env)[i] = ft_strdup(environ[i]);
		if (!((*our_env)[i]))
			exit(1);
		i++;
	}
	(*our_env)[i] = NULL;
	(*env_size) = i;
	handle_shlvl(our_env, env_size);
}

/*
** Main of the amazing Codyshell 🐶
** Prints prompt
** Reads from the terminal
** Calls get_token to tokenize and parse the input for the terminal
** Calls check_token to make sure the token is valid
** Calls cody_catch where the commands are executed
** Returns 0
*/

int				main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	ft_putstr_fd("Welcome to the amazing Codyshell!\n", 1);
	initialize_env(&data.our_env, &data.env_size);
	while (1)
	{
		write(1, "🐶 > ", sizeof("🐶 > "));
		ft_signal_handler();
		data.r = get_next_line(0, &data.input);
		if (data.r == -1)
			exit(1);
		if (data.r == 0 && !*(data.input))
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		get_token(&data, data.input);
		// ft_lstiter(data.token, print_token);
		if (!check_token(&data))
			cody_catch(&data);
		ft_lstclear(&data.token, free_token);
		free(data.input);
		data.input = NULL;
	}
	return (0);
}
