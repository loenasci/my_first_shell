/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:13:47 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/05 16:55:30 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

void	parse_error_node(char *msg, t_ast_node *node)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	node_free(node);
	set_exit_status(2);
}

void	parse_error_command(char *msg, t_command *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	command_free(cmd);
	set_exit_status(2);
}

void	empty_command_error(t_command *cmd)
{
	ft_putstr_fd("minishell: syntax error: empty command\n", STDERR_FILENO);
	set_exit_status(2);
	command_free(cmd);
}

void	*parser_null_error(char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	set_exit_status(2);
	return (NULL);
}

void	parse_error_free(char *msg, void *ptr, void (*free_func)(void *))
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	set_exit_status(2);
	if (ptr && free_func)
		free_func(ptr);
}
