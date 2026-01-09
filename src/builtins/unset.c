/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:44:06 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/09 17:07:01 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

int	builtin_unset(char **args, t_env *env)
{
	int i;

	if (!env)
		return (1);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_printf("minishell: unset: '%s': not a valid identifier\n", args[i]);
			return (1);
		}
		else
			env_unset(env, args[i]);
		i++;
	}
	return (0);
}
