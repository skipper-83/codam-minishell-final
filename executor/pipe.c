/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:52:06 by ewehl             #+#    #+#             */
/*   Updated: 2023/08/07 12:08:53 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/**
 * @brief Set up the ends of a pipe
 *
 * Closes one end of the pipe and duplicates the old file descriptor
 * to a new one.
 * Also, the old file descriptor is closed afterwards. In case of a
 * duplication error, an error message is printed and 1 is returned.
 *
 * @param old_fd The old file descriptor
 * @param new_fd The new file descriptor
 * @param pipe_end_to_close The end of the pipe to close
 * @return int 0 if successful, 1 if there is a duplication error
 */
int	setup_pipe_ends(int old_fd, int new_fd, int pipe_end_to_close)
{
	close(pipe_end_to_close);
	if (dup2(old_fd, new_fd) == -1)
		return (print_error(DUP_ERR, NULL), 1);
	close(old_fd);
	return (0);
}

/**
 * @brief Duplicates file descriptors
 *
 * If the files parameter is not NULL, saves the current file descriptor
 * in the saved_fd variable and duplicates the command file descriptor to the 
 * standard one. In case of a duplication error, an error message is 
 * printed and -1 is returned.
 *
 * @param cmd_fd The command file descriptor
 * @param std_fd The standard file descriptor
 * @param files A pointer to the file
 * @return int The saved file descriptor, or -1 in case of a duplication error
 */
int	dup_files(int *cmd_fd, int std_fd, void *files)
{
	int	saved_fd;

	saved_fd = -2;
	if (files != NULL)
	{
		saved_fd = dup(std_fd);
		if (dup2(*cmd_fd, std_fd) < 0 || saved_fd < 0)
			return (print_error(DUP_ERR, NULL), -1);
	}
	return (saved_fd);
}

/**
 * @brief Resets a stream to its saved state
 *
 * If the saved stream file descriptor is valid (i.e., not negative), it 
 * is duplicated to the actual stream file descriptor. In case of a 
 * duplication error, an error message is printed and 1 is returned.
 *
 * @param save_stream The saved stream file descriptor
 * @param actual_stream The actual stream file descriptor
 * @return int 0 if successful, 1 if there is a duplication error
 */
int	reset_stream(int save_stream, int actual_stream)
{
	if (save_stream >= 0)
	{
		if (dup2(save_stream, actual_stream) == -1)
		{
			print_error(DUP_ERR, NULL);
			return (1);
		}
	}
	return (0);
}

/**
 * @brief Closes file descriptors and cleans up the open file
 * descriptors list
 *
 * Iterates over the list of open file descriptors.
 * For each descriptor, it is closed and the corresponding
 * list item is deleted.
 *
 * @param env The environment variables structure
 */
void	close_fds(t_env *env)
{
	t_list	*open_fds;
	t_list	*buf;
	int		fd;

	open_fds = env->open_fds;
	while (open_fds)
	{
		fd = ((t_cmd *)(open_fds->content))->fd;
		close(fd);
		buf = open_fds;
		open_fds = open_fds->next;
		ft_lstdel_item(&env->open_fds, buf, NULL);
	}
}
