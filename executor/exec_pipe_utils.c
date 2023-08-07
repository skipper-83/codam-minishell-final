/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:18:39 by ewehl             #+#    #+#             */
/*   Updated: 2023/08/07 15:28:42 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/**
 * @brief Checik if path is a dir
 * 
 * @param path 
 * @return int 
 */
int	is_dir(char	*path)
{
	struct stat	path_struct;

	stat(path, &path_struct);
	return (S_ISREG(path_struct.st_mode));
}

/**
 * @brief Creates the first process in a pipeline, where the output of the 
 * 			process is connected to a pipe for the next process.
 *
 * @param fi The first command to be executed.
 * @param fds An array of two integers representing the file descriptors for the 
 * 				pipe ends.
 * @param node The current node in the command tree to be executed.
 * @param env The environment in which the commands are executed.
 * @return int Returns 0 on successful execution.
 */
int	create_first_process(t_cmd *fi, int fds[2], t_btnode *node, t_env *env)
{
	fi->pid = fork();
	if (!fi->pid)
	{
		setup_pipe_ends(fds[WRITE], STDOUT_FILENO, fds[READ]);
		exit(execute_command_tree(node->left, env));
	}
	else if (fi->pid == -1)
		print_error(FORK_ERR, NULL);
	return (0);
}

/**
 * @brief Creates the last process in a pipeline, where the input of the process 
 * 			is connected from a pipe of the previous process.
 *
 * @param ls The last command to be executed.
 * @param fds An array of two integers representing the file descriptors for the 
 * 				pipe ends.
 * @param node The current node in the command tree to be executed.
 * @param env The environment in which the commands are executed.
 * @return int Returns 0 on successful execution.
 */
int	create_last_process(t_cmd *ls, int fds[2], t_btnode *node, t_env *env)
{
	ls->pid = fork();
	if (!ls->pid)
	{
		setup_pipe_ends(fds[READ], STDIN_FILENO, fds[WRITE]);
		exit(execute_command_tree(node->right, env));
	}
	else
	{
		if (ls->pid == -1)
			print_error(FORK_ERR, NULL);
		close(fds[READ]);
		close(fds[WRITE]);
		return (0);
	}
}

/**
 * @brief Executes a child process using the execve system call.
 *
 * @param cmd_path The path to the command to be executed.
 * @param cmd The command to be executed.
 * @param env_arr A null-terminated array of environment strings.
 * @return int Returns 127 on unsuccessful execution, corresponding 
 * 	to a command not found error.
 */
int	execute_child_process(char *cmd_path, t_cmd *cmd, char **env_arr)
{
	execve(cmd_path, cmd->arg_arr, env_arr);
	print_error(EXECVE_ERR, cmd->literal);
	exit(127);
}

/**
 * @brief Handles the fork of a process and the execution of a child process.
 *
 * @param cmd The command to be executed.
 * @param cmd_path The path to the command to be executed.
 * @param env_arr A null-terminated array of environment strings.
 * @return int Returns the exit status of the child process, or 0 if the 
 * 			function is called in the child process.
 */
int	handle_fork(t_cmd *cmd, char *cmd_path, char **env_arr)
{
	int	result;

	cmd->pid = fork();
	if (!cmd->pid)
		execute_child_process(cmd_path, cmd, env_arr);
	else
	{
		waitpid(cmd->pid, &result, 0);
		free_2d_arr(env_arr);
		free(cmd_path);
		return (result);
	}
	return (0);
}
