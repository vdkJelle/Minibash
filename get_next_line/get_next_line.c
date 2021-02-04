/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 16:30:55 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/02/04 11:35:14 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_writeline(char **ret, char **line, int i)
{
	*line = ft_strdup_gnl(*ret, '\n');
	if (*line == NULL)
		return (-1);
	*ret = ft_memmove_gnl(*ret, (ft_strchr_gnl(*ret, '\n') + 1));
	if (**ret == 0 && i == 0)
	{
		free(*ret);
		*ret = NULL;
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char			*ret[_SC_OPEN_MAX];
	char				buf[BUFFER_SIZE + 1];
	int					i;

	i = 1;
	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	if (!ret[fd])
	{
		ret[fd] = malloc(sizeof(char));
		if (!ret[fd])
			return (-1);
		ret[fd][0] = '\0';
	}
	while (i && !ft_strchr_gnl(ret[fd], '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i < 0)
			return (-1);
		buf[i] = '\0';
		ret[fd] = ft_strjoin_gnl(ret[fd], buf);
		if (ret[fd] == 0)
			return (-1);
	}
	return (ft_writeline(&ret[fd], line, i));
}
