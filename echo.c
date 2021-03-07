/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 10:21:10 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/03/03 13:25:18 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		print_env(char *line)
{
	int		len;
	char	*key;
	char	*value;

	len = 0;
	while (line[len] && !is_whitespace(line[len]))
		len++;
	key = ft_substr(line, 0, len);
	if (!key)
		exit(1);
	value = get_env(NULL, key);
	free(key);
	ft_putstr_fd(value, 1);
	return (len);
}

static int		print_env_in_doubleq(char *line)
{
	int		len;
	char	*key;
	char	*value;

	len = 0;
	while (line[len] && !is_whitespace(line[len]) && line[len] != '\"')
		len++;
	key = ft_substr(line, 0, len);
	if (!key)
		exit(1);
	value = getenv(key);
	free(key);
	ft_putstr_fd(value, 1);
	return (len);
}

static int		print_between_doubleq(char *line)
{
	int		i;

	i = 1;
	while (line[i] && line[i] != '\"')
	{
		if (line[i] == '\\')
		{
			if (ft_strchr("\\\"", line[i + 1]))
			{
				write(1, &line[i + 1], 1);
				i++;
			}
			else
				write(1, &line[i], 1);
		}
		else if (line[i] == '$' && count_backslash(line, i) % 2 == 0)
			i += print_env_in_doubleq(line + i + 1);
		else
			write(1, &line[i], 1);
		i++;
		if (line[i] == '\"' && count_backslash(line, i) % 2 != 0)
		{
			write (1, &line[i], 1);
			i++;
		}
	}
	return (i);
}

static int		print_between_singleq(char *line)
{
	int		i;

	i = 1;
	while (line[i] && line[i] != '\'')
	{
		write (1, &line[i], 1);
		i++;
	}
	return (i);
}

static int		print_whitespaces(char *line)
{
	int		i;

	i = 0;
	i += skip_whitespaces_int(line);
	if (line[i] || (i > 0 || line[i - 1] == '\\'))
		write(1, " ", 1);
	return (i - 1);
}

static void		print_echo(char *line, int newline)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && count_backslash(line, i) % 2 == 0)
			i += print_between_singleq(line + i);
		else if (line[i] == '\"' && count_backslash(line, i) % 2 == 0)
			i += print_between_doubleq(line + i);
		else if (line[i] == '\\')
		{
			if (i > 0 && count_backslash(line, i) % 2 != 0)
				write(1, &line[i], 1);
		}
		else if (line[i] == ' ')
			i += print_whitespaces(line + i);
		else if (line[i] == '$' && count_backslash(line, i) % 2 == 0)
			i += print_env(line + i + 1);
		else
			write(1, &line[i], 1);
		i++;
	}
	if (newline == 1)
		write(1, "\n", 1);
}

void			ft_echo(char *line)
{
	int		newline;
	int		i;

	if (count_quotes(line) == -1)
		return (ft_putstr_fd("Multiline command1\n", 2));
	if (count_backslash(line, ft_strlen(line)) % 2 != 0)
		return (ft_putstr_fd("Multiline command2\n", 2));
	i = 0;
	newline = 1;
	if (ft_strlen(line) > 0)
	{
		i += skip_whitespaces_int(line + i);
		if (line[i] == '-' && line[i + 1] == 'n' && line[i + 2] == '\0')
			return ;
		if (line[i] == '-' && line[i + 1] == 'n' && line[i + 2] == ' ')
		{
			newline = 0;
			i += 3;
		}
		i += skip_whitespaces_int(line + i);
	}
	print_echo(line + i, newline);
}
