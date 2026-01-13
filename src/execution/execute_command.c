/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:54:59 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/13 19:13:01 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static void	child_process_expanded(t_command *cmd, char *executable,
	t_env *env, char **expanded_args)
{
	char	**envp;

	restore_signals_default();
	if (!apply_redirects(cmd))
	{
		ft_free_split(expanded_args);
		free(executable);
		exit(1);
	}
	envp = env_to_array(env);
	if (!envp)
	{
		ft_free_split(expanded_args);
		free(executable);
		exit(1);
	}
	execve(executable, expanded_args, envp);
	ft_printf("%s: execution failed\n", expanded_args[0]);
	free_env_array(envp);
	ft_free_split(expanded_args);
	free(executable);
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

int	fork_and_execute_with_expanded(t_command *cmd, char *executable,
	t_env *env, char **expanded_args)
{
	pid_t	pid;

	setup_signals_executing();
	pid = fork();
	if (pid == -1)
	{
		free(executable);
		perror("fork");
		return (1);
	}
	if (pid == 0)
		child_process_expanded(cmd, executable, env, expanded_args);
	free(executable);
	return (wait_child(pid));
}

static int	execute_builtin_command(t_command *cmd, char **expanded_args,
			t_env *env)
{
	int	ret;

	if (cmd->redirects)
		ret = execute_redirects(cmd, -1, env, expanded_args);
	else
		ret = execute_builtin(expanded_args, env);
	return (ret);
}

int	execute_command(t_command *cmd, t_env *env)
{
	int		handled;
	char	**expanded_args;
	int		ret;

	handled = empty_handle_manager(cmd, env);
	if (handled != -1)
		return (handled);
	expanded_args = expand_args_runtime(cmd->args);
	if (!expanded_args)
		return (1);
	if (is_builtin(expanded_args[0]))
		ret = execute_builtin_command(cmd, expanded_args, env);
	else
		ret = execute_external_process(cmd, expanded_args, env);
	ft_free_split(expanded_args);
	return (ret);
}
