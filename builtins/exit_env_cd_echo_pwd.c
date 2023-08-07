/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_env_cd_echo_pwd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:40:14 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 17:34:45 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include <stdio.h>

static int	check_exit_arg(char *arg)
{
	int	sign;
	long	n;

	sign = 0;
	if (arg[0] == '+')
		sign = 0;
	else if (arg[0] == '-')
		sign = -1;
	else
	{
		if (!ft_check_string(arg, ft_isdigit))
		{
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			return (-1);
		}
	}
	n = ft_atoli(arg);
	if ((size_t)(n - sign) > LONG_MAX)
	{
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		n = -1;
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
	int				sign;

	exit_status = 0;
	sign = 0;
	if (cmd != NULL && cmd->args != NULL)
	{
		arg = (t_cmd *)cmd->args->content;
		if (ft_lstsize(cmd->args) > 1)
			return (print_error("exit: too many arguments", NULL), 1 << 8);
		else
		{
			exit_status = check_exit_arg(arg->literal);
			// printf("status: %lli, %zu\n", exit_status, (size_t)exit_status);
			
			// exit_status = 1;
		}
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
			(cur->export && display == ONLY_ENV) || \
			(!cur->export && display == ONLY_LOCAL))
			ft_printf("%s=%s\n", cur->key, cur->value);
		wrk = wrk->next;
	}
	return (0);
}

/**
 * @brief	Change the current working directory and update the 
 * 			PATH and OLDPWD vars.
 * 
 * @param cmd The structure with the parsed command and its arguments.
 * @param env The structure with the current environment variables.
 * @return int Returns 0 if the command was executed successfully, and 1 
 * 			in case of an error.
 */
int	cd(t_cmd *cmd, t_env *env)
{
	char		*new_pwd;
	char		new_cwd[PATH_MAX];
	t_env_var	*old_pwd;
	t_env_var	*pwd;

	pwd = (t_env_var *)get_env_var(env->env_vars, "PWD")->content;
	old_pwd = (t_env_var *)get_env_var(env->env_vars, "OLDPWD")->content;
	if (cmd->args == NULL)
		new_pwd = ft_strdup(get_env_value(env->env_vars, "HOME"));
	else
		new_pwd = ft_strdup(cmd->arg_arr[1]);
	if (new_pwd == NULL)
		return (mem_error(), 1 << 8);
	if (chdir(new_pwd) < 0)
		return (ft_dprintf(2, "cd: "), perror(new_pwd), free(new_pwd), 1 << 8);
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	free(new_pwd);
	getcwd(new_cwd, PATH_MAX);
	pwd->value = ft_strdup(new_cwd);
	if (pwd->value == NULL)
		return (mem_error(), 1 << 8);
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
