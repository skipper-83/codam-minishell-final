/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:59:01 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 16:27:28 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

/**
 * @brief Executes built-in commands based on the command literal,
 * returning a status value upon completion.
 *
 * @param cmd The command to be executed.
 * @param env The environment in which the command is executed.
 * @return int Returns the status of the command execution, -1 if
 * command is not recognized as a built-in.
 */
int	run_builtins(t_cmd *cmd, t_env *env)
{
	if (cmd->is_var_setter)
		return (set_local_vars(cmd, env));
	if (!ft_strcmp(cmd->literal, "cd"))
		return (cd(cmd, env));
	if (!ft_strcmp(cmd->literal, "pwd"))
		return (pwd(cmd, env));
	if (!ft_strcmp(cmd->literal, "env"))
		return (env_builtin(env, cmd));
	if (!ft_strcmp(cmd->literal, "exit"))
		return (exit_ceash(env, cmd));
	if (!ft_strcmp(cmd->literal, "echo"))
		return (echo(cmd));
	if (!ft_strcmp(cmd->literal, "export"))
		return (export_ceash(cmd, env));
	if (!ft_strcmp(cmd->literal, "unset"))
		return (unset(cmd, env));
	return (-1);
}
