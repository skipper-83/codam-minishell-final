/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:31:21 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/01 12:41:18 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

/**
 * @brief	Loops through all the commands between brackets and parses them with
 * 			parse_simple_cmd.
 * 
 * @param cmd	t_list item with the current command token in the list
 * @param env 	t_env with environment vars (especially the list of here_docs)
 * @param the_cmd	t_cmd the command to which pipes and redirects are attached
 */
static void	bracket_loop(t_list **cmd, t_env *env, t_cmd **the_cmd)
{
	t_cmd			*buf;

	while (*cmd != NULL && ((t_cmd *)(*cmd)->content)->type != BRC)
	{
		buf = parse_simple_cmd(*cmd, env, cmd);
		if (buf == NULL)
			return ;
		if (*the_cmd == NULL)
		{
			*the_cmd = buf;
			if (*cmd != NULL)
			{
				buf = (t_cmd *)(*cmd)->content;
				if (buf->type >= PIPE_2 && buf->type <= SC)
					*the_cmd = buf;
			}
		}
		if (*cmd != NULL && ((t_cmd *)(*cmd)->content)->type == BRC)
			break ;
		if (*cmd != NULL)
			*cmd = (*cmd)->next;
	}
}

/**
 * @brief	Adds pipe if found after a bracket.
 * 
 * @param c 
 * @param wrk 
 * @param cmd 
 * @return int 
 */
int	add_pipe_after_bracket(t_cmd **c, t_cmd *wrk, t_list **cmd)
{
	if (*c == NULL && wrk->infiles == NULL)
		return (parse_error((*cmd)->content, ERR_TOKEN_UNEXP), 0);
	else if (*c == NULL)
		*c = (t_cmd *)(*cmd)->content;
	return (1);
}

/**
 * @brief	Parses the redirects after the bracket
 * 
 * @param cmd	t_list item with the current command token in the list
 * @param env	t_env with environment vars (especially the list of here_docs)
 * @param c  	t_cmd (abbreviated from the_command): the command to which
 * 				pipes and redirects are attached
 * @param wrk 	temporary cmd struct with the in- and outfiles already found
 * @return int	returns int with error status (0 is error, 1 is no error)
 */
static int	get_bracket_redir(t_list **cmd, t_env *env, t_cmd **c, t_cmd *wrk)
{
	int				retval;
	t_token_type	type;

	while (*cmd)
	{
		retval = -1;
		type = ((t_cmd *)(*cmd)->content)->type;
		if (type == SMALLER || type == SMALLER_2)
			retval = add_infile(cmd, wrk, env);
		else if (type == GREATER || type == GREATER_2)
			retval = add_outfile(cmd, &env->cmd_list, wrk);
		else if (type == PIPE)
			return (add_pipe_after_bracket(c, wrk, cmd));
		else if (type == LITERAL)
			return (parse_error((*cmd)->content, ERR_TOKEN_UNEXP), 0);
		if (!retval)
			return (clear_inf_outf(wrk), 0);
		else if (retval > 0)
			retval = -1;
		else
			break ;
	}
	return (1);
}

/**
 * @brief	Gets called when parser encounters opening bracket. Adds all infiles 
 * 			and outfiles already define before the brackets to the first command
 * 			or (if available) the first operator between the brackts
 * 
 * @param cmd t_list item with the current command token in the list
 * @param env t_env with environment vars (especially the list of here_docs)
 * @param wrk_cmd temporary cmd struct with the in- and outfiles already found
 * @return t_cmd* returns the command to which the in- and outfiles are attached
 */
t_cmd	*parse_bracketed_cmd(t_list **cmd, t_env *env, t_cmd *wrk_cmd)
{
	t_cmd			*the_command;

	*cmd = (*cmd)->next;
	the_command = NULL;
	bracket_loop(cmd, env, &the_command);
	if (the_command == NULL)
		return (NULL);
	if (*cmd != NULL)
		*cmd = (*cmd)->next;
	if (!get_bracket_redir(cmd, env, &the_command, wrk_cmd))
		return (NULL);
	return (ret_parsed_cmd(the_command, NULL, *cmd, wrk_cmd));
}
