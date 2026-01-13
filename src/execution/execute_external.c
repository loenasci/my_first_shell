/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:45:48 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/13 17:10:42 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	execute_external_command(char **args, t_env *env)
{
	t_command	cmd;

	if (!args || !args[0])
		return (0);
	cmd.args = args;
	cmd.redirects = NULL;
	return (execute_command(&cmd, env));
}

int	execute_external_process(t_command *cmd, char **expanded_args,
	t_env *env)
{
	char	*executable;
	int		ret;

	executable = find_executable(expanded_args[0], env);
	if (executable == (char *)-1)
		return (126);
	if (!executable)
	{
		if (ft_strchr(expanded_args[0], '/') && is_directory(expanded_args[0]))
		{
			ft_printf("%s: Is a directory\n", expanded_args[0]);
			return (126);
		}
		ft_printf("%s: command not found\n", expanded_args[0]);
		return (127);
	}
	ret = fork_and_execute_with_expanded(cmd, executable, env, expanded_args);
	return (ret);
}
