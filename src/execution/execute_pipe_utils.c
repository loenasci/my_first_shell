/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:26:48 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/13 19:46:22 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

void	pipe_exit_with(char **args, const char *msg, int code)
{
	ft_printf("%s: %s\n", args[0], msg);
	ft_free_split(args);
	exit(code);
}

void	set_exit(t_ast_node *node, t_env *env)
{
	char	**expanded;
	int		ret;

	if (!node)
		exit(1);
	if (node->type == NODE_PIPE)
		exit(execute_pipe(node, env));
	if (node->type != NODE_COMMAND || !node->cmd)
		exit(1);
	if (!node->cmd->args || !node->cmd->args[0])
		exit(0);
	expanded = expand_args_runtime(node->cmd->args);
	if (!expanded)
		exit(1);
	if (is_builtin(expanded[0]))
	{
		ret = execute_builtin(expanded, env);
		ft_free_split(expanded);
		exit(ret);
	}
	ft_free_split(expanded);
}

void	free_exec_and_exit(char *exec)
{
	free(exec);
	exit(1);
}

void	do_pipe_execve(char **args, char *exec, t_env *env)
{
	char	**envp;

	envp = env_to_array(env);
	if (!envp)
	{
		ft_free_split(args);
		free_exec_and_exit(exec);
	}
	execve(exec, args, envp);
	ft_printf("%s: execution failed\n", args[0]);
	free_env_array(envp);
	ft_free_split(args);
	free(exec);
	exit(126);
}
