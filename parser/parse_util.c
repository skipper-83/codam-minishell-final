/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:44:39 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/05 10:38:10 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minishell.h"
#include "tokenizer.h"

/**
 * @brief	Parse function for use in main program. Wants the command list
 * 			(which is in the env struct, but it wants it apart as to not
 * 			destroy the pointer when walking through the list).
 * 			Calls parse_simple_cmd for every sub-part of the command line 
 * 			entered. Skips operators and calls the parse_simple_cmd function
 * 			again.
 * 
 * @param cmd	t_list with the address of the command list
 * @param env	t_env with environment vars, especially the here_doc list
 * @return int 	returns 0 on error, 1 on succes.
 */
int	parse_command_list(t_list *cmd, t_env *env)
{
	while (cmd)
	{
		if (parse_simple_cmd(cmd, env, &cmd) == NULL)
			return (0);
		if (cmd != NULL)
			cmd = cmd->next;
	}
	return (1);
}

/**
 * @brief	Takes the token_lst that is produced by the lexer and 
 * 			makes it into a linked list with command struct.
 * 			Literal is copied from the token list, so that it can
 * 			be freed.
 * 
 * @param tok_list	token list provided by lexer
 * @return t_list*	list with command structs
 */
t_list	*make_command_list(t_token_lst *tok_list)
{
	t_token		*wrk;
	t_list		*res;
	t_list		*lst;
	t_cmd		*cmd;
	char		*literal;

	wrk = tok_list->head;
	res = NULL;
	while (wrk)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		lst = ft_lstnew(cmd);
		literal = ft_strdup(wrk->value);
		if (cmd == NULL || lst == NULL || literal == NULL)
		{
			ft_lstclear(&res, free_cmd_struct);
			free_token_struct(tok_list);
			return (mem_error(), NULL);
		}
		cmd->literal = literal;
		cmd->type = wrk->type;
		ft_lstadd_back(&res, lst);
		wrk = wrk->next;
	}
	return (free_token_struct(tok_list), res);
}

/**
 * @brief	Subfunction to clear the infile and outfile lists
 * 			from the temporay command struct used by the parser
 * 
 * @param wrk_cmd	struct to be cleared
 */
void	clear_inf_outf(t_cmd *wrk_cmd)
{
	ft_lstclear(&wrk_cmd->infiles, free_cmd_struct);
	ft_lstclear(&wrk_cmd->outfiles, free_cmd_struct);
	ft_lstclear(&wrk_cmd->vars, free_env_struct);
}

/**
 * @brief	Get previous item of list. Returns NULL if current item is head, or no
 * 			prev is found.
 * 
 * @param head 
 * @param cur 
 * @return t_list* 
 */
t_list	*get_prev(t_list *head, t_list *cur)
{
	t_list	*wrk;

	wrk = head;
	while (wrk)
	{
		if (wrk->next == cur)
			return (wrk);
		wrk = wrk->next;
	}
	return (NULL);
}
