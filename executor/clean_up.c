/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:37:19 by ewehl             #+#    #+#             */
/*   Updated: 2023/08/07 11:45:29 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/**
 * @brief Print an error message to the error output stream.
 *
 * @param msg The primary error message to be printed.
 * @param msg2 An optional secondary message to be printed in brackets. 
 * 			If NULL, only the primary message is printed.
 */
void	print_error(char *msg, char *msg2)
{
	if (msg2 == NULL)
		ft_dprintf(2, "minishell: %s\n", msg);
	else
		ft_dprintf(2, "minishell: %s [%s]\n", msg, msg2);
}

/**
 * @brief Close all here-document (hdoc) files and remove their corresponding 
 * 		nodes from the hdocs list in the environment.
 *
 * @param env Pointer to the environment in which the commands were executed.
 */
void	close_hdocs(t_env *env)
{
	t_list	*wrk_list;
	t_list	*buf;
	int		fd;

	if (!env->hdocs || !env->hdocs->content)
		return ;
	wrk_list = env->hdocs;
	while (wrk_list)
	{
		fd = ((t_cmd *)wrk_list->content)->fd;
		close(fd);
		buf = wrk_list;
		wrk_list = wrk_list->next;
		ft_lstdel_item(&env->hdocs, buf, NULL);
	}
}

/**
 * @brief Cleans up the environment and file descriptors after command execution.
 *
 * @param env Double pointer to the environment in which the commands 
 * 			were executed.
 * @param save_in Pointer to the input file descriptor.
 * @param save_out Pointer to the output file descriptor.
 * @param retval Pointer to the return value of the command.
 */
void	clean_up(t_env **env, int *save_in, int *save_out, int *retval)
{
	close_fds(*env);
	reset_stream(*save_out, STDOUT_FILENO);
	reset_stream(*save_in, STDIN_FILENO);
	if (WTERMSIG(*retval))
		*retval = 128 + WTERMSIG(*retval);
	else
		*retval = WEXITSTATUS(*retval);
}
