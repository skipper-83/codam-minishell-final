/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:40:21 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 12:58:01 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

void	sort_gobble_list(t_list *head);
int		reset_cmd(t_cmd *cmd, t_list *wc);
t_cmd	*cmd_from_char(char *literal);
char	*get_wc_string(t_list *wc);

int		check_wildcard(char *input, t_list *wildcard);

int		gobble(t_list **wc, t_list **start, t_list *last, t_cmd *prev);

int		count_pattern_repetitions(t_list *wc);
int		count_input_reps(t_list *wc, int pat_reps, char *input, int *i);
void	print_wc_to_stderr(void *param);

#endif