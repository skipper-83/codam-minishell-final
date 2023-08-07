/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:47:01 by albertvanan       #+#    #+#             */
/*   Updated: 2023/06/08 12:54:12 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief	Adds infile to wrk_cmd struct.
 * 
 * @param cmd	t_list item with the current command token in the list
 * @param wrk_cmd	temporary cmd struct with the in- and outfiles already found
 * @param env	t_env with environment vars (especially the list of here_docs) 
 * @return int	returns 1 on success, 0 on error. Throws its own error msgs.
 */
int	add_infile(t_list **cmd, t_cmd *wrk_cmd, t_env *env)
{
	t_list	*wrk_li;
	t_cmd	*cur;

	if ((*cmd)->next == NULL || \
						((t_cmd *)(*cmd)->next->content)->type != LITERAL)
		return (parse_error((*cmd)->content, ERR_EXP_EXPRESSION), 0);
	wrk_li = *cmd;
	*cmd = (*cmd)->next;
	cur = (t_cmd *)(*cmd)->content;
	cur->type = ((t_cmd *)wrk_li->content)->type;
	ft_lstdel_item(&env->cmd_list, wrk_li, free_cmd_struct);
	wrk_li = ft_lstnew(cur);
	if (wrk_li == NULL)
		return (mem_error(), 0);
	ft_lstadd_back(&wrk_cmd->infiles, wrk_li);
	if (cur->type == SMALLER_2)
	{
		wrk_li = ft_lstnew(cur);
		if (wrk_li == NULL)
			return (mem_error(), 0);
		ft_lstadd_back(&env->hdocs, wrk_li);
	}
	wrk_li = *cmd;
	*cmd = (*cmd)->next;
	return (ft_lstdel_item(&env->cmd_list, wrk_li, NULL), 1);
}

/**
 * @brief	Adds outfile to wrk_cmd struct.
 * 
 * @param cmd	t_list item with the current command token in the list
 * @param wrk_cmd	temporary cmd struct with the in- and outfiles already found
 * @param env	t_env with environment vars (especially the list of here_docs) 
 * @return int	returns 1 on success, 0 on error. Throws its own error msgs.
 */
int	add_outfile(t_list **cmd, t_list **top, t_cmd *wrk_cmd)
{
	t_list	*wrk_li;
	t_cmd	*cur;

	if ((*cmd)->next == NULL || \
					((t_cmd *)(*cmd)->next->content)->type != LITERAL)
		return (parse_error((*cmd)->content, ERR_EXP_EXPRESSION), 0);
	wrk_li = *cmd;
	*cmd = (*cmd)->next;
	cur = (t_cmd *)(*cmd)->content;
	cur->type = ((t_cmd *)wrk_li->content)->type;
	ft_lstdel_item(top, wrk_li, free_cmd_struct);
	wrk_li = ft_lstnew((*cmd)->content);
	if (wrk_li == NULL)
		return (mem_error(), 0);
	ft_lstadd_back(&wrk_cmd->outfiles, wrk_li);
	wrk_li = *cmd;
	*cmd = (*cmd)->next;
	ft_lstdel_item(top, wrk_li, NULL);
	return (1);
}
