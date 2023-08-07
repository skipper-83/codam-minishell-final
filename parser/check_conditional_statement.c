/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_conditional_statement.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:28:42 by albertvanan       #+#    #+#             */
/*   Updated: 2023/05/24 15:37:48 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

#define NEED_OPERATOR 1
#define NEED_LITERAL 2
#define START_CMD 0
#define SUBGROUP_SUCCESS -1
#define PARSE_ER -2

/**
 * @brief	Subfunction for check_conditions()
 * 			calls check_conditions when a ( is encountered
 * 			returns value based on command type found,
 * 			negative values result in returning calling function
 * 
 * @param cur 
 * @param cmd 
 * @param level 
 * @param status 
 * @return int 
 */
static int	cc_loop_body(t_cmd *cur, t_list **cmd, int status)
{
	if (cur->type == BRO)
	{
		if (!check_conditions((*cmd)->next, cmd, status))
			return (PARSE_ER);
		return (NEED_OPERATOR);
	}
	if (cur->type >= PIPE && cur->type <= SC)
	{
		if (status != NEED_OPERATOR && cur->type >= PIPE_2 && cur->type <= SC)
			return (parse_error((*cmd)->content, ERR_EXP_EXPRESSION), PARSE_ER);
		else
			return (NEED_LITERAL);
	}
	if (cur->type == LITERAL)
		if (status == START_CMD || status == NEED_LITERAL)
			return (NEED_OPERATOR);
	if (cur->type == BRC && cmd != NULL && status > 0)
		return (SUBGROUP_SUCCESS);
	if (status == NEED_OPERATOR)
		return (parse_error((*cmd)->content, ERR_EXP_OPERATOR), PARSE_ER);
	else
		return (parse_error((*cmd)->content, ERR_EXP_EXPRESSION), PARSE_ER);
}

/**
 * @brief	Checks if an input list of commands has correct its conditional
 * 			statements and bracket prioritization correctly formatted.
 * 
 * @param command	the list with command tokens
 * @param work	the current position in the list, used in recursion, pass NULL
 * 				on first call
 * @param level	the depth level (ie the amount of brackets, like so: 
 * 				level 0 (level 1 ( level 2))) -- used in recursion, pass 0 on
 * 				first call
 * @return int	returns 1 when no errors found, 0 on error (throws its own msgs)
 */
int	check_conditions(t_list *command, t_list **work, int status)
{
	t_cmd	*cur;

	while (command)
	{
		if (work != NULL)
			*work = command;
		cur = (t_cmd *)command->content;
		status = cc_loop_body(cur, &command, status);
		if (status < 0)
			return (status + 2);
		command = command->next;
	}
	if (status > 1 && cur->type != SC)
		return (parse_error(command, ERR_EXP_EXPRESSION), 0);
	if (status == START_CMD)
		return (parse_error(command, ERR_EXP_EXPRESSION), 0);
	if (command == NULL && work != NULL)
		return (parse_error(command, ERR_CLOSE_PAR), 0);
	return (1);
}
