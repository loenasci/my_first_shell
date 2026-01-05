/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:17:50 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/05 14:58:59 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	has_literal_quote(t_word_part *parts)
{
	while (parts)
	{
		if (parts->type == PART_SINGLE_QUOTE
			|| parts->type == PART_DOUBLE_QUOTE)
			return (1);
		parts = parts->next;
	}
	return (0);
}

int	should_keep_expanded_arg(char *arg, int is_from_literal)
{
	if (!arg)
		return (0);
	if (arg[0] || is_from_literal)
		return (1);
	return (0);
}

static int	is_valid_heredoc_delimiter(char *delimiter)
{
	char	*clean;

	if (!delimiter || delimiter[0] == '\0')
		return (0);
	clean = clear_heredoc_delimiter(delimiter);
	if (!clean || clean[0] == '\0')
	{
		if (clean)
			free(clean);
		return (0);
	}
	free(clean);
	return (1);
}

static int	is_valid_redirect_file(char *file)
{
	if (!file || file[0] == '\0')
		return (0);
	return (1);
}

int	has_valid_redirect_target(t_token_type type, char *target)
{
	if (type == TOKEN_HEREDOC)
		return (is_valid_heredoc_delimiter(target));
	return (is_valid_redirect_file(target));
}
