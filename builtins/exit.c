/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:51:18 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/08 13:25:49 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

/**
 * @brief Check arguments for exit. Return -1 (255) if non-numeric numbers 
 * 		are used or when the number passed is larger/smaller than long int.
 * 
 * @param arg 
 * @return int 
 */
static int	check_exit_arg(char *arg)
{
	int		sign;
	size_t	n;

	sign = 0;
	if ((!ft_isdigit(arg[0] && (arg[0] == '+' || arg[0] == '-'))))
		if (!ft_check_string(&arg[1], ft_isdigit))
			return (print_error("exit: numeric argument required", NULL), -1);
	n = ft_atosizet(arg, &sign);
	if ((n + sign) > (size_t)LONG_MAX)
	{
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		return (-1);
	}
	if (sign)
		return ((int)n * sign);
	return ((int)n);
}

/**
 * @brief This function implements the shell "exit" command.
 *
 * "exit" command is used to end the shell session. It can optionally accept an 
 * integer argument that sets the exit status.
 *
 * @param env The structure with the current environment variables.
 * @param cmd The structure with the parsed command and its arguments.
 * @return No return value since the function ends the shell session using the 
 * exit system call.
 */
int	exit_ceash(t_env *env, t_cmd *cmd)
{
	long long		exit_status;
	t_cmd			*arg;

	exit_status = 0;
	if (cmd != NULL && cmd->args != NULL)
	{
		arg = (t_cmd *)cmd->args->content;
		if (ft_lstsize(cmd->args) > 1)
			return (print_error("exit: too many arguments", NULL), 1 << 8);
		else
			exit_status = check_exit_arg(arg->literal);
	}
	ft_lstclear(&env->open_fds, NULL);
	ft_lstclear(&env->hdocs, NULL);
	ft_lstclear(&env->cmd_list, free_cmd_struct);
	ft_lstclear(&env->env_vars, free_env_struct);
	free(env);
	clear_history();
	ft_putendl_fd("exit", 1);
	exit ((int)exit_status);
}
