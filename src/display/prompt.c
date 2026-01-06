/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:56:21 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 19:09:01 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static char	*build_minimal_prompt(t_display_config *config)
{
	if (config->is_color_active)
		return (RL_COLOR_GREEN "my_shell" RL_COLOR_RESET " $ ");
	return ("$ ");
}

static char	*build_default_prompt(t_display_config *config)
{
	if (config->is_color_active)
		return (RL_COLOR_BLUE "my_shell" RL_COLOR_RESET ":" \
			RL_COLOR_CYAN "~" RL_COLOR_RESET "> ");
	return ("[my_shell]> ");
}

static char	*build_fancy_prompt(t_display_config *config)
{
	if (config->is_color_active)
		return (RL_COLOR_BOLD_GREEN "my_shell" RL_COLOR_RESET ":" \
			RL_COLOR_BOLD_BLUE "~" RL_COLOR_RESET " ➜ ");
	return ("my_shell:~ ➜ ");
}

char	*build_prompt(t_display_config *config)
{
	t_prompt_style	style;

	style = parse_prompt_style();
	if (style == PROMPT_STYLE_MINIMAL)
		return (build_minimal_prompt(config));
	else if (style == PROMPT_STYLE_FANCY)
		return (build_fancy_prompt(config));
	else
		return (build_default_prompt(config));
}
