/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_config_colors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:10:37 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 18:48:10 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

t_color_mode	parse_color_mode(void)
{
	char	*no_color;
	char	*color;

	no_color = getenv("NO_COLOR");
	if (no_color)
		return (COLOR_MODE_NEVER);
	color = getenv("COLOR");
	if (color)
	{
		if (ft_strcmp(color, "always") == 0)
			return (COLOR_MODE_ALWAYS);
		if (ft_strcmp(color, "never") == 0)
			return (COLOR_MODE_NEVER);
	}
	return (COLOR_MODE_AUTO);
}

int	should_enable_colors(t_color_mode mode, t_terminal_type term_type)
{
	if (mode == COLOR_MODE_NEVER)
		return (0);
	if (mode == COLOR_MODE_ALWAYS)
		return (1);
	if (term_type != TERMINAL_TYPE_DUMB && is_tty_output())
		return (1);
	return (0);
}
