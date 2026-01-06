/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:58 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 18:44:52 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

t_display_config	*init_display(void)
{
	t_display_config	*config;
	int					utf8_support;

	config = malloc(sizeof(t_display_config));
	if (!config)
		return (NULL);
	config->terminal_type = detect_terminal_type();
	config->color_mode = parse_color_mode();
	config->is_color_active = should_enable_colors(
			config->color_mode, config->terminal_type);
	utf8_support = supports_utf8();
	config->prompt_style = parse_prompt_style(
			utf8_support, config->is_color_active);
	config->output_format = parse_output_format(config->is_color_active);
	config->prompt_type = PROMPT_PRIMARY;
	config->verbose = parse_verbose_level();
	config->is_enabled = 1;
	return (config);
}

void	free_display_config(t_display_config *config)
{
	if (config)
		free(config);
}
