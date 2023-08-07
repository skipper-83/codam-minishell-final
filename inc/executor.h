/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 23:19:09 by ewehl             #+#    #+#             */
/*   Updated: 2023/08/07 15:28:59 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <string.h>
# include <sys/errno.h>
# include "error.h"

# define READ 0
# define WRITE 1

char	**make_env_arr(t_env *env, t_cmd *cmd);

int		handle_fork(t_cmd *cmd, char *cmd_path, char **env_arr);
int		create_first_process(t_cmd *fi, int fds[2], t_btnode *node, t_env *env);
int		create_last_process(t_cmd *ls, int fds[2], t_btnode *node, t_env *env);

int		execute_or(t_btnode *node, t_env *env);
int		execute_and(t_btnode *node, t_env *env);
int		execute_pipe(t_btnode *node, t_env *env);
int		execute_semicolon(t_btnode *node, t_env *env);
int		execute_simple_command(t_cmd *cmd, t_env *env);
int		get_exec_type(t_cmd *cmd, t_btnode *node, t_env *env);

int		dup_files(int *cmd_fd, int std_fd, void *files);
int		reset_stream(int save_stream, int actual_stream);
int		setup_pipe_ends(int old_fd, int new_fd, int pipe_end_to_close);

int		open_infiles(t_cmd *cmd, t_env *env);
int		create_outfiles(t_cmd *cmd, t_env *env);
void	check_files(t_cmd *file_cmd, int io);

char	**append_slash(char **paths);
char	*cmd_pathfinder(char *cmd, char **paths);
char	*get_cmd_path(t_cmd *cmd, t_env *env);

void	clean_up(t_env **env, int *save_in, int *save_out, int *retval);
int		is_dir(char	*path);

#endif