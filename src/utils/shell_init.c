/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:39:01 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 20:14:38 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

t_env	*init_shell(char **envp)
{
	t_env	*env;

	env = init_env(envp);
	if (!env)
		return (NULL);
	display_banner();
	return (env);
}

void	cleanup_shell(t_env *env)
{
	if (!env)
		return ;
	free_env(env);
}
