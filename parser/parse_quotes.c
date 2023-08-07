/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:52:26 by albertvanan       #+#    #+#             */
/*   Updated: 2023/06/27 22:54:44 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

/**
 * @brief	If multiple nodes of the 'literal' type are found in succesion, 
 * 			combine them into a single node.
 * 
 * @param start 
 * @return int 
 */
static int	combine_literals(t_list **command)
{
	t_list	*wrk;
	t_list	*end;

	wrk = *command;
	while (wrk)
	{
		if (((t_cmd *)wrk->content)->type == LITERAL)
		{
			end = wrk;
			while (1)
			{
				if (end == NULL || end->next == NULL)
					break ;
				if (((t_cmd *)end->next->content)->type != LITERAL)
					break ;
				end = end->next;
			}
			if (!combine_commands(wrk, end))
				return (0);
		}
		wrk = wrk->next;
	}
	return (1);
}

/**
 * @brief	Cleans out the command list: remove the spaces and
 * 			combine nodes of literal type
 * 
 * @param command 
 * @return int 
 */
static int	remove_spaces(t_list **command)
{
	t_cmd	*cur;
	t_list	*wrk;
	t_list	*buf;

	wrk = *command;
	while (wrk)
	{
		cur = (t_cmd *)wrk->content;
		buf = wrk;
		wrk = wrk->next;
		if (cur->type == SP)
			ft_lstdel_item(command, buf, free_cmd_struct);
	}
	return (1);
}

/**
 * @brief	Parses the quotes in a string literal. Determines which quote
 * 			type (' or ") takes precedence and updates the quote_type attribute
 * 			of the command struct accordingly.
 * 
 * @param command	t_list with the command stream, passed as pointer as the list 
 * 					items	containting the quotes are deleted and one of them might 
 * 					be the list head.
 * @return int	1 if no parse/mem errors encoutered, 0 on error (error msg is 
 * 				thrown)
 */
int	parse_quotes(t_env *env)
{
	t_token_type	type;
	t_list			*wrk;
	int				ret;

	wrk = env->cmd_list;
	while (wrk)
	{
		ret = 1;
		type = ((t_cmd *)wrk->content)->type;
		if (type == BACKSLASH)
			ret = handle_backslash(&env->cmd_list, &wrk, LITERAL);
		else if (type == DLR_SIGN)
			ret = expand(&wrk, env);
		else if (type == SQ || type == DQ)
			ret = comb_quoted_cmds(env, &wrk, type);
		else
			wrk = wrk->next;
		if (!ret)
			return (0);
	}
	if (!combine_literals(&env->cmd_list) || !parse_wildcard(&env->cmd_list))
		return (0);
	return (remove_spaces(&env->cmd_list));
}
