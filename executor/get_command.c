/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_command.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-and <avan-and@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/23 13:31:50 by ewehl         #+#    #+#                 */
/*   Updated: 2023/08/08 13:56:31 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Appends a '/' character to the end of each string in an array of paths.
 *
 * This function is useful to prepare a list of directories to be used for 
 * file or command searches.
 *
 * @param paths An array of strings each representing a path.
 * @return char** The modified array of paths.
 */
char	**append_slash(char **paths)
{
	char	*tmp;
	size_t	idx;

	idx = 0;
	while (paths[idx])
	{
		tmp = paths[idx];
		paths[idx] = ft_strjoin(tmp, "/");
		free(tmp);
		idx++;
	}
	return (paths);
}

/**
 * @brief Finds a command in the system's PATH directories.
 *
 * For each directory in the PATH, this function checks if the command 
 * is present (and executable) in the directory.
 *
 * @param cmd The command to find.
 * @param paths An array of strings each representing a path.
 * @return char* The complete path to the command if it is found. NULL otherwise.
 */
char	*cmd_pathfinder(char *cmd, char **paths)
{
	size_t	idx;
	char	*the_way;

	idx = 0;
	the_way = NULL;
	if (!cmd || !paths)
		return (NULL);
	while (paths[idx])
	{
		the_way = ft_strjoin(paths[idx], cmd);
		if (the_way == NULL)
			return (free_2d_arr(paths), print_error(ERR_MEM, NULL), NULL);
		if (access(the_way, F_OK) == 0)
		{
			if (access(the_way, X_OK) < 0)
				return (print_error(PERM_DEN, NULL), free(the_way), NULL);
			return (the_way);
		}
		free(the_way);
		idx++;
	}
	print_error("command not found", cmd);
	return (NULL);
}

char	*check_access(char **ret_cmd, t_cmd *cmd)
{
	*ret_cmd = ft_strjoin(cmd->path, cmd->literal);
	if (access(*ret_cmd, F_OK) == 0)
	{
		if (access(*ret_cmd, X_OK) < 0)
			return (print_error(PERM_DEN, NULL), free(*ret_cmd), NULL);
		return (*ret_cmd);
	}
	return (print_error(NO_FILE_DIR, *ret_cmd), free(*ret_cmd), NULL);
}

/**
 * @brief Finds the full path of a command.
 *
 * This function first checks if the command is a relative or absolute path.
 * If it is, it checks if the command is executable. If it isn't, it attempts
 * to find the command in the system's PATH directories.
 *
 * @param cmd The command structure that contains the command to find.
 * @param env The environment variables structure.
 * @return char* The complete path to the command if it is found. NULL otherwise.
 */
char	*get_cmd_path(t_cmd *cmd, t_env *env)
{
	char	**tmp_p;
	char	*ret_cmd;
	char	**tmp_path;
	char	*tmp_env_path;

	ret_cmd = NULL;
	if (cmd->path)
	{
		return (check_access(&ret_cmd, cmd));
	}
	tmp_env_path = get_env_value(env->env_vars, "PATH");
	if (tmp_env_path == NULL)
		return (print_error(NO_FILE_DIR, cmd->literal), NULL);
	tmp_path = ft_split(tmp_env_path, ':');
	if (tmp_path == NULL)
		return (print_error(ERR_MEM, NULL), NULL);
	tmp_p = append_slash(tmp_path);
	ret_cmd = cmd_pathfinder(cmd->literal, tmp_p);
	free_2d_arr(tmp_p);
	return (ret_cmd);
}
