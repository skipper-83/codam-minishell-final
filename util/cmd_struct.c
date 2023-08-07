/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:37:40 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/04 23:20:37 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	*make_cmd_struct(void *input)
// {
// 	t_cmd	*command;
// 	t_token	*token;

// 	token = (t_token *)input;
// 	command = ft_calloc(1, sizeof(t_cmd));
// 	if (command == NULL)
// 		return (mem_error(), NULL);
// 	command->literal = ft_strdup(token->value);
// 	if (command->literal == NULL)
// 		return (free(command), ft_putendl_fd(ERR_MEM, 2), NULL);
// 	command->type = token->type;
// 	command->output_pipe[0] = -1;
// 	command->output_pipe[1] = -1;
// 	command->input_pipe[0] = -1;
// 	command->input_pipe[1] = -1;
// 	return (command);
// }

void	free_cmd_struct(void *content)
{
	t_cmd	*command;

	command = (t_cmd *)content;
	free(command->literal);
	free(command->path);
	command->literal = NULL;
	command->path = NULL;
	if (command->arg_arr != NULL)
	{
		free(command->arg_arr[0]);
		command->arg_arr[0] = NULL;
	}
	free(command->arg_arr);
	ft_lstclear(&command->infiles, free_cmd_struct);
	ft_lstclear(&command->outfiles, free_cmd_struct);
	ft_lstclear(&command->args, free_cmd_struct);
	ft_lstclear(&command->vars, free_env_struct);
	free(command);
	command = NULL;
}
