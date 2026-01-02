/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:28:45 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/02 17:29:38 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static int	builtin_exit(char **args, t_env *env)
{
	int	exit_code;
	int	arg_count;

	ft_printf("exit\n");
	arg_count = count_args(args);
	if (arg_count == 1)
		exit(env->last_exit_status);
	if (!is_numeric(args[1]))
	{
		ft_printf("minishell: exit %s: numeric argument required\n", args[1]);
		exit(255);
	}
	if (arg_count > 2)
	{
		ft_printf("minishell: exit: too many arguments");
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	exit(exit_code % 256);
}

int	execute_builtin(char **args, t_env *env)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, env));
	if (ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "cd") == 0)
		return (execute_builtin_files(args, env));
	return (1);
}
