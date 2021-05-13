/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_arg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 20:56:05 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/13 15:29:59 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

arg_characters	get_arg_characters(char *s, int i)
{
	arg_characters	ac;

	if (s[i] == '\'' && !(count_backslash(s, i) % 2))
		ac = SINGLEQUOTE;
	else if (s[i] == '\"' && !(count_backslash(s, i) % 2))
		ac = DOUBLEQUOTE;
	else if (s[i] == '\\' && !(count_backslash(s, i) % 2))
		ac = BACKSLASH;
	else if (s[i] == '$' && !(count_backslash(s, i) % 2) && !is_control_operator(s[i + 1]) && !(s[i + 1] != '_' && s[i + 1] != '?' && !ft_isalpha(s[i + 1])))
		ac = ENVIRONMENT_VARIABLE;
	else if (is_metacharacter(s[i]) && !(count_backslash(s, i) % 2))
		ac = METACHARACTER;
	else
		ac = NORMAL;
	return (ac);
}

int				get_arg(t_data *data, t_word **word, char *s, char control_op)
{
	int				i;
	arg_characters	ac;
	f_arg_handler	arg_handler[5];

	arg_handler[0] = handle_char;
    arg_handler[1] = handle_doublequotes;
    arg_handler[2] = handle_environment_variable;
	arg_handler[3] = handle_metacharacter;
    arg_handler[4] = handle_singlequotes;
	if (s[0] && is_metacharacter(s[0]))
		return (arg_handler[3](data, word, s));
	i = 0;
	while (s[i] && s[i] != control_op)
	{
		ac = get_arg_characters(s, i);
		if (ac == BACKSLASH)
			i++;
		else if (ac == METACHARACTER)
			return (i + skip_while_char(s + i, is_whitespace));
		else
			i += arg_handler[ac](data, word, s + i);
	}
	return (i);
}
