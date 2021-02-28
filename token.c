/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 12:37:26 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/02/28 12:20:01 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenize(char *s, char c, t_list **token)
{
	int		lencmd;
	int		lenarg;
	t_token *tok;

	lencmd = 0;
	lenarg = 0;
	tok = (t_token*)malloc(sizeof(t_token));
	if (!tok)
		exit(1);
	skip_whitespaces(&s);
	lencmd += skip_nonwhitespaces_int(s);
	tok->cmd = ft_substr(s, 0, lencmd);
	if (!tok->cmd)
		exit(1);
	lencmd += skip_whitespaces_int(s);
	lenarg += skip_until_char(s + lencmd, c);
	tok->arg = ft_substr(s, lencmd, lenarg);
	if (!tok->arg)
		exit(1);
	ft_lstadd_back(token, ft_lstnew(tok));
	return (lencmd + lenarg);
}

static int	skip_doubleq(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '\"')
	{
		i++;
		if (line[i] && count_backslash(line, i) % 2 == 1)
			i++;
	}
	return (i);
}

void		get_token(char *line, t_list **token)
{
	int		i;
	int		saved;

	i = 0;
	saved = 0;
	while (line[i])
	{
		if (line[i] == ';')
			saved += 1 + tokenize(line + saved, ';', token);
		else if (line[i] == '|')
			saved += 1 + tokenize(line + saved, '|', token);
		else if (line[i] == '\'')
			i += skip_until_char(line + i + 1, '\'');
		else if (line[i] == '\"')
			i += skip_doubleq(line + i + 1);
		i++;
	}
	tokenize(line + saved, '\0', token);
	ft_lstiter(*token, print_token);
}
