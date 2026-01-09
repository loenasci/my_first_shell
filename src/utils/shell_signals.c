/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:33:58 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/08 14:34:06 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	check_signal_received(void)
{
	return (get_signal_state()->received != 0);
}

int	was_interrupted(void)
{
	return (get_signal_state()->received == SIGINT);
}

void	handle_signal_after_readline(char **input)
{
	if (check_signal_received())
	{
		signal_clear();
		if (*input)
		{
			free(*input);
			*input = NULL;
		}
	}
}

void	handle_signal_after_execution(void)
{
	if (check_signal_received())
		signal_clear();
}

int	should_exit_shell(char *input)
{
	if (!input)
		return (1);
	return (0);
}
