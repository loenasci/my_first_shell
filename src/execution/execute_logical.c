/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:57:22 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/13 19:01:48 by loda-sil         ###   ########.fr       */
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
	set_exit_status(left_status);
	if (left_status == 0)
	{
		right_status = execute_ast(right, env);
		set_exit_status(right_status);
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
	set_exit_status(left_status);
	if (left_status != 0)
	{
		right_status = execute_ast(right, env);
		set_exit_status(right_status);
		return (right_status);
	}
	return (left_status);
}
