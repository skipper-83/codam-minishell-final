/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:37:54 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/08 13:06:22 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "main.h"

/**
 * @brief Get the shell level to the appropiate level
 * 
 * @param env 
 * @return int 
 */
static int	set_shlvl(t_env *env)
{
	int			shlvl;
	t_list		*shlvl_li;
	t_env_var	*shlvl_var;

	shlvl_li = get_env_var(env->env_vars, "SHLVL");
	if (shlvl_li == NULL)
		return (add_env_var(env, "SHLVL", "1", 1));
	shlvl_var = (t_env_var *)shlvl_li->content;
	shlvl = ft_atoi(shlvl_var->value);
	free (shlvl_var->value);
	shlvl_var->value = ft_itoa(++shlvl);
	if (shlvl_var->value == NULL)
		return (mem_error(), 0);
	return (1);
}

/**
 * @brief Reset OLDPWD, and set PWD and HOME if they arrive unset
 * 
 * @param env 
 * @return int 
 */
int	reset_important_env_vars(t_env *env)
{
	t_list		*wrk;
	t_env_var	*old_pwd;	

	wrk = get_env_var(env->env_vars, "OLDPWD");
	if (wrk == NULL)
	{
		if (!add_env_var(env, "OLDPWD", "", 1))
			return (0);
	}
	else
	{
		old_pwd = (t_env_var *)wrk->content;
		free (old_pwd->value);
		old_pwd->value = ft_strdup("");
		if (old_pwd->value == NULL)
			return (mem_error(), 0);
	}
	wrk = get_env_var(env->env_vars, "HOME");
	if (wrk == NULL)
		if (!add_env_var(env, "HOME", "", 1))
			return (0);
	wrk = get_env_var(env->env_vars, "PWD");
	if (wrk == NULL)
		return (add_env_var(env, "PWD", "", 1));
	return (1);
}

/**
 * @brief Initialize the env struct and some important variables
 * 			throw the first prompt.
 * 
 * @param env 
 * @param envp 
 * @param buf 
 * @param argv 
 * @return int 
 */
int	init(t_env **env, char **envp, char **buf, char **argv)
{
	*env = ft_calloc(1, sizeof(t_env));
	if (env == NULL)
		return (0);
	(*env)->env_vars = make_env_list(envp);
	if ((*env)->env_vars == NULL)
		return (0);
	if (!add_env_var(*env, "PS1", PROMPT, 0) || \
					!set_shlvl(*env) || !reset_important_env_vars(*env))
		return (0);
	if (argv[1] && !ft_strcmp(argv[1], "-v"))
		(*env)->verbose = 1;
	prompt(buf, *env);
	return (1);
}
