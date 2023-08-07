/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:34:44 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/05 10:39:41 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

/**
 * @brief	Subfunction for add_cmd_args, adds the literals to a linked list
 * 			of arguments.
 * 
 * @param cmd t_list item with the current command token in the list
 * @param the_command t_cmd to which pipes and redirs are attached
 * @param env t_env with environment vars (especially the list of here_docs)
 * @return int returns 0 on error (parse or mem, msg is thrown), 1 on success
 */
static int	add_args(t_list **cmd, t_cmd **the_command, t_env *env)
{
	t_list	*wrk_li;

	wrk_li = ft_lstnew((t_cmd *)(*cmd)->content);
	if (wrk_li == NULL)
		return (mem_error(), 0);
	ft_lstadd_back(&(*the_command)->args, wrk_li);
	wrk_li = *cmd;
	*cmd = (*cmd)->next;
	ft_lstdel_item(&env->cmd_list, wrk_li, NULL);
	return (1);
}

/**
 * @brief	Essentialy parses literals in succesion. If it is the first, the 
 * 			literal will be parsed as the_command (to which pipes and 
 * 			redirects are attached).Succesive literals will be parsed as 
 * 			arguments to said command and be put in a linked list 
 * 			that is available in the command struct.
 * 
 * @param the_command t_cmd to which pipes and redirs are attached
 * @param cmd t_list item with the current command token in the list
 * @param env t_env with environment vars (especially the list of here_docs)
 * @param wrk_cmd temporary cmd struct with the in- and outfiles already found
 * @return int return 0 on error, 1 on success.
 */
int	add_cmd_args(t_cmd **the_command, t_list **cmd, t_env *env, t_cmd *wrk_cmd)
{
	if (((t_cmd *)(*cmd)->content)->type == BRO)
	{
		*the_command = parse_bracketed_cmd(cmd, env, wrk_cmd);
		if (*the_command == NULL)
			return (0);
		return (1);
	}
	else if (*the_command == NULL)
	{
		if (is_var(((t_cmd *)(*cmd)->content)->literal, 1))
		{
			if (!add_var(&wrk_cmd->vars, cmd, &env->cmd_list))
				return (0);
		}
		else
		{
			*the_command = (t_cmd *)(*cmd)->content;
			*cmd = (*cmd)->next;
		}
		return (1);
	}
	else
		return (add_args(cmd, the_command, env));
}
