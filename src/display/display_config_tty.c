/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_config_tty.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:11:48 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 18:15:25 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

t_terminal_type	detect_terminal_type(void)
{
	char	*term;

	term = getenv("TERM");
	if (!term || !term[0] || ft_strcmp(term, "dumb") == 0
		|| ft_strcmp(term, "unknown") == 0)
		return (TERMINAL_TYPE_DUMB);
	return (TERMINAL_TYPE_OTHER);
}
