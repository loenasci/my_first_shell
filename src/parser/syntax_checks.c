/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:03:55 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/05 16:32:51 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	redirect_has_valid_target(t_token *redirect)
{
	if (!redirect || !redirect->next)
		return (0);
	return (redirect->next->type == TOKEN_WORD);
}

int	is_invalid_redirect_sequence(t_token *current)
{
	if (!current || !current->next)
		return (0);
	return (is_redirect(current) && is_operator_token(current->next));
}

int	has_orphan_operator_start(t_token *tokens)
{
	return (is_invalid_start_token(tokens));
}

int	has_orphan_operator_end(t_token *tokens)
{
	t_token	*last;

	last = get_last_token(tokens);
	return (is_invalid_end_token(last));
}

int	has_consecutive_operators(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && current->next)
	{
		if (is_operator_token(current) && is_operator_token(current->next))
			return (1);
		current = current->next;
	}
	return (0);
}
