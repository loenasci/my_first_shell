/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delimiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:46:14 by loda-sil          #+#    #+#             */
/*   Updated: 2026/01/13 18:46:18 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static char	get_quote_char(t_word_part *parts)
{
	if (!parts)
		return (0);
	if (parts->type == PART_SINGLE_QUOTE)
		return ('\'');
	if (parts->type == PART_DOUBLE_QUOTE)
		return ('"');
	return (0);
}

char	*get_heredoc_delimiter(t_word_part *parts)
{
	char	*result;
	char	quote;

	result = ft_strdup("");
	quote = get_quote_char(parts);
	if (quote)
		result = join_char_and_free(result, quote);
	while (parts)
	{
		if (parts->type == PART_LITERAL || parts->type == PART_SINGLE_QUOTE
			|| parts->type == PART_DOUBLE_QUOTE)
			result = join_and_free(result, parts->content);
		parts = parts->next;
	}
	return (result);
}
