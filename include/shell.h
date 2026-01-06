/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:23:21 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 16:34:52 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "builtins.h"
# include "display.h"
# include "exec.h"
# include "lexer.h"
# include "parser.h"
# include "signals.h"
# include "structs.h"
# include "types.h"
# include "lexer.h"
# include "debug.h"
# include "env.h"
# include "file.h"

# define PATH_MAX	4096
# define MAX_COMMAND_LENGTH 131072

/* Exit status management */
void	set_exit_status(int status);
int		get_exit_status(void);

#endif
