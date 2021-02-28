/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/24 13:15:26 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_env(char ***our_env)
{
	int i;

	i = 0;
	while (environ[i])
		i++;
	*our_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		(*our_env)[i] = ft_strdup(environ[i]);
		i++;
	}
	(*our_env)[i] = NULL;
}

int	main(void)
{
	t_data		data;
	int			i;

	ft_bzero(&data, sizeof(data));
	printf("Welcome to the amazing Codyshell!\n");
	initialize_env(&data.our_env);
	i = 0;
	while (1)
	{
		write(1, "🐶 > ", sizeof("🐶 > "));
		data.r = get_next_line(0, &data.input);
		if (data.r == -1)
			exit(1);
		while (data.input[i] == ' ')
			i++;
		if (!ft_strncmp(data.input + i, "exit", 4) && ft_strlen(data.input) == 4)
			exit(0);
		if (!ft_strncmp(data.input + i, "pwd", 3) && ft_strlen(data.input) == 3)
			pwd();
		if (!ft_strncmp(data.input + i, "cd ", 3) && count_words(data.input, ' ') == 2)
			cd(data.input);
		if (!ft_strncmp(data.input + i, "./", 2) || !ft_strncmp(data.input, "/", 1) || !ft_strncmp(data.input, "..", 2))
			execute(data.input, data);
		if (!ft_strncmp(data.input + i, "echo", 4))
			ft_echo(data.input);
		if (!ft_strncmp(data.input + i, "export", 6))
			export(data.input, &data, &data.our_env);
		free(data.input);
		data.input = NULL;
	}
}
