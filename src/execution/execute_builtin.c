/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:28:45 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/07 21:22:07 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	execute_builtin(char **args, t_env *env)
{
	if	(!args || !args[0])
		return (1);
	if	(ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, env));
	if	(ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, env));
	if	(ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args, env));
	if	(ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, env));
	if	(ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args, env));
	if	(ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, env));
	if	(ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, env));
	return (1);
}
