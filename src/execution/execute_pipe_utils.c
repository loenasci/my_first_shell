/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:26:48 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/08 17:31:51 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

void	set_exit(t_ast_node *node, t_env *env)
{
	if (!node)
		exit(1);
	if (node->type == NODE_PIPE)
		exit(execute_pipe(node, env));
	if (node->type != NODE_COMMAND || !node->cmd)
		exit(1);
	if (!node->cmd->args || !node->cmd->args[0])
		exit(0);
	if (is_builtin(node->cmd->args[0]))
		exit(execute_builtin(node->cmd->args, env));
}
