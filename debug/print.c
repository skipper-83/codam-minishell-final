/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:18:08 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/05 16:54:47 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*last_file(t_list *filestream)
{
	return (((t_cmd *)ft_lstlast(filestream)->content)->literal);
}

char	*get_cmd_literal(void *param, int line)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)param;
	if (line == 0)
		return (ft_msprintf("%s", cmd->literal));
	if (line == 1)
		return (ft_msprintf("type: %i", cmd->type));
	if (line == 2)
		return (ft_msprintf("qtype: %i", cmd->quote_type));
	if (line == 3)
	{
		if (cmd->infiles == NULL)
			return (ft_msprintf("inf: %s", "none"));
		return (ft_msprintf("inf: %s", last_file(cmd->infiles)));
	}
	if (line == 4)
	{
		if (cmd->outfiles == NULL)
			return (ft_msprintf("outf: %s", "none"));
		return (ft_msprintf("outf: %s", last_file(cmd->outfiles)));
	}
	if (line == 5)
		return (ft_msprintf("argc: %i", ft_lstsize(cmd->args)));
	return (NULL);
}

void	print_cmd_item(void *param)
{
	t_cmd	*command;

	command = (t_cmd *)param;
	ft_printf("%s, type %i, argc %i ", command->literal, \
						command->type, ft_lstsize(command->args));
	ft_printf("infile_c: %i ", ft_lstsize(command->infiles));
	ft_printf("outifle_c: %i ", ft_lstsize(command->outfiles));
	ft_printf("path: %s", command->path);
	if (command->arg_arr != NULL)
		ft_printf(" arg_arr[0]: %s \n", command->arg_arr[0]);
	else
		ft_printf("\n");
	ft_lstiter(command->vars, print_env_item);
}

void	print_env_item(void *param)
{
	t_env_var	*var;

	var = (t_env_var *)param;
	ft_printf("%s -> %s\n", var->key, var->value);
}

void	print_char_arr(char **arr)
{
	int	i;

	ft_putendl_fd("printing char arr\n", 2);
	i = 0;
	while (arr[i] != NULL)
	{
		ft_putendl_fd(arr[i], 2);
		i++;
	}
}
