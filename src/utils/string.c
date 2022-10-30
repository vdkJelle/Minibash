/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/01 14:24:42 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/10/30 15:02:44 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Compares two strings
**	Returns 0 if the strings are identical
**	Returns an integer not equal to 0 if they are different
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - s2[i]);
}

/*
**	Wrapper function for ft_strjoin
**	Calls ft_strjoin which returns the malloc concatenated string
**	Depending on the mode it frees nothing, string 1, string 2 or both
**	Returns the malloced concatenated string
**	Returns NULL if something went wrong in ft_strjoin
*/

char	*ft_strjoin_wrapper(char *s1, char *s2, int mode)
{
	char	*s;

	s = malloc_guard(ft_strjoin(s1, s2));
	if (mode == 1)
		free(s1);
	else if (mode == 2)
		free(s2);
	else if (mode == 3)
	{
		free(s1);
		free(s2);
	}
	if (!s)
		return (NULL);
	return (s);
}

/*
**	Constructs a path from the environmental variable PATH
**	Checks if the command (arg) is present in the directory
**	Takes the directory and appends it to the argument
**		with a "/" in between
*/

char	*get_path_from_bin(t_data *data, char *arg)
{
	char	**splitted_path;
	char	*ret;
	int		i;

	ret = NULL;
	i = 0;
	splitted_path = malloc_guard(ft_split(get_env(data->our_env, "PATH"), ':'));
	while (splitted_path && splitted_path[i])
	{
		if (check_in_dir(arg, splitted_path[i]))
		{
			ret = ft_malloc(sizeof(char) * (ft_strlen(splitted_path[i]) + 2));
			ft_strlcat(ret, splitted_path[i], ft_strlen(splitted_path[i]) + 2);
			ret[ft_strlen(splitted_path[i]) + 0] = '/';
			ret[ft_strlen(splitted_path[i]) + 1] = '\0';
			ret = malloc_guard(ft_strjoin_wrapper(ret, arg, 1));
			break ;
		}
		i++;
	}
	free_array(splitted_path);
	return (ret);
}
