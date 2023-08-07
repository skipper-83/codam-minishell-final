/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:11:31 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/05 13:27:06 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

/**
 * @brief	Handle the character after the backslash according to
 * 			the quote type passsed.
 * 
 * @param head 
 * @param wrk 
 * @param qtype 
 * @return int 
 */
int	handle_backslash(t_list **head, t_list **wrk, t_token_type qtype)
{
	t_list	*buf;
	t_cmd	*next;

	if ((*wrk)->next == NULL)
		return (parse_error((*wrk)->content, ERR_EXP_EXPRESSION), 0);
	next = ((t_cmd *)(*wrk)->next->content);
	if (qtype == DQ || qtype == SQ)
	{
		if ((next->type != DQ && next->type != DLR_SIGN \
						&& next->type != BACKSLASH) || qtype == SQ)
		{
			((t_cmd *)(*wrk)->content)->type = LITERAL;
			next->type = LITERAL;
			*wrk = (*wrk)->next;
			return (1);
		}
	}
	next->type = LITERAL;
	buf = (*wrk)->next;
	ft_lstdel_item(head, *wrk, free_cmd_struct);
	*wrk = buf;
	return (1);
}
