/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:52:17 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/09 20:27:31 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

/*--------- general utilities --------------------------*/
int			is_builtin(char *cmd);
int			is_valid_identifier(char *str);
int			count_args(char **args);
int			is_numeric(char *str);
int			is_env_builtin(char *command);
int			close_and_exit(int	fd_in, int fd_out, int ex_status);
void		resolve_fd(int	*fd);
int			decide_command_type(char *command, t_env *env);
int			is_redirect_needed(t_command *cmd);
void		free_exec_and_exit(char *exec);
void		set_exit(t_ast_node *node, t_env *env);

/*--------- redirection utilities ----------------------*/
int			apply_redir_in(t_redirect *redir);
int			apply_redir_out(t_redirect *redir);
int			apply_append(t_redirect *redir);
int			apply_heredoc(t_redirect *redir);
int			apply_redirects(t_command *cmd);

/*--------- execiton main functions ----------------------*/
int			execute_ast(t_ast_node *node, t_env *env);
int			execute_command(t_command *cmd, t_env *env);
int			execute_redirects(t_command *command, int fd, t_env *env);
int			execute_pipe(t_ast_node *node, t_env *env);

/*--------- file builtin executor ------------------------*/
int			execute_builtin_files(char **args, t_env *env);

/*--------- general builtin executor ---------------------*/
int			execute_builtin(char **args, t_env *env);

#endif