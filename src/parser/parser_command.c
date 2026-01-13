/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:28:26 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/13 19:44:01 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static char	*build_var_literal(char *var_name)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin("${", var_name);
	result = ft_strjoin(tmp, "}");
	free(tmp);
	return (result);
}

static char	*build_literal_word(t_word_part *parts)
{
	char	*result;

	result = ft_strdup("");
	while (parts)
	{
		if (parts->type == PART_LITERAL)
			result = join_and_free_both(result, ft_strdup(parts->content));
		else if (parts->type == PART_SINGLE_QUOTE)
		{
			result = join_and_free_both(result, ft_strdup("'"));
			result = join_and_free_both(result, ft_strdup(parts->content));
			result = join_and_free_both(result, ft_strdup("'"));
		}
		else if (parts->type == PART_DOUBLE_QUOTE)
			result = join_and_free_both(result, ft_strdup(parts->content));
		else if (parts->type == PART_VARIABLE)
			result = join_and_free_both(result,
					build_var_literal(parts->content));
		parts = parts->next;
	}
	return (result);
}

static int	process_word(t_command *cmd, t_token *token)
{
	char	*expanded;
	int		has_quotes;

	expanded = build_literal_word(token->parts);
	if (!expanded)
		return (0);
	has_quotes = has_literal_quote(token->parts);
	if (!should_keep_expanded_arg(expanded, has_quotes))
		return (free(expanded), 1);
	if (!command_add_arg(cmd, expanded))
		return (free(expanded), 0);
	return (1);
}

static int	process_token(t_command *cmd, t_token **tokens)
{
	if ((*tokens)->type == TOKEN_WORD)
		return (process_word(cmd, *tokens));
	if (is_redirect(*tokens))
		return (handle_redirect(cmd, tokens));
	return (1);
}

t_ast_node	*parse_simple_cmd(t_token **tokens)
{
	t_command	*cmd;

	cmd = command_new();
	if (!cmd)
		return (NULL);
	while (*tokens && is_word_or_redirect(*tokens))
	{
		if (!process_token(cmd, tokens))
			return (parse_error_command("invalid token", cmd), NULL);
		*tokens = (*tokens)->next;
	}
	if (!is_valid_command(cmd))
		return (empty_command_error(cmd), NULL);
	if (!process_all_heredocs(cmd))
	{
		if (get_signal_state()->received != SIGINT)
			parse_error_command("heredoc processing failed", cmd);
		else
			command_free(cmd);
		return (NULL);
	}
	return (node_new_command(cmd));
}
