/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/16 21:45:18 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_backslash(char *line, int loc)
{
	int		i;
	int		count;

	// printf("hallo %d\n", loc);
	if (line[loc] == '\\')
		i = loc;
	else
		i = loc - 1;
	count = 0;		
	while (i > 0 && line[i] == '\\')
	{
		count++;
		i--;
	}
	return (count);
}

static int		print_between_doubleq(char *line, int w)
{
	int		i;

	i = 1;
	while (line[i] && line[i] != '\"')
	{
		if (line[i] == '\\')
		{
			if (ft_strchr("\\\"", line[i + 1]))
			{
				if (w == 1)
					write(1, &line[i + 1], 1);
				i++;
			}
			else
				if (w == 1)
					write(1, &line[i], 1);			
		}
		else
			if (w == 1)
				write(1, &line[i], 1);
		i++;
		if (line[i] == '\"' && count_backslash(line, i) % 2 != 0)
		{
			if (w == 1)
				write (1, &line[i], 1);
			i++;			
		}
	}
	return (i);
}

static int		print_between_singleq(char *line, int w)
{
	int		i;

	i = 1;

	while (line[i] && line[i] != '\'')
	{
		if (w == 1)
			write (1, &line[i], 1);
		i++;
	}
	return (i);
}

static int		print_whitespaces(char *line)
{
	int		i;

	i = 0;
	while(line[i] && line[i] == ' ')
		i++;
	write(1, " ", 1);
	return (i - 1);
}

static void		print_echo(char *line, int newline)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && count_backslash(line, i) % 2 != 0)
			i += print_between_singleq(line + i, 1);
		else if (line[i] == '\"' && count_backslash(line, i) % 2 != 0)
			i += print_between_doubleq(line + i, 1);
		else if (line[i] == '\\')
		{
				// printf("-------\n");
			if (i > 0 && count_backslash(line, i) % 2 == 0)
			{

				write(1, &line[i], 1);
			}
		}
		else if (line[i] == ' ')
			i += print_whitespaces(line + i);
		else
			write(1, &line[i], 1);
		i++;
	}
	write(1, "$", 1);
	if (newline == 1)
		write(1, "\n", 1);
}

static int		count_quotes(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && count_backslash(line, i) % 2 == 0)
		{
			i += print_between_singleq(line + i, 0);
			if (i == (int)ft_strlen(line))
				return (-1);
		}
		else if (line[i] == '\"')
		{
			i += print_between_doubleq(line + i, 0);
			if (i == (int)ft_strlen(line))
				return (-1);
		}
		i++;
	}
	return (0);
}

void	ft_echo(char *line)
{
	int		newline;
	int		i;

	if (count_quotes(line) == -1)
		return (ft_putstr_fd("Multiline command1\n", 2));
	if (count_backslash(line, ft_strlen(line)) % 2 != 0)
		return (ft_putstr_fd("Multiline command2\n", 2));
	i = 4;
	newline = 1;
	if (ft_strlen(line) > 4)
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == '-' && line[i + 1] == 'n' && line[i + 2] == '\0')
			return ;
		if (line[i] == '-' && line[i + 1] == 'n' && line[i + 2] == ' ')
		{
			newline = 0;
			i += 3;
		}
		while (line[i] && line[i] == ' ')
			i++;
	}
	print_echo(line + i, newline);
}

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
		if (!ft_strncmp(data.input, "echo", 4))
			ft_echo(data.input);
		free(data.input);
		data.input = NULL;
	}
}
