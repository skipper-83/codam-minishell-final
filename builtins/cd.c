/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ewehl <ewehl@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/08 13:08:41 by ewehl         #+#    #+#                 */
/*   Updated: 2023/08/08 13:30:57 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

/**
 * @brief	helper function for cd, updates the old and current pwd values	
 * 
 * @param new_pwd The string containing the new_pwd value.
 * @param old_pwd The structure containing the old_pwd.
 * @param pwd The structure containing the current pwd.
 * @return int Returns 1 if pwd->value == NULL and 0 if not.
 */
static int	update_pwd_values(char *new_pwd, t_env_var *old_pwd, t_env_var *pwd)
{
	char	new_cwd[PATH_MAX];

	if (chdir(new_pwd) < 0)
		return (ft_dprintf(2, "fsf\n"), print_error(NO_FILE_DIR, new_pwd), \
			free(new_pwd), 1);
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	getcwd(new_cwd, PATH_MAX);
	pwd->value = ft_strdup(new_cwd);
	if (pwd->value == NULL)
		return (mem_error(), 1);
	return (0);
}

static int	get_new_pwd(t_cmd *cmd, t_env *env, char **new_pwd)
{
	if (cmd->args == NULL)
	{
		*new_pwd = ft_strdup(get_env_value(env->env_vars, "HOME"));
		if (*new_pwd == NULL)
			return (print_error("not set", "HOME"), 1);
	}
	else
	{
		*new_pwd = ft_strdup(cmd->arg_arr[1]);
		if (*new_pwd == NULL)
			return (mem_error(), 1);
	}
	return (0);
}

/**
 * @brief	Change the current working directory and update the 
 * 			PATH and OLDPWD vars.
 * 
 * @param cmd The structure with the parsed command and its arguments.
 * @param env The structure with the current environment variables.
 * @return int Returns 0 if the command was executed successfully, an
 * 1 in case of an error.
 */
int	cd(t_cmd *cmd, t_env *env)
{
	t_list		*wrk;
	t_env_var	*old_pwd;
	t_env_var	*pwd;
	char		*new_pwd;

	new_pwd = NULL;
	wrk = get_env_var(env->env_vars, "PWD");
	if (wrk == NULL)
		return (0);
	pwd = (t_env_var *)wrk->content;
	wrk = get_env_var(env->env_vars, "OLDPWD");
	if (wrk == NULL)
		return (1 << 8);
	old_pwd = (t_env_var *)wrk->content;
	if (get_new_pwd(cmd, env, &new_pwd))
		return (1 << 8);
	if (update_pwd_values(new_pwd, old_pwd, pwd))
		return (1 << 8);
	free(new_pwd);
	return (0);
}
