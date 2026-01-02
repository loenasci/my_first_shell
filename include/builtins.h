/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:08:41 by lsarraci          #+#    #+#             */
/*   Updated: 2025/12/16 17:09:44 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

/*--------- builtin commands -----------------*/
int	builtin_cd(char **args, t_env *env);
int	builtin_echo(char **args, t_env *env);
int	builtin_env(char **args, t_env *env);
int	builtin_exit(char **args, t_env *env);
int	builtin_export(char **args, t_env *env);
int	builtin_pwd(char **args, t_env *env);
int	builtin_unset(char **args, t_env *env);

#endif
