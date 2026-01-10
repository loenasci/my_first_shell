/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:51:37 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/10 14:20:35 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	execute_ast(t_ast_node *node, t_env *env)
{
	if (!node)
		return (env->last_exit_status);
	if (node->type == NODE_COMMAND)
		return (execute_command(node->cmd, env));
	if (node->type == NODE_PIPE)
		return (execute_pipe(node, env));
	return (1);
}
