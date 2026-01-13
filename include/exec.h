/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:52:17 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/13 19:46:51 by loda-sil         ###   ########.fr       */
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
int			close_and_exit(int fd_in, int fd_out, int ex_status);
void		resolve_fd(int	*fd);
int			decide_command_type(char **args, t_env *env);
int			is_redirect_needed(t_command *cmd);
void		free_exec_and_exit(char *exec);
void		set_exit(t_ast_node *node, t_env *env);
void		do_pipe_execve(char **args, char *exec, t_env *env);
void		pipe_exit_with(char **args, const char *msg, int code);

/*--------- redirection utilities ----------------------*/
int			apply_redir_in(t_redirect *redir);
int			apply_redir_out(t_redirect *redir);
int			apply_append(t_redirect *redir);
int			apply_heredoc(t_redirect *redir);
int			apply_redirects(t_command *cmd);
int			empty_handle_manager(t_command *cmd, t_env *env);

/*--------- execuiton main functions ----------------------*/
int			execute_ast(t_ast_node *node, t_env *env);
int			execute_command(t_command *cmd, t_env *env);
int			execute_redirects(t_command *command, int fd, t_env *env,
				char **expanded);
int			execute_pipe(t_ast_node *node, t_env *env);
int			execute_logical_and(t_ast_node *left, t_ast_node *right,
				t_env *env);
int			execute_logical_or(t_ast_node *left, t_ast_node *right,
				t_env *env);
char		*define_executable(t_command *cmd, t_env *env);

int			execute_external_command(char **args, t_env *env);
int			fork_and_execute_with_expanded(t_command *cmd, char *executable,
				t_env *env, char **expanded_args);
int			execute_external_process(t_command *cmd, char **expanded_args,
				t_env *env);

/*--------- expansion variables utilities  ---------------*/
char		**expand_args_runtime(char **raw_args);
char		*expand_runtime_string(char *str, int i);

/*--------- file builtin executor ------------------------*/
int			execute_builtin_files(char **args, t_env *env);

/*--------- general builtin executor ---------------------*/
int			execute_builtin(char **args, t_env *env);

#endif
