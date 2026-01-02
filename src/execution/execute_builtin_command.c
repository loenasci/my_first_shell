/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:28:45 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/02 17:42:54 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static int	builtin_export(char **args, t_env *env)
{
	(void)args;
	(void)env;
	return (0);
}

static int	builtin_unset(char **args, t_env *env)
{
	(void)args;
	(void)env;
	return (0);
}

static int	builtin_env(char **args, t_env *env)
{
	(void)args;
	(void)env;
	return (0);
}

static int	builtin_echo(char **args, t_env *env)
{
	(void)args;
	(void)env;
	return (0);
}

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
	return (1);
}
