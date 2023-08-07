/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ewehl <ewehl@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 17:44:19 by ewehl         #+#    #+#                 */
/*   Updated: 2023/08/04 19:20:50 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/**
 * @brief Writes user input to a file until a specific delimiter (lim) is entered
 *
 * Opens or creates a new file with writing permissions, then reads 
 * lines from the standard input 
 * and writes them to the file until the delimiter is entered. The file
 * is then closed.
 *
 * @param lim The delimiter that stops the writing to the file
 * @param filename The name of the file to write to
 * @return int 0 if successful, 1 if there was an error opening the file
 */
int	write_to_pipe(char *lim, char *filename)
{
	int		tmp_fd;
	char	*line;

	tmp_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
		return (1);
	ft_dprintf(1, "heredoc [%s%s%s] > ", RED, lim, ENDC);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if ((!ft_strncmp(line, lim, ft_strlen(lim)) \
			&& ft_strlen(lim) == (ft_strlen(line)) - 1))
			break ;
		else
			ft_dprintf(tmp_fd, line);
		free(line);
		ft_dprintf(1, "heredoc [%s%s%s] > ", RED, lim, ENDC);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(tmp_fd);
	return (0);
}

/**
 * @brief Handles the heredoc redirection in the shell
 *
 * Iterates over the list of heredocs. For each heredoc, a temporary
 * file is created and filled 
 * with the contents of the heredoc (done by calling write_to_pipe()).
 * The heredoc's file descriptor is then set to this temporary file's
 * descriptor, and the temporary file is deleted.
 *
 * @param env The environment variables structure
 * @return int 0 if successful, 1 if there was an error writing to a pipe
 */
int	redir_heredoc(t_env *env)
{
	int		tmp_fd;
	t_list	*wrk;
	int		counter;
	char	*filename;

	counter = 0;
	wrk = env->hdocs;
	while (wrk)
	{
		filename = ft_msprintf(".heredoc%i.tmp", counter);
		if (write_to_pipe(((t_cmd *)wrk->content)->literal, filename))
			return (unlink(filename), free(filename), 1);
		tmp_fd = open(filename, O_RDONLY);
		((t_cmd *)wrk->content)->fd = tmp_fd;
		unlink(filename);
		free(filename);
		wrk = wrk->next;
		counter++;
	}
	return (0);
}
