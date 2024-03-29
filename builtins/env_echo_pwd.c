/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_cd_echo_pwd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-and <avan-and@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 13:40:14 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/08/08 13:21:23 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

/**
 * @brief	Display the environment variables.
 * 
 * Default: only those that are  exported. Flags: "-a" for both exported and 
 * local, "-l" for only local vars.
 * 
 * @param env The structure with the current environment variables.
 * @param cmd The structure with the parsed command and its arguments.
 * @return int Returns 0 if the command was executed successfully.
 */
int	env_builtin(t_env *env, t_cmd *cmd)
{
	t_list		*wrk;
	t_env_var	*cur;
	int			display;

	wrk = env->env_vars;
	display = ONLY_ENV;
	if (cmd->args != NULL)
	{
		if (((t_cmd *)cmd->args->content)->literal[1] == 'a')
			display = LOCAL_AND_ENV;
		if (((t_cmd *)cmd->args->content)->literal[1] == 'l')
			display = ONLY_LOCAL;
	}
	while (wrk)
	{
		cur = (t_env_var *)wrk->content;
		if (display == LOCAL_AND_ENV || \
			((cur->export && display == ONLY_ENV) && cur->value[0]) || \
			(!cur->export && display == ONLY_LOCAL))
			ft_printf("%s=%s\n", cur->key, cur->value);
		wrk = wrk->next;
	}
	return (0);
}

/**
 * @brief	Echo: print the arguments to stdout. Flag -n will omit
 * 			the newline after the last argument.
 * 
 * @param cmd The structure with the parsed command and its arguments.
 * @return int Returns 0 if the command was executed successfully.
 */
int	echo(t_cmd *cmd)
{
	int		i;
	char	newline;

	newline = 1;
	i = 1;
	if (cmd->arg_arr[1] != NULL && !ft_strcmp("-n", cmd->arg_arr[1]))
	{
		i++;
		newline = 0;
	}
	while (cmd->arg_arr[i] != NULL)
	{
		if (newline + i != 2)
			ft_printf(" ");
		ft_printf("%s", cmd->arg_arr[i]);
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}

/**
 * @brief This function handles the "pwd" command in the shell.
 *
 * The "pwd" command is used to print the path of the current working directory.
 *
 * @param cmd The structure with the parsed command and its arguments.
 * @param env The structure with the current environment variables.
 * @return int Returns 0 if the command was executed successfully. Returns 1 and 
 * 			prints an error message if the "pwd" command is called with any arguments, 
 * 			as it does not accept any.
 */

int	pwd(t_cmd *cmd, t_env *env)
{
	(void)cmd;
	ft_printf("%s\n", get_env_value(env->env_vars, "PWD"));
	return (0);
}
