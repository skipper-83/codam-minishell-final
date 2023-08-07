/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_wildcard.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 00:32:11 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/08/01 17:46:09 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

/**
 * @brief	Makes wildcard t_list. ex*mple would take the form of
 * 			ex -> * -> mple. This list is used for wildcard gobbling
 *			by gobble()
 * 
 * @param start 
 * @param end 
 * @return t_list* 
 */
static t_list	*make_wildcard_list(t_list **start, t_list **end)
{
	t_list	*wildcard;
	t_list	*wrk;
	t_list	*new;
	t_list	*del;
	char	*lit;

	wildcard = NULL;
	wrk = *start;
	while (wrk && (((t_cmd *)wrk->content)->type == LITERAL \
							|| ((t_cmd *)wrk->content)->type == AST))
	{
		lit = ft_strdup(((t_cmd *)wrk->content)->literal);
		new = ft_lstnew(lit);
		if (new == NULL || lit == NULL)
			return (mem_error(), ft_lstclear(&wildcard, free), NULL);
		ft_lstadd_back(&wildcard, new);
		del = wrk;
		wrk = wrk->next;
		if (del != *start)
			ft_lstdel_item(start, del, free_cmd_struct);
	}
	*end = wrk;
	return (wildcard);
}

/**
 * @brief 	Norminette-induced looper. Makes wildcard list when asterisk is 
 * 			encountered, gobbles up all matching filenames, and adds them
 * 			to the list of command nodes. 
 * 
 * @param wrk 
 * @param start 
 * @param prev 
 * @return int 
 */
static int	parse_wildcard_loop(t_list	**wrk, t_list ***start, t_list **prev)
{
	t_list	*wildcard;

	if (((t_cmd *)(*wrk)->content)->type == AST)
	{
		wildcard = make_wildcard_list(*start, wrk);
		if (wildcard == NULL)
			return (0);
		if (!gobble(&wildcard, *start, *wrk, (t_cmd *)(*prev)->content))
			return (ft_lstclear(&wildcard, free), 0);
		ft_lstclear(&wildcard, free);
	}
	else if (((t_cmd *)(*wrk)->content)->type != LITERAL)
	{
		*start = &(*wrk)->next;
		if (((t_cmd *)(*wrk)->content)->type != SP)
			*prev = *wrk;
		*wrk = (*wrk)->next;
	}
	else
		*wrk = (*wrk)->next;
	return (1);
}

/**
 * @brief	Calls parse_wildcard_loop() to run over string of commands
 * 			until operator is encountered. Makes a wildcard list when 
 * 			an asterisk is encountered and gobbles up matching filenames
 * 			from the cwd or path specified by the first command encountered.
 * 
 * @param command 
 * @return int 
 */
int	parse_wildcard(t_list **command)
{
	t_list	*wrk;
	t_list	*prev;
	t_list	**start;

	wrk = *command;
	start = command;
	prev = wrk;
	while (wrk)
		if (!parse_wildcard_loop(&wrk, &start, &prev))
			return (0);
	return (1);
}
