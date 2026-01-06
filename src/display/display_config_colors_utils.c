/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_config_colors_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:26:48 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 18:58:54 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	check_if_color(t_display_config *config)
{
	if (!config || !config->is_enabled)
		return (0);
	return (config->is_color_active);
}

const char	*get_color_by_config(t_display_config *config, const char *color)
{
	if (check_if_color(config))
		return (color);
	return ("");
}

t_prompt_style	parse_prompt_style(void)
{
	char	*style;
	int		supports;
	int		colors;

	supports = supports_utf8();
	colors = check_if_color(NULL);
	style = getenv("MYSH_PROMPT_STYLE");
	if (style)
	{
		if (ft_strcmp(style, "minimal") == 0)
			return (PROMPT_STYLE_MINIMAL);
		if (ft_strcmp(style, "fancy") == 0)
			return (PROMPT_STYLE_FANCY);
		if (ft_strcmp(style, "detailed") == 0)
			return (PROMPT_STYLE_DETAILED);
	}
	if (supports && colors)
		return (PROMPT_STYLE_FANCY);
	if (!supports)
		return (PROMPT_STYLE_MINIMAL);
	return (PROMPT_STYLE_DEFAULT);
}
