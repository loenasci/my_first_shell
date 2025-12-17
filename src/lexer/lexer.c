/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:18:45 by lsarraci          #+#    #+#             */
/*   Updated: 2025/12/17 17:28:40 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static t_token	*create_single_token(char *op_string,
			t_token_type type, int *i, int pos)
{
	char	*value;

	value = ft_strdup(op_string);
	if (!value)
		return (NULL);
	(*i) += ft_strlen(op_string);
	return (token_new(type, value, pos));
}

static t_token	*create_operator_token(char *input, int *i, int pos)
{
	t_token_type	type;
	char			*value;

	if (input[*i] == '|')
		return (create_single_token("|", TOKEN_PIPE, i, pos));
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			return (create_single_token("<<", TOKEN_REDIR_IN, i, pos));
		else
			return (create_single_token("<", TOKEN_REDIR_IN, i, pos));
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '<')
			return (create_single_token(">>", TOKEN_REDIR_OUT, i, pos));
		else
			return (create_single_token(">", TOKEN_REDIR_OUT, i, pos));
	}
	return (NULL);
}

static int	skip_spaces(char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

/*static char *extract_word(char *input, int *i)
{
	
}*/

t_token	*lexer(char *input)
{
	int		i;
	int		pos;
	t_token	*tokens;
	t_token	*new;

	i = 0;
	tokens = NULL;
	pos = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		if (is_operator(input[i]))
		{
			new = create_operator_token(input, &i, pos);
			token_list_add_back(&tokens, new);
			pos++;
		}
	}
	return (tokens);
}
