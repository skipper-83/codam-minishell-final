/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_tree.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ewehl <ewehl@student.						  +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 23:10:42 by ewehl		   #+#    #+#                 */
/*   Updated: 2023/07/09 11:52:25 by eluse         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/**
 * @brief Executes a subtree command and manages child process.
 *
 * @param cmd The command to be executed.
 * @param env The environment in which the commands are executed.
 * @param node The current node in the command tree to be executed.
 * @return int Returns the exit status of the command.
 */
int	check_subtree(t_cmd *cmd, t_env *env, t_btnode *node)
{
	int	status;

	status = -1;
	cmd->pid = fork();
	if (cmd->pid)
	{
		waitpid(cmd->pid, &status, 0);
		return (status >> 8);
	}
	else if (cmd->pid == 0)
	{
		cmd->is_subtree = 2;
		env->test += 2;
		exit(execute_command_tree(node, env));
	}
	perror(strerror(errno));
	exit(errno);
}

/**
 * @brief Retrieves command and file descriptors from the given 
 * 			node and environment.
 *
 * @param cmd Double pointer to the command to be executed.
 * @param node The current node in the command tree to be executed.
 * @param env The environment in which the commands are executed.
 */
void	get_cmd_and_fds(t_cmd **cmd, t_btnode *node, t_env *env)
{
	*cmd = (t_cmd *)node->content;
	(*cmd)->infile_fd = open_infiles(*cmd, env);
	(*cmd)->outfile_fd = create_outfiles(*cmd, env);
}

/**
 * @brief Determines the type of command to be executed and calls 
 * 		the corresponding execution function.
 *
 * @param cmd The command to be executed.
 * @param node The current node in the command tree to be executed.
 * @param env The environment in which the commands are executed.
 * @return int Returns the result of the executed command.
 */
int	get_exec_type(t_cmd *cmd, t_btnode *node, t_env *env)
{
	int	retval;

	if (cmd->type == LITERAL)
		retval = execute_simple_command(cmd, env);
	else if (cmd->type == PIPE)
		retval = execute_pipe(node, env);
	else if (cmd->type == AMP_2)
		retval = execute_and(node, env);
	else if (cmd->type == PIPE_2)
		retval = execute_or(node, env);
	else
		retval = execute_semicolon(node, env);
	return (retval);
}

/**
 * 
 * @brief	Go through branches of binary tree recursively and select
 * 			the correct function for eacht command type
 * 
 * @param node	the node to be executed, tree root on first call
 * @return int the result of the last command executed
 */
int	execute_command_tree(t_btnode *node, t_env *env)
{
	t_cmd	*cmd;
	int		retval;
	int		save_in;
	int		save_out;

	get_cmd_and_fds(&cmd, node, env);
	if (cmd->is_subtree == 1)
		return (check_subtree(cmd, env, node));
	if (cmd->infile_fd < 0 || cmd->outfile_fd < 0)
		return (1);
	save_in = dup_files(&(cmd->infile_fd), STDIN_FILENO, cmd->infiles);
	save_out = dup_files(&(cmd->outfile_fd), STDOUT_FILENO, cmd->outfiles);
	if (save_in == -1 || save_out == -1)
		return (1);
	retval = get_exec_type(cmd, node, env);
	clean_up(&env, &save_in, &save_out, &retval);
	return (retval);
}
