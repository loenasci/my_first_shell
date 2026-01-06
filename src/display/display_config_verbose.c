/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_config_verbose.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:10:59 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 18:25:52 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static int	is_verbose_off(const char *value)
{
	return (ft_strcmp(value, "0") == 0
		|| ft_strcmp(value, "off") == 0
		|| ft_strcmp(value, "false") == 0
		|| ft_strcmp(value, "no") == 0);
}

static int	is_verbose_max(const char *value)
{
	return (ft_strcmp(value, "2") == 0
		|| ft_strcmp(value, "verbose") == 0
		|| ft_strcmp(value, "debug") == 0);
}

t_verbose	parse_verbose_level(void)
{
	char	*verbose;

	verbose = getenv("VERBOSE");
	if (!verbose)
	{
		if (is_tty_input())
			return (NONVERBOSE);
		return (OFF);
	}
	if (is_verbose_off(verbose))
		return (OFF);
	if (is_verbose_max(verbose))
		return (VERBOSE);
	return (NONVERBOSE);
}

int	should_print_message(t_display_config *config, t_verbose min_level)
{
	if (!config || !config->is_enabled)
		return (0);
	if (config->verbose == OFF)
		return (0);
	if (config->verbose >= min_level)
		return (1);
	return (0);
}
