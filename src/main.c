/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:22:34 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 19:39:38 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	process_input(char *input, t_env *env)
{
	t_token		*tokens;
	t_ast_node	*tree;
	int			status;
	char		*debug_mode;

	debug_mode = getenv("DEBUG");
	tokens = lexer(input, 0);
	if (!tokens)
		return ;
	if (debug_mode && ft_strcmp(debug_mode, "1") == 0)
		print_tokens(tokens);
	tree = parse_tokens(tokens);
	if (!tree)
	{
		token_list_free(tokens);
		return ;
	}
	if (debug_mode && ft_strcmp(debug_mode, "1") == 0)
		print_ast(tree);
	status = execute_ast(tree, env);
	env->last_exit_status = status;
	node_free(tree);
	token_list_free(tokens);
}

static int	process_line(char *input, t_env *env)
{
	if (!input[0])
		return (0);
	add_history(input);
	process_input(input, env);
	handle_signal_after_execution();
	return (env->should_exit);
}

static void	shell_loop(t_env *env)
{
	char	*input;

	while (1)
	{
		input = readline(build_prompt());
		if (should_exit_shell(input))
		{
			ft_printf("exit\n");
			break ;
		}
		handle_signal_after_readline(&input);
		if (input && process_line(input, env))
		{
			free(input);
			break ;
		}
		if (input)
			free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		exit_code;

	(void)argc;
	(void)argv;
	env = init_shell(envp);
	if (!env)
		return (1);
	setup_signals_interactive();
	shell_loop(env);
	exit_code = env->exit_code;
	rl_clear_history();
	cleanup_shell(env);
	return (exit_code);
}
