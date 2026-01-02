/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:28:45 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/02 18:38:59 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	execute_builtin_command(char **args, t_env *env)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args, env));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args, env));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, env));
	return (1);
}
