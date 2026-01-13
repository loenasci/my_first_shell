/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:46:11 by loda-sil          #+#    #+#             */
/*   Updated: 2026/01/13 19:00:31 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shell.h"

static char	*extract_var_name_from_raw(char *str, int *i)
{
	char	*var_name;
	int		len;
	int		braced;

	braced = 0;
	if (str[0] == '?')
		return (*i += 1, ft_strdup("?"));
	if (str[0] == '{')
	{
		braced = 1;
		str++;
		if (str[0] == '?')
			return (*i += 3, ft_strdup("?"));
	}
	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	if (braced && str[len] == '}')
		*i += len + 2;
	else
		*i += len;
	var_name = ft_substr(str, 0, len);
	return (var_name);
}

static char	*handle_dollar_expand(char *str, int *i, char *result)
{
	char	*var_name;
	char	*value;

	(*i)++;
	var_name = extract_var_name_from_raw(&str[*i], i);
	if (!var_name)
		return (free(result), NULL);
	if (ft_strcmp(var_name, "?") == 0)
		value = ft_itoa(get_exit_status());
	else
		value = expand_variable(var_name);
	result = join_and_free(result, value);
	free(var_name);
	free(value);
	return (result);
}

char	*expand_runtime_string(char *str, int i)
{
	char	*result;

	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (ft_substr(str, 1, ft_strlen(str) - 2));
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			result = handle_dollar_expand(str, &i, result);
		else
			result = join_char_and_free(result, str[i++]);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	**expand_args_runtime(char **raw_args)
{
	int		i;
	int		count;
	char	**expanded;

	count = 0;
	while (raw_args[count])
		count++;
	expanded = malloc((count + 1) * sizeof(char *));
	if (!expanded)
		return (NULL);
	i = 0;
	while (raw_args[i])
	{
		expanded[i] = expand_runtime_string(raw_args[i], 0);
		if (!expanded[i])
		{
			ft_free_split(expanded);
			return (NULL);
		}
		i++;
	}
	expanded[i] = NULL;
	return (expanded);
}
