/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:23:50 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/11 15:54:54 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

char	*read_heredoc_line(void)
{
	char	*line;
	size_t	len;

	if (isatty(STDIN_FILENO))
		return (readline("> "));
	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

int	is_delimiter_reached(char *line, char *clean_delim)
{
	if (!line)
		return (1);
	if (ft_strcmp(line, clean_delim) == 0)
		return (1);
	return (0);
}

int	process_heredoc(char *delimiter)
{
	int		pipe_fds[2];
	char	*clean_delim;

	pipe(pipe_fds);
	clean_delim = clear_heredoc_delimiter(delimiter);
	signal_enter_heredoc();
	read_heredoc_content(pipe_fds[1], delimiter, clean_delim);
	signal_exit_heredoc();
	free(clean_delim);
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}
