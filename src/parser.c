/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 18:38:11 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/06/07 19:15:21 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Joins the word segments into a word
**	Returns a malloced string with the word
*/

static char	*join_word(t_word *arg)
{
	char	*word;
	char	*word_segment;
	int		size;
	t_list	*temp;

	temp = arg->word_segment;
	size = 0;
	while (temp)
	{
		word_segment = temp->content;
		size += ft_strlen(word_segment);
		temp = temp->next;
	}
	word = malloc_guard(ft_calloc(sizeof(char), size + 1));
	temp = arg->word_segment;
	while (temp)
	{
		word_segment = temp->content;
		ft_strlcat(word, word_segment, size + 1);
		temp = temp->next;
	}
	return (word);
}

/*
**	Gets the arguments
**	Calls count_arguments to get the size of the array of arguments
**	Calls get_arg to get the word segements of the argument
**	Calls join word to merge the word segments of the command into one word
**	Returns a malloced array of malloced t_word structs
*/

static t_word	**get_arguments(t_data *data, char *s, char control_operator)
{
	int		i;
	int		j;
	int		size;
	t_word	**args;

	size = count_arguments(s, control_operator);
	args = malloc_guard(ft_calloc(sizeof(t_word *), size + 1));
	i = 0;
	j = 0;
	while (i < size)
	{
		args[i] = malloc_guard(ft_calloc(sizeof(t_word), 1));
		j += get_word(data, &args[i], s + j, control_operator);
		args[i]->word = join_word(args[i]);
		i++;
	}
	return (args);
}

/*
**	Parses over tokens and builds expressions out of them
**	Each expression consists of arguments and a control operator
**	Arguments are words seperated by metacharacters
**	No return value
*/

void	parser(t_data *data)
{
	t_list			*temp;
	t_token			*token;
	t_expression	*expression;

	temp = data->token;
	while (temp)
	{
		token = temp->content;
		expression = malloc_guard(ft_calloc(sizeof(t_expression), 1));
		if (token->string)
			expression->arg = get_arguments(data, token->string,
					token->control_operator[0]);
		expression->control_operator = malloc_guard(ft_strdup
				(token->control_operator));
		ft_lstadd_back(&data->expression, malloc_guard(ft_lstnew(expression)));
		temp = temp->next;
	}
}
