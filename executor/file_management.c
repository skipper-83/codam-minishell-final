/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:09:13 by ewehl             #+#    #+#             */
/*   Updated: 2023/08/07 16:03:06 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/**
 * @brief Opens the input files for a command.
 *
 * The command structure contains a list of input files, which are opened for 
 * reading in this function. Each file is added to the list of open file 
 * descriptors in the environment structure.
 *
 * @param cmd The command that might need input files.
 * @param env The environment variables structure that also contains the list of 
 * 	open file descriptors.
 * @return int The file descriptor of the last input file opened. 
 * 	If no file is opened, it returns 0. If an error occurs, it returns -1.
 */
int	open_infiles(t_cmd *cmd, t_env *env)
{
	t_list	*wrk_list;
	t_list	*infiles;
	t_cmd	*file_cmd;

	infiles = cmd->infiles;
	if (infiles == NULL)
		return (0);
	while (infiles)
	{
		file_cmd = (t_cmd *)infiles->content;
		if (file_cmd->type == SMALLER)
		{
			file_cmd->fd = open(file_cmd->literal, O_RDONLY);
			if (file_cmd->fd < 0)
				return (print_error(INF_ERR, file_cmd->literal), -1);
			wrk_list = ft_lstnew(file_cmd);
			if (wrk_list == NULL)
				return (mem_error(), -1);
			ft_lstadd_front(&env->open_fds, wrk_list);
		}
		infiles = infiles->next;
	}
	return (file_cmd->fd);
}

/**
 * @brief Creates or opens the output files for a command.
 *
 * The command structure contains a list of output files, which are created or 
 * opened for writing in this function. Each file is added to the list of open 
 * file descriptors in the environment structure.
 *
 * @param cmd The command that might need output files.
 * @param env The environment variables structure that also contains the list of 
 * 	open file descriptors.
 * @return int The file descriptor of the last output file opened. If no file is 
 * 	opened, it returns 0. If an error occurs, it returns -1.
 */
int	create_outfiles(t_cmd *cmd, t_env *env)
{
	t_list	*wrk_list;
	t_list	*outfiles;
	t_cmd	*file_cmd;

	outfiles = cmd->outfiles;
	if (outfiles == NULL)
		return (0);
	while (outfiles)
	{
		file_cmd = (t_cmd *)outfiles->content;
		if (file_cmd->type == GREATER_2)
			file_cmd->fd = open(file_cmd->literal, \
							O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			file_cmd->fd = open(file_cmd->literal, \
							O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_cmd->fd < 0)
			return (print_error(OUTF_ERR, file_cmd->literal), -1);
		wrk_list = ft_lstnew(file_cmd);
		if (wrk_list == NULL)
			return (mem_error(), -1);
		ft_lstadd_front(&env->open_fds, wrk_list);
		outfiles = outfiles->next;
	}
	return (file_cmd->fd);
}

/**
 * @brief Checks the permissions on a file.
 *
 * Depending on the parameter io, the function checks if the file can 
 * be read (if io is 1) or written (if io is anything else).
 *
 * @param file_cmd The command structure that contains the file to check.
 * @param io An integer that determines the type of permission to check.
 */
void	check_files(t_cmd *file_cmd, int io)
{
	if (io == 1)
	{
		if (access(file_cmd->literal, F_OK) < 0)
			print_error(strerror(errno), NULL);
		if (access(file_cmd->literal, R_OK) < 0)
			print_error(PERM_DEN, file_cmd->literal);
	}
	else
	{
		if (access(file_cmd->literal, W_OK) < 0)
			print_error(strerror(errno), NULL);
	}
}
