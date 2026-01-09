/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:51:29 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/02 18:00:00 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	builtin_exit(char **args, t_env *env)
{
	int	exit_code;
	int	arg_count;

	ft_printf("exit\n");
	arg_count = count_args(args);
	if (arg_count == 1)
		exit_code = env->last_exit_status;
	else if (!is_numeric(args[1]))
	{
		ft_printf("minishell: exit %s: numeric argument required\n", args[1]);
		exit_code = 255;
	}
	else if (arg_count > 2)
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else
		exit_code = ft_atoi(args[1]);
	env->should_exit = 1;
	env->exit_code = exit_code % 256;
	return (0);
}
