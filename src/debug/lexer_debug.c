/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:54:49 by lsarraci          #+#    #+#             */
/*   Updated: 2025/12/17 19:16:29 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

void	print_tokens(t_token *tokens)
{
	t_token			*current;
	int				i;
	const char		*type_names[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT",
		"APPEND", "HEREDOC", "SINGLE_QUOTE", "DOUBLE_QUOTE", "VARIABLE",
		"AND", "OR"};

	current = tokens;
	i = 0;
	ft_printf("\n=== TOKENS ===\n");
	while (current)
	{
		ft_printf("[%d] %s: '%s'\n", current->pos,
			type_names[current->type], current->value);
		current = current->next;
		i++;
	}
	ft_printf("Total: %d tokens\n==============\n\n", i);
}
