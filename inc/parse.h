/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:32:17 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/05 10:37:42 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

// infiles, outfiles, pipes, arguments

int		add_cmd_args(t_cmd **the_cmd, t_list **cmd, t_env *env, t_cmd *wrk_cmd);
int		add_infile(t_list **cmd, t_cmd *wrk_cmd, t_env *env);
int		add_outfile(t_list **cmd, t_list **top, t_cmd *wrk_cmd);
int		add_pipe(t_list **cmd, t_env *env, t_cmd **the_command, t_cmd *wrk_cmd);

// parse simple/bracketed command

t_cmd	*parse_simple_cmd(t_list *cmd, t_env *env, t_list **wrk);
t_cmd	*ret_parsed_cmd(t_cmd *c, t_list **wrk, t_list *cmd, t_cmd *wrk_cmd);
t_cmd	*parse_bracketed_cmd(t_list **cmd, t_env *env, t_cmd *wrk_cmd);

// parse quotes

int		comb_quoted_cmds(t_env *env, t_list **start, t_token_type qtype);
int		combine_commands(t_list *start, t_list *end);
int		handle_backslash(t_list **head, t_list **wrk, t_token_type qtype);

// util

int		get_path(t_cmd *cmd);
void	clear_inf_outf(t_cmd *wrk_cmd);
void	parse_error(void *param, char *description);
t_list	*get_prev(t_list *head, t_list *cur);

// parse var setters

t_list	*get_prev(t_list *head, t_list *cur);
int		make_var_set_cmd(t_cmd **the_command, t_env *env, t_list *prev);
int		add_var(t_list **vars, t_list **cmd, t_list **cmd_list);
// int		is_var(char *input);

#endif