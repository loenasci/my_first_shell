/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:44:11 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/11 15:56:43 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

char	*clear_heredoc_delimiter(char *delimiter)
{
	char	*cleaned;

	if (!delimiter)
		return (NULL);
	if (has_quotes(delimiter[0]))
		cleaned = ft_strtrim(delimiter, "\'\"");
	else
		cleaned = ft_strdup(delimiter);
	return (cleaned);
}

char	*extract_var_name_heredoc(char *start, int *len)
{
	int		i;
	char	*var_name;

	i = 0;
	if (!ft_isalpha(start[i]) && start[i] != '_')
	{
		*len = 0;
		return (ft_strdup(""));
	}
	while (start[i] && is_var_char(start[i]))
		i++;
	*len = i;
	var_name = ft_substr(start, 0, i);
	return (var_name);
}

void	write_line_to_pipe(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}
