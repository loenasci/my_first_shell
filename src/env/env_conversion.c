/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:46:23 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/02 18:34:17 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static int	count_env_vars(t_env *env)
{
	t_env_var	*current;
	int			count;

	if (!env)
		return (0);
	count = 0;
	current = env->vars;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static char	*create_env_string(t_env_var *node)
{
	char	*temp;
	char	*result;

	if (!node || !node->key || !node->value)
		return (NULL);
	temp = ft_strjoin(node->key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, node->value);
	free(temp);
	return (result);
}

char	**env_to_array(t_env *env)
{
	char		**envp;
	t_env_var	*current;
	int			count;
	int			i;

	count = count_env_vars(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	current = env->vars;
	i = 0;
	while (current)
	{
		envp[i] = create_env_string(current);
		if (!envp[i])
		{
			free_env_array(envp);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_env_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
