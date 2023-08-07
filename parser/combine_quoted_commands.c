/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_quoted_commands.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:10:58 by avan-and          #+#    #+#             */
/*   Updated: 2023/08/07 15:14:24 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minishell.h"

/**
 * @brief Helper for comb_quotes_commands, writs empty string to original command
 * 		when "" is passed, and deletes the quotes.
 * 
 * @param start 
 * @param work 
 * @return int 
 */
int	finish_empty_quotes(t_list **start, t_list *work)
{
	(*start)->next = work->next;
	ft_lstdelone(work, free_cmd_struct);
	free (((t_cmd *)(*start)->content)->literal);
	((t_cmd *)(*start)->content)->type = LITERAL;
	((t_cmd *)(*start)->content)->literal = ft_strdup("");
	if (((t_cmd *)(*start)->content)->literal == NULL)
		return (mem_error(), 0);
	return (1);
}

/**
 * @brief	Helper for comb_quoted_cmds(), return error when no finishing
 * 			quote is found (work->next is NULL), combine the commands
 * 			and return 0 on mem error, free the original literal and
 * 			put the combined literal in the place of the opening quote
 * 			change the type  to literal, remove the nodes with the quote
 * 			at the end of the quoted commands
 * 
 * @param start 
 * @param work 
 * @param qtype 
 * @return int 
 */
static int	finish_quoted_cmd(t_list **start, t_list *work, t_token_type qtype)
{
	t_list	*buf;
	t_cmd	*combined;

	if (work == NULL)
		return (*start = work, parse_error(NULL, ERR_QUOTE_UNBALANCE), 0);
	if (((t_cmd *)(*start)->next->content)->type == qtype)
		return (finish_empty_quotes(start, work));
	buf = work;
	work = ft_lst_get_prev(*start, work);
	if (!combine_commands((*start)->next, work))
		return (0);
	combined = ((t_cmd *)(*start)->content);
	free(combined->literal);
	combined->literal = ((t_cmd *)(*start)->next->content)->literal;
	combined->type = LITERAL;
	combined->quote_type = qtype;
	((t_cmd *)(*start)->next->content)->literal = NULL;
	ft_lstdelone((*start)->next, free_cmd_struct);
	(*start)->next = buf->next;
	*start = (*start)->next;
	ft_lstdelone(buf, free_cmd_struct);
	return (1);
}

/**
 * @brief	Called when a quote is found. Combine all commands between quotes,
 * 			parse backslashes end expansions according to quote type, return
 * 			error on malloc or parse fail.
 * 
 * @param head 
 * @param start 
 * @param qtype 
 * @return int 
 */
int	comb_quoted_cmds(t_env *env, t_list **start, t_token_type qtype)
{
	t_list	*work;

	work = (*start)->next;
	while (work != NULL)
	{
		if (((t_cmd *)work->content)->type == BACKSLASH)
			handle_backslash(&env->cmd_list, &work, qtype);
		else if (((t_cmd *)work->content)->type == DLR_SIGN)
		{
			if (qtype == DQ)
			{
				if (!expand(&work, env))
					return (0);
			}
			else
				((t_cmd *)work->content)->type = LITERAL;
		}
		else if (((t_cmd *)work->content)->type == qtype)
		{
			break ;
		}
		else
			work = work->next;
	}
	return (finish_quoted_cmd(start, work, qtype));
}
