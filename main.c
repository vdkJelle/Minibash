/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/08 15:46:11 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	printf("Welcome to the amazing Codyshell!\n");
	while (1)
	{
		write(1, "🐶 > ", sizeof("🐶 > "));
		data.r = get_next_line(0, &data.input);
		if (data.r == -1)
			exit(1);
		if (!ft_strncmp(data.input, "exit", 4) && ft_strlen(data.input) == 4)
			exit(0);
		if (!ft_strncmp(data.input, "pwd", 3) && ft_strlen(data.input) == 3)
			pwd();
		if (!ft_strncmp(data.input, "cd ", 3) && count_words(data.input, ' ') == 2)
			cd(data.input);
		if (!ft_strncmp(data.input, "./", 2) || !ft_strncmp(data.input, "/", 1) || !ft_strncmp(data.input, "..", 2))
			execute(data.input);
		free(data.input);
		data.input = NULL;
	}
}
