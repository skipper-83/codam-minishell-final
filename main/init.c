/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:37:54 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 16:39:28 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "main.h"

static int	set_env_var(t_env *env, char *key, char *value, int export)
{
	t_env_var	*new_env_var;
	t_list		*new;

	new_env_var = malloc(sizeof(t_env_var));
	if (new_env_var == NULL)
		return (mem_error(), 0);
	new_env_var->key = ft_strdup(key);
	new_env_var->value = ft_strdup(value);
	new_env_var->export = export;
	new = ft_lstnew(new_env_var);
	if (new_env_var->key == NULL || new_env_var->value == NULL || new == NULL)
		return (mem_error(), 0);
	ft_lstadd_back(&env->env_vars, new);
	return (1);
}

static int	set_shlvl(t_env *env)
{
	int			shlvl;
	t_list		*shlvl_li;
	t_env_var	*shlvl_var;

	shlvl_li = get_env_var(env->env_vars, "SHLVL");
	if (shlvl_li == NULL)
		return (set_env_var(env, "SHLVL", "1", 1));
	shlvl_var = (t_env_var *)shlvl_li->content;
	shlvl = ft_atoi(shlvl_var->value);
	free (shlvl_var->value);
	shlvl_var->value = ft_itoa(++shlvl);
	if (shlvl_var->value == NULL)
		return (mem_error(), 0);
	return (1);
}

int	init(t_env **env, char **envp, char **buf, char **argv)
{
	*env = ft_calloc(1, sizeof(t_env));
	if (env == NULL)
		return (0);
	(*env)->env_vars = make_env_list(envp);
	if ((*env)->env_vars == NULL)
		return (0);
	if (!set_env_var(*env, "PS1", PROMPT, 0) || !set_shlvl(*env))
		return (0);
	if (argv[1] && !ft_strcmp(argv[1], "-v"))
		(*env)->verbose = 1;
	prompt(buf, *env);
	return (1);
}
