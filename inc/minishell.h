/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:23:33 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 15:28:40 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <limits.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "error.h"
# include "defines_and_typedefs.h"
# include "debug.h"
# include "util.h"

// ugly hack to make the dang readline library work
void		rl_replace_line(const char *text, int clear_undo);

//  INIT

int			init(t_env **env, char **envp, char **buf, char **argv);
int			parse(t_env	*env, char *input);
void		prompt(char **buf, t_env *env);
void		execute(t_env *env, char *buf);

//  SIGS

void		signal_message(int signo);
void		sigint_reprompt(int signo);
void		empty_sighandler(int signo);

// PARSE

int			parse_quotes(t_env *env);
int			parse_command_list(t_list *cmd, t_env *env);
int			check_conditions(t_list *command, t_list **work, int level);
t_list		*make_command_list(t_token_lst *tok_list);
t_btnode	*make_command_tree(t_list *command);

// EXPAND

t_list		*make_env_list(char **envp);
int			parse_wildcard(t_list **command);
int			expand(t_list **cmd, t_env *env);
void		free_env_struct(void *param);
char		*get_env_value(t_list	*env, char *key);
t_list		*get_env_var(t_list	*env, char *key);

// EXECUTE

void		close_fds(t_env *env);
void		close_hdocs(t_env *env);
int			redir_heredoc(t_env *env);
int			execute_command_tree(t_btnode *node, t_env *env);
int			run_builtins(t_cmd *cmd, t_env *env);
int			is_var(char *input, int check_key);
int			check_var_key(char *input);
t_env_var	*make_var(char *input);

// UTIL

char		*get_lit(void *param);
char		*make_env_arr_item(void *param);
char		**list_to_arr(t_list *list, char *(*f)(void *param));
void		free_2d_arr(char **arr);
int			exit_ceash(t_env *env, t_cmd *cmd);
void		signal_message(int signo);

#endif