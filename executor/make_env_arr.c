/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:51:51 by ewehl             #+#    #+#             */
/*   Updated: 2023/08/07 12:12:04 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of environment variables to export
 *
 * Iterates over a list of environment variables. For each variable marked
 * for export, the counter is incremented.
 *
 * @param env_vars A list of environment variables
 * @param cmd The command containing additional variables
 * @return int The number of variables to export
 */
static int	get_env_var_count(t_list *env_vars, t_cmd *cmd)
{
	int		cnt;
	t_list	*wrk_list;

	cnt = 0;
	wrk_list = env_vars;
	while (wrk_list)
	{
		if (((t_env_var *)wrk_list->content)->export)
			cnt++;
		wrk_list = wrk_list->next;
	}
	return (cnt + ft_lstsize(cmd->vars));
}

/**
 * @brief Copies environment variables into a newly allocated string array
 *
 * Iterates over a list of environment variables. For each variable marked
 * for export, a new string is created and stored in the resulting array.
 *
 * @param res A pointer to the string array where the environment 
 * 			variables will be stored
 * @param env_vars A list of environment variables
 * @return int The index of the last added variable
 */
static int	copy_env_vars(char **res, t_list *env_vars)
{
	int		idx;
	t_list	*wrk_list;

	idx = 0;
	wrk_list = env_vars;
	while (wrk_list)
	{
		if (((t_env_var *)wrk_list->content)->export)
		{
			res[idx] = make_env_arr_item(wrk_list->content);
			if (res[idx] == NULL)
				return (idx);
			idx++;
		}
		wrk_list = wrk_list->next;
	}
	return (idx);
}

/**
 * @brief Copies command-specific variables into a newly allocated string array
 *
 * Iterates over a list of command-specific variables. For each variable,
 * a new string is created and stored in the resulting array.
 *
 * @param res A pointer to the string array where the command-specific 
 * 	variables will be stored
 * @param cmd_vars A list of command-specific variables
 * @param start_idx The index in the array where to start adding the 
 * 	command-specific variables
 * @return int The number of command-specific variables added
 */
static int	copy_cmd_vars(char **res, t_list *cmd_vars, int start_idx)
{
	int		cnt;
	t_list	*wrk_list;

	cnt = 0;
	wrk_list = cmd_vars;
	while (wrk_list)
	{
		res[start_idx] = make_env_arr_item(wrk_list->content);
		if (res[start_idx] == NULL)
			return (cnt);
		start_idx++;
		cnt++;
		wrk_list = wrk_list->next;
	}
	return (cnt);
}

/**
 * @brief Allocates a new string array for environment variables
 *
 * The array is sized according to the count parameter and is 
 * initialized with * NULL at the last position. In case of memory 
 * allocation failure, an error message is printed.
 *
 * @param count The number of environment variables
 * @return char** A pointer to the newly allocated string array
 */
static char	**allocate_env_arr(int count)
{
	char	**res;

	res = (char **)malloc(sizeof(char *) * count + 1);
	if (res == NULL)
		return (print_error(ERR_MEM, NULL), NULL);
	res[count] = NULL;
	return (res);
}

/**
 * @brief Creates a  double string array of environment variables for
 * execution
 * Counts the total number of environment variables first. Then, allocates a
 * new string array and copies the environment and command-specific variables 
 * into this array.
 *
 * @param env The environment variables structure
 * @param cmd The command containing additional variables
 * @return char** A pointer to the newly created string array of 
 * 	environment variables
 */
char	**make_env_arr(t_env *env, t_cmd *cmd)
{
	int		e_vars_cnt;
	int		c_vars_cnt;
	char	**res;
	int		idx;

	e_vars_cnt = get_env_var_count(env->env_vars, cmd);
	res = allocate_env_arr(e_vars_cnt);
	if (res == NULL)
		return (NULL);
	idx = copy_env_vars(res, env->env_vars);
	if (res[idx] == NULL && idx < e_vars_cnt)
		return (free_2d_arr(res), mem_error(), NULL);
	c_vars_cnt = copy_cmd_vars(res, cmd->vars, idx);
	if (res[idx] == NULL && idx < (e_vars_cnt + c_vars_cnt))
		return (free_2d_arr(res), mem_error(), NULL);
	return (res);
}
