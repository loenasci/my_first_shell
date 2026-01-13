/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:34:20 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/13 19:42:46 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	has_quotes(char c)
{
	return (c == '\'' || c == '"');
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	needs_expansion(char *str)
{
	if (!str)
		return (0);
	return (ft_strchr(str, '$') != NULL);
}
