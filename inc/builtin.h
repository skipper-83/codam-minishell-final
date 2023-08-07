/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:37:14 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 16:27:14 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

# define ONLY_ENV 0
# define LOCAL_AND_ENV 1
# define ONLY_LOCAL 2

int	exit_ceash(t_env *env, t_cmd *cmd);
int	env_builtin(t_env *env, t_cmd *cmd);
int	cd(t_cmd *cmd, t_env *env);
int	echo(t_cmd *cmd);
int	pwd(t_cmd *cmd, t_env *env);
int	set_local_vars(t_cmd *cmd, t_env *env);
int	unset(t_cmd *cmd, t_env *env);
int	export_ceash(t_cmd *cmd, t_env *env);

int	print_export_list(t_cmd *cmd, t_env *env);

#endif
