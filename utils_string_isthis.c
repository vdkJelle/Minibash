/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string_isthis.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 12:19:07 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/06 15:14:06 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//A token that performs a control function. It is a newline or: ‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’.
int		is_control_operator(char c)
{
	if (c == '|' || c == ';' || c == '(' || c == ')' || c == '&' || c == '\0')
		return (1);
	return (0);
}

//A character that, when unquoted, separates words. A metacharacter is a space, tab, newline, or one of the following characters: ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
int		is_metacharacter(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')' || c == ';' || c == ' ' || c == '\t' || c == '\0')
		return (1);
	return (0);
}

//The command and arguments are seperated by spaces and tabs
int		is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		is_redirection(char *s)
{
	if (!ft_strcmp(s, "<\0") || !ft_strcmp(s, ">\0") || !ft_strcmp(s, ">>\0"))
		return (1);
	return (0);
}
