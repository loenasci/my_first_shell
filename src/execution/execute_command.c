/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:54:59 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/09 19:26:09 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static void	child_process(t_command *cmd, char *executable, t_env *env)
{
	char	**envp;

	restore_signals_default();
	if (!apply_redirects(cmd))
		exit(1);
	envp = env_to_array(env);
	if (!envp)
		exit(1);
	execve(executable, cmd->args, envp);
	ft_printf("%s: execution failed\n", cmd->args[0]);
	free_env_array(envp);
	exit(126);
}

static int	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	setup_signals_interactive();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_command(t_command *cmd, t_env *env)
{
	char	*executable;
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd->args, env));
	executable = find_executable(cmd->args[0], env);
	if (!executable)
	{
		ft_printf("%s: command not found\n", cmd->args[0]);
		return (127);
	}
	setup_signals_executing();
	pid = fork();
	if (pid == -1)
	{
		free(executable);
		perror("fork");
		return (1);
	}
	if (pid == 0)
		child_process(cmd, executable, env);
	free(executable);
	return (wait_child(pid));
}
