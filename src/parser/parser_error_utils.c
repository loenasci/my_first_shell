/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:08:17 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/05 15:24:23 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	redirect_error(char *msg, t_token_type type, char *file)
{
	(void)type;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (file != NULL)
		free(file);
	set_exit_status(2);
	return (0);
}

int	ambiguous_redirect_error(char *target)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (target && target[0])
		ft_putstr_fd(target, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	set_exit_status(1);
	if (target)
		free(target);
	return (0);
}

int	heredoc_limiter_error(char *delimiter)
{
	ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
	ft_putstr_fd("invalid heredoc delimiter\n", STDERR_FILENO);
	set_exit_status(2);
	if (delimiter)
		free(delimiter);
	return (0);
}

int	parser_false_error(char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	set_exit_status(2);
	return (0);
}
