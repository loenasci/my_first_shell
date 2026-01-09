/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:52:17 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/07 21:45:53 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

/*--------- execution utilities --------------------------*/
int			is_builtin(char *cmd);
int			is_valid_identifier(char *str);
int			count_args(char **args);
int			is_numeric(char *str);
void		set_exit(t_ast_node *node, t_env *env);
void		free_exec_and_exit(char *exec);

/*--------- execiton main functions ----------------------*/
int			execute_ast(t_ast_node *node, t_env *env);
int			execute_command(t_command *cmd, t_env *env);
int			execute_pipe(t_ast_node *node, t_env *env);

/*--------- general builtin executor ---------------------*/
int			execute_builtin(char **args, t_env *env);

#endif
