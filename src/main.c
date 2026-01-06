/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:22:34 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 19:15:51 by lsarraci         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_env				*env;
	t_display_config	*display;

	(void)argc;
	(void)argv;
	display = init_display();
	if (!display)
		return (1);
	env = init_env(envp);
	if (!env)
	{
		free_display_config(display);
		return (1);
	}
	env->display = display;
	display_banner();
	setup_signals_interactive();
	while (1)
	{
		input = readline(build_prompt(display));
		if (!input)
			break ;
		if (input[0])
		{
			add_history(input);
			process_input(input, env);
		}
		free(input);
	}
	free_env(env);
	free_display_config(display);
	return (0);
}
