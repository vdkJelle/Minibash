/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_isthis.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 12:19:07 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/01 14:24:56 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Checks if the character is a control operator
** A control operator is a token that performs a control function
**		and seperates token sets from each other
** Returns 0 if the character is not a control operator
** Returns 1 if the character is a control operator
*/

int	is_control_operator(char c)
{
	if (c == '|' || c == ';' || c == '(' || c == ')' || c == '&' || c == '\0')
		return (1);
	return (0);
}

/*
** Checks if the character is a metacharacter
** A metacharacter is a character that, when unquoted, seperates words
** Returns 0 if the character is not a metacharacter
** Returns 1 if the character is a metacharacter
*/

int	is_metacharacter(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')'
	|| c == ';' || c == ' ' || c == '\t' || c == '\0')
		return (1);
	return (0);
}

/*
** Checks if the character is a whitespace
** Returns 0 if the character is not a whitespace
** Returns 1 if the character is a whitespace
*/

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

/*
** Checks if the string is a valid redirection
** Returns 0 if the string is not a valid redirection
** Returns 1 if the string is a valid redirection
*/

int	is_redirection(char *s)
{
	if (!ft_strcmp(s, "<\0") || !ft_strcmp(s, ">\0") || !ft_strcmp(s, ">>\0"))
		return (1);
	return (0);
}

/*
** Checks if the character is a digit
** Returns 0 if the character is not a digit
** Returns 1 if the character is a digit
*/

int	ft_isdigit_char(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
