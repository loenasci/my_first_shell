/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:57:17 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/08 17:29:32 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "structs.h"

/* ---------------   signals setup -------------------------*/

void			setup_signals_interactive(void);
void			setup_signals_executing(void);
void			setup_signals_heredoc(void);

/* ---------------signal utilities -------------------------*/

void			handle_sigint(int sig);
void			handle_sigquit(int sig);
void			restore_signals_default(void);
void			set_exit(t_ast_node *node, t_env *env);

/* ---------------signal state management ------------------*/

t_signal_state	*get_signal_state(void);
void			signal_clear(void);
void			signal_enter_heredoc(void);
void			signal_exit_heredoc(void);

#endif
