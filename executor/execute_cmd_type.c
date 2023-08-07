/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 23:19:00 by ewehl             #+#    #+#             */
/*   Updated: 2023/08/07 15:45:20 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/**
 * @brief Executes a simple command.
 *
 * A simple command is one that does not involve any control operators 
 * (like &&, ||, ;, or |). First, the function checks if the command is a 
 * built-in command and tries to run it. If the command is not built-in, the 
 * function finds the path of the command executable,prepares the environment 
 * variables for the command, and executes the command in a new process.
 *
 * @param cmd The command structure.
 * @param env The environment variables structure.
 * @return int The return value of the command. If the command is not found, 
 * 			it returns 127 << 8.
 */
int	execute_simple_command(t_cmd *cmd, t_env *env)
{
	int		result;
	char	*cmd_path;
	char	**env_arr;

	result = run_builtins(cmd, env);
	if (result < 0)
	{
		cmd_path = get_cmd_path(cmd, env);
		if (cmd_path == NULL)
			return (127 << 8);
		if (!is_dir(cmd_path))
			return (print_error(IS_DIR, cmd_path), free(cmd_path), 126 << 8);
		env_arr = make_env_arr(env, cmd);
		if (env_arr == NULL)
			return (mem_error(), -1);
		result = handle_fork(cmd, cmd_path, env_arr);
		if (WIFSIGNALED(result))
			signal_message(128 + WTERMSIG(result));
	}
	return (result);
}

/**
 * @brief Executes a pipeline of commands.
 *
 * The function creates a pipe and executes the first command in the pipeline
 * with its stdout connected to the write end of the pipe, and the last command
 * with its stdin connected to the read end of the pipe. The function waits for
 * both commands to finish and returns the exit status of the last command.
 *
 * @param node The binary tree node containing the pipeline.
 * @param env The environment variables structure.
 * @return int The exit status of the last command in the pipeline.
 */
int	execute_pipe(t_btnode *node, t_env *env)
{
	int		retval;
	int		fds[2];
	t_cmd	*first;
	t_cmd	*last;

	if (node->right == NULL)
	{
		first = ((t_cmd *)node->left->content);
		first->infiles = ((t_cmd *)node->content)->infiles;
		((t_cmd *)node->content)->infiles = NULL;
		return (execute_command_tree(node->left, env));
	}
	first = ((t_cmd *)node->left->content);
	last = ((t_cmd *)node->right->content);
	if (pipe(fds) < 0)
		return (print_error(PIP_ERR, NULL), 1);
	create_first_process(first, fds, node, env);
	create_last_process(last, fds, node, env);
	waitpid(first->pid, &retval, 0);
	waitpid(last->pid, &retval, 0);
	return (retval);
}

/**
 * @brief Executes two commands connected by an AND operator.
 *
 * The function first executes the command on the left. If that command
 * succeeds (returns 0), it executes the command on the right and returns
 * its exit status.
 *
 * @param node The binary tree node containing the AND operator.
 * @param env The environment variables structure.
 * @return int The exit status of the last command executed.
 */
int	execute_and(t_btnode *node, t_env *env)
{
	int	retval;

	retval = execute_command_tree(node->left, env);
	if (!WEXITSTATUS(retval))
		retval = execute_command_tree(node->right, env);
	return (retval);
}

/**
 * @brief Executes two commands connected by an OR operator.
 *
 * The function first executes the command on the left. If that command fails
 * (returns non-zero), it executes the command on the right and returns its
 * exit status.
 *
 * @param node The binary tree node containing the OR operator.
 * @param env The environment variables structure.
 * @return int The exit status of the last command executed.
 */
int	execute_or(t_btnode *node, t_env *env)
{
	int	retval;

	retval = execute_command_tree(node->left, env);
	if (WEXITSTATUS(retval))
		retval = execute_command_tree(node->right, env);
	return (retval);
}

/**
 * @brief Executes two commands separated by a semicolon.
 *
 * The function first executes the command on the left, then the command on
 * the right, and returns the exit status of the last command executed.
 *
 * @param node The binary tree node containing the semicolon operator.
 * @param env The environment variables structure.
 * @return int The exit status of the last command executed.
 */
int	execute_semicolon(t_btnode *node, t_env *env)
{
	int	retval;

	retval = execute_command_tree(node->left, env);
	if (node->right != NULL)
		retval = execute_command_tree(node->right, env);
	return (retval);
}
