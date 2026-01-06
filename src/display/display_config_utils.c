/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_config_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:09:50 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 18:00:51 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	is_tty_output(void)
{
	return (isatty(STDOUT_FILENO));
}

int	is_tty_input(void)
{
	return (isatty(STDIN_FILENO));
}

int	verify_utf8_variants(const char *str)
{
	char	*utf8_variants[5];
	size_t	i;

	utf8_variants[0] = ".utf8";
	utf8_variants[1] = ".UTF8";
	utf8_variants[2] = ".utf-8";
	utf8_variants[3] = ".UTF-8";
	utf8_variants[4] = NULL;
	i = 0;
	while (utf8_variants[i])
	{
		if (ft_strstr(str, utf8_variants[i]))
			return (1);
		i++;
	}
	return (0);
}

int	verify_undotted_utf8_variants(const char *str)
{
	char	*utf8_variants[5];
	size_t	i;

	utf8_variants[0] = "utf8";
	utf8_variants[1] = "UTF8";
	utf8_variants[2] = "utf-8";
	utf8_variants[3] = "UTF-8";
	utf8_variants[4] = NULL;
	i = 0;
	while (utf8_variants[i])
	{
		if (ft_strstr(str, utf8_variants[i]))
			return (1);
		i++;
	}
	return (0);
}

int	supports_utf8(void)
{
	char	*locale;

	locale = getenv("LANG");
	if (!locale)
		locale = getenv("LC_ALL");
	if (!locale)
		locale = getenv("LC_CTYPE");
	if (locale && (verify_utf8_variants(locale)
			|| verify_undotted_utf8_variants(locale)))
		return (1);
	return (0);
}
