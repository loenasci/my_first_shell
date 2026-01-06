/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:58 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 18:26:11 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

t_display_config	*init_display(void)
{
	t_display_config	*config;
	char				*term;
	char				*no_color;
	char				*verbose;

	config = malloc(sizeof(t_display_config));
	if (!config)
		return (NULL);
	term = getenv("TERM");
	no_color = getenv("NO_COLOR");
	verbose = getenv("VERBOSE");
	config->terminal_type = detect_terminal_type();
	config->verbose = get_verbose_mode(config);
	config->color_mode = COLOR_MODE_AUTO;
	if (no_color && no_color[0])
		config->color_mode = COLOR_MODE_NEVER;
	else if (config->terminal_type != TERMINAL_TYPE_DUMB
		&& is_tty_output())
		config->color_mode = COLOR_MODE_ALWAYS;
	return (config);
}
