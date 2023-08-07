/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:06:29 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 15:11:21 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minishell.h"

/**
 * @brief	Helper function for combine_commands(), get the total
 * 			length of the literals to be combined for memory allocation
 * 
 * @param start 
 * @param end 
 * @return int 
 */
static int	get_combined_length(t_list *start, t_list *end)
{
	t_list	*wrk;
	int		res;

	wrk = start;
	res = 0;
	while (wrk != end->next)
	{
		res += ft_strlen(((t_cmd *)wrk->content)->literal);
		wrk = wrk->next;
	}
	return (res);
}

/**
 * @brief	Helper for combine_commands(), browse through the nodes and 
 * 			append the literals in pre-allocated string
 * 
 * @param cmb_cmd 
 * @param wrk 
 * @param last 
 * @param start 
 */
static void	combine(char *cmb_cmd, t_list **wrk, t_list *last, t_list *start)
{
	t_list	*buf;
	int		len;
	int		i;

	i = 0;
	while (*wrk != last)
	{
		len = ft_strlen(((t_cmd *)(*wrk)->content)->literal);
		ft_strlcpy(&cmb_cmd[i], ((t_cmd *)(*wrk)->content)->literal, len + 1);
		i += len;
		buf = (*wrk)->next;
		if (*wrk != start)
		{
			ft_lstdelone(*wrk, free_cmd_struct);
			*wrk = NULL;
		}
		*wrk = buf;
	}
}

/**
 * @brief	Combine the commands from [start] through to [end],
 * 			set pointer to the element after [end]
 * 
 * @param start 
 * @param end 
 * @return int 
 */
int	combine_commands(t_list *start, t_list *end)
{
	t_list	*wrk;
	t_list	*last;
	int		len;
	char	*cmb_literal;

	len = get_combined_length(start, end);
	cmb_literal = malloc(sizeof(char) * len + 1);
	wrk = start;
	last = end->next;
	if (cmb_literal == NULL)
		return (mem_error(), 0);
	combine(cmb_literal, &wrk, last, start);
	free(((t_cmd *)start->content)->literal);
	((t_cmd *)start->content)->type = LITERAL;
	((t_cmd *)start->content)->literal = cmb_literal;
	start->next = last;
	return (1);
}
