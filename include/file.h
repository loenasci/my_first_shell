/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:16:30 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/08 15:44:15 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "structs.h"

/* ---------------   Path Management  ----------------------*/
char	*find_executable(char *cmd, t_env *env);
char	**get_default_path(t_env *env);

/* ---------------   File Utilities  -----------------------*/
int		is_directory(const char *path);
void	cache_executables(t_env *env);
int		validate_executable(char *path);

#endif