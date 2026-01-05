/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:36:55 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/05 15:48:09 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static int	handle_escape_in_double_quote(char *input, int *i)
{
	if (input[*i] == '\\' && input[*i + 1])
	{
		(*i)++;
		return (1);
	}
	return (0);
}

static char	process_quote_char(char *input, int *i, char in_quote)
{
	if (in_quote == '"')
	{
		if (handle_escape_in_double_quote(input, i))
			return (in_quote);
		if (input[*i] == '"')
			return (0);
	}
	else if (in_quote == '\'')
	{
		if (input[*i] == '\'')
			return (0);
	}
	return (in_quote);
}

static int	validate_quotes_error(void)
{
	ft_putstr_fd("minishell: syntax error: unclosed quote\n", STDERR_FILENO);
	return (0);
}

int	validate_quotes(char *input)
{
	int		i;
	char	in_quote;

	i = 0;
	in_quote = 0;
	while (input[i])
	{
		if (!in_quote)
		{
			if (input[i] == '\'' || input[i] == '"')
				in_quote = input[i];
		}
		else
			in_quote = process_quote_char(input, &i, in_quote);
		i++;
	}
	if (in_quote)
		return (validate_quotes_error());
	return (1);
}
