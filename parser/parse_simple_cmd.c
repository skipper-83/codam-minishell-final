/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:10:22 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/05 10:44:01 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief	Checks if a command is preceded by a path (ie ./a.out). If so,
 * 			adds the past to the cmd->path variable and cuts the path of 
 * 			the command. So ./a.out will become cmd->literal: a.out, cmd->path: ./
 * 
 * @param cmd 
 * @return int 
 */
int	get_path(t_cmd *cmd)
{
	char	*last_slash;
	char	*command;

	last_slash = ft_strrchr(cmd->literal, '/');
	if (last_slash == NULL)
		return (2);
	command = ft_substr(last_slash, 1, ft_strlen(last_slash) - 1);
	last_slash[1] = 0;
	cmd->path = ft_strdup(cmd->literal);
	if (command == NULL || cmd->path == NULL)
		return (mem_error(), 0);
	free(cmd->literal);
	cmd->literal = command;
	return (1);
}

/**
 * @brief	Adds command as first item to the arg list and
 * 			makes the char ** for use in execve()
 * 
 * @param cmd 
 * @return int 
 */
int	make_arg_list(t_cmd *cmd)
{
	t_list	*new;
	char	**args;

	if (cmd->arg_arr != NULL)
		return (1);
	new = ft_lstnew(cmd);
	if (new == NULL)
		return (mem_error(), 0);
	ft_lstadd_front(&cmd->args, new);
	args = list_to_arr(cmd->args, get_lit);
	ft_lstdel_item(&cmd->args, new, NULL);
	if (args == NULL)
		return (free (new), mem_error(), 0);
	args[0] = ft_strdup(cmd->literal);
	if (args[0] == NULL)
		return (free_2d_arr(args), mem_error(), 0);
	cmd->arg_arr = args;
	return (1);
}

/**
 * @brief	Gets called by parse_simple_cmd for every next token. Determines the
 * 			type and calls the appropriate funcion.
 * 
 * @param cmd	t_list item with the current command token in the list
 * @param wrk_c temporary cmd struct with the in- and outfiles already found
 * @param env	t_env with environment vars (especially the list of here_docs)
 * @param the_cmd t_cmd to which pipes and redirs are attached
 * @return int	returns 0 on error, 1 when the command is finished, -1 for need
 * 				next token
 */
int	parse_loop(t_list **cmd, t_cmd *wrk_c, t_env *env, t_cmd **the_cmd)
{
	int				retval;
	t_token_type	type;

	retval = -1;
	type = ((t_cmd *)(*cmd)->content)->type;
	if (type == SMALLER || type == SMALLER_2)
		retval = add_infile(cmd, wrk_c, env);
	else if (type == LITERAL || type == BRO)
		retval = add_cmd_args(the_cmd, cmd, env, wrk_c);
	else if (type == GREATER || type == GREATER_2)
		retval = add_outfile(cmd, &env->cmd_list, wrk_c);
	else if (type == PIPE)
	{
		if (*the_cmd == NULL && wrk_c->infiles == NULL)
			return (parse_error((*cmd)->content, ERR_TOKEN_UNEXP), 0);
		else if (*the_cmd == NULL)
			*the_cmd = (t_cmd *)(*cmd)->content;
		return (1);
	}
	if (!retval)
		return (0);
	else if (retval > 0)
		return (-1);
	else
		return (1);
}

/**
 * @brief	Subfunction for parse_simple_cmd. Checks if a command has been found, 
 * 			if not, clears the wrk_cmd struct that stores the infiles and outfiles.
 * 			Updates the *wrk linked list pointer when parse_simple_cmd was called 
 * 			recursively, so caller function can proceed in list where this instance
 * 			has left off.
 * 			Adds in- and outfiles to the command and resets the wrk_cmd struct items.
 * 
 * @param the_cmd	t_cmd to which pipes and redirs are attached
 * @param wrk	t_list item used in recursion, wants the address of the linked
 * 				list pointer that is used to move through the list.
 * @param cmd	t_list item with the current command token in the list
 * @param wrk_c 	temporary cmd struct with the in- and outfiles already found
 * @return t_cmd* 	returns the command to which the pipes and redirs are attached
 */
t_cmd	*ret_parsed_cmd(t_cmd *the_cmd, t_list **wrk, t_list *cmd, t_cmd *wrk_c)
{
	if (the_cmd == NULL)
		return (clear_inf_outf(wrk_c), \
		parse_error(NULL, ERR_EXP_EXPRESSION), NULL);
	if (wrk != NULL)
		*wrk = cmd;
	if (the_cmd->infiles != NULL)
		ft_lstadd_back(&wrk_c->infiles, the_cmd->infiles);
	if (the_cmd->outfiles != NULL)
		ft_lstadd_back(&wrk_c->outfiles, the_cmd->outfiles);
	the_cmd->infiles = wrk_c->infiles;
	the_cmd->outfiles = wrk_c->outfiles;
	the_cmd->vars = wrk_c->vars;
	wrk_c->infiles = NULL;
	wrk_c->outfiles = NULL;
	wrk_c->vars = NULL;
	if (!make_arg_list(the_cmd) || !get_path(the_cmd))
		return (NULL);
	return (the_cmd);
}

/**
 * @brief	Parser workhorse. Parses a succesion of tokens, classifies
 * 			them as pipe, redirect, command or argument and assembles them
 * 			in a command struct.
 * 
 * @param cmd 	t_list item with the current command token in the list
 * @param env	t_env with environment vars (especially the list of here_docs)
 * @param wrk 	t_list item used in recursion, wants the address of the linked
 * 				list pointer that is used to move through the list.
 * @return t_cmd*	returns the command to which the pipes and redirs are attached
 */
t_cmd	*parse_simple_cmd(t_list *cmd, t_env *env, t_list **wrk)
{
	t_cmd			*the_command;
	t_cmd			wrk_cmd;
	t_list			*prev;
	int				retval;

	the_command = NULL;
	wrk_cmd.infiles = NULL;
	wrk_cmd.outfiles = NULL;
	wrk_cmd.vars = NULL;
	retval = -1;
	prev = get_prev(env->cmd_list, cmd);
	while (cmd)
	{
		retval = parse_loop(&cmd, &wrk_cmd, env, &the_command);
		if (!retval)
			return (clear_inf_outf(&wrk_cmd), NULL);
		if (retval > 0)
			break ;
	}
	if (the_command == NULL && wrk_cmd.vars != NULL)
	{
		if (!make_var_set_cmd(&the_command, env, prev))
			return (0);
	}
	return (ret_parsed_cmd(the_command, wrk, cmd, &wrk_cmd));
}
