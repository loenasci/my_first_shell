/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_files.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:28:45 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/02 17:16:16 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static int	builtin_cd(char **args, t_env *env)
{
	(void)args;
	(void)env;
	return (0);
}

static int	builtin_pwd(char **args, t_env *env)
{
	char	buffer[PATH_MAX];

	(void)args;
	(void)env;
	if (!getcwd(buffer, PATH_MAX))
	{
		perror("pwd");
		return (1);
	}
	ft_printf("%s\n", buffer);
	return (0);
}

int	execute_builtin_files(char **args, t_env *env)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args, env));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, env));
	return (1);
}
