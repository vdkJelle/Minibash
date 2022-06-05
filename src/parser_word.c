/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_word.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 20:56:05 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/05 18:34:47 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Calls the correct word segment handler function based on the special character c
** Returns the index of the end of the word segment
*/

static int	word_segment_handler(t_data *data, e_special_char c, t_word **word, char *s)
{
	f_word_segment_handler	word_segment_handler[5];

	word_segment_handler[CHAR] = handle_char;
    word_segment_handler[DOUBLEQUOTE] = handle_doublequotes;
    word_segment_handler[ENVIRONMENT_VARIABLE] = handle_environment_variable;
	word_segment_handler[METACHARACTER] = handle_metacharacter;
    word_segment_handler[SINGLEQUOTE] = handle_singlequotes;
	return (word_segment_handler[c](data, word, s));
}

/*
** Identifies the type of character
** Some characters have special meanings and need to be handled differently
** Checks if special characters are not escaped
** In case of an environmental character also checkes if
**		the next character is not a control operator
**		the next character is the first character of a valid identifier
** Returns the type of character
*/

static e_special_char	identify_character(char *s, int i)
{
	if (s[i] == '\'' && !(count_backslash(s, i) % 2))
		return (SINGLEQUOTE);
	else if (s[i] == '\"' && !(count_backslash(s, i) % 2))
		return (DOUBLEQUOTE);
	else if (s[i] == '\\' && !(count_backslash(s, i) % 2))
		return (BACKSLASH);
	else if (s[i] == '$' && !(count_backslash(s, i) % 2)
	&& !is_control_operator(s[i + 1])
	&& !(s[i + 1] != '_' && s[i + 1] != '?' && !ft_isalpha(s[i + 1])))
		return (ENVIRONMENT_VARIABLE);
	else if (is_metacharacter(s[i]) && !(count_backslash(s, i) % 2))
		return (METACHARACTER);
	else
		return (CHAR);
}

/*
** Gets the word
** Words are seperated by metacharacters
** Checks if the first character is a metacharacter
**		it is saved as a word to check for a syntax error later
** Loops over the input string and calls identify_character
** If the character is a backslash it can be skipped
** If the character is a metacharacter the end of the word has been reached and
**		the function returns
** If the character is not a backslash or a metacharacter the correct
**		word_segment_handler function is called where word segments are added to the word
** Returns index of the end of the word
*/

int	get_word(t_data *data, t_word **word, char *s, char control_operator)
{
	int				i;
	e_special_char	c;

	if (s[0] && is_metacharacter(s[0]))
		return (word_segment_handler(data, METACHARACTER, word, s));
	i = 0;
	while (s[i] && s[i] != control_operator)
	{
		c = identify_character(s, i);
		if (c == BACKSLASH)
			i++;
		else if (c == METACHARACTER)
			return (i + skip_while_char(s + i, is_whitespace));
		else
			i += word_segment_handler(data, c, word, s + i);
	}
	return (i);
}
