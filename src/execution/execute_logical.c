/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:57:22 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/10 14:46:07 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	execute_logical_and(t_ast_node *left, t_ast_node *right, t_env *env)
{
	int	left_status;
	int	right_status;

	if (!left || !right)
		return (1);
	left_status = execute_ast(left, env);
	if (left_status == 0)
	{
		right_status = execute_ast(right, env);
		return (right_status);
	}
	return (left_status);
}

int	execute_logical_or(t_ast_node *left, t_ast_node *right, t_env *env)
{
	int	left_status;
	int	right_status;

	if (!left || !right)
		return (1);
	left_status = execute_ast(left, env);
	if (left_status != 0)
	{
		right_status = execute_ast(right, env);
		return (right_status);
	}
	return (left_status);
}
