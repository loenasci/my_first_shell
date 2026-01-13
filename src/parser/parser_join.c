/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:42:08 by loda-sil          #+#    #+#             */
/*   Updated: 2026/01/13 19:42:29 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
	{
		if (s1)
			return (s1);
		if (s2)
			return (ft_strdup(s2));
		return (ft_strdup(""));
	}
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char	*join_and_free_both(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
	{
		if (s1)
		{
			free(s2);
			return (s1);
		}
		if (s2)
			return (s2);
		return (ft_strdup(""));
	}
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

char	*join_char_and_free(char *s, char c)
{
	char	*temp;
	char	char_str[2];

	char_str[0] = c;
	char_str[1] = '\0';
	temp = ft_strjoin(s, char_str);
	free(s);
	return (temp);
}
