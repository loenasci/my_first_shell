/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:54:59 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/09 17:50:15 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static void	child_process(char *executable, char **args, t_env *env)
{
	char	**envp;

	restore_signals_default();
	envp = env_to_array(env);
	if (!envp)
		exit(1);
	execve(executable, args, envp);
	ft_printf("%s: execution failed\n", args[0]);
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
	ft_printf("minishell: command not found: %s\n", cmd->args[0]);
	return (127);
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
		child_process(executable, cmd->args, env);
	free(executable);
	return (wait_child(pid));
}
