/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:28:44 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/05 16:30:06 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	is_invalid_start_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_PIPE
		|| token->type == TOKEN_AND
		|| token->type == TOKEN_OR);
}

int	is_invalid_end_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_PIPE
		|| token->type == TOKEN_AND
		|| token->type == TOKEN_OR);
}

t_token	*get_last_token(t_token *tokens)
{
	t_token	*last;

	if (!tokens)
		return (NULL);
	last = tokens;
	while (last->next)
		last = last->next;
	return (last);
}
