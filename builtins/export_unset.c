/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:51:04 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 16:27:21 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"

/**
 * @brief	Display error message when variable key does not match
 * 			the bash criteria
 * 
 * @param token 
 * @return int 
 */
static int	export_error(char *cmd_id, char *token)
{
	ft_putstr_fd(cmd_id, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("' is not a valid identifier", 2);
	return (1);
}

/**
 * @brief	Helper for export. Sets new variable if the argument
 * 			passed to export is in the form var=value.
 * 
 * @param wrk 
 * @param env 
 * @return int 
 */
static int	set_new_export_var(t_cmd *wrk, t_env *env)
{
	t_env_var	*cur;
	t_list		*found_var;
	t_list		*new;

	cur = make_var(wrk->literal);
	if (cur == NULL)
		return (1);
	found_var = get_env_var(env->env_vars, cur->key);
	if (found_var != NULL)
	{
		free(((t_env_var *)found_var->content)->value);
		((t_env_var *)found_var->content)->value = cur->value;
		((t_env_var *)found_var->content)->export = 1;
		free (cur->key);
		free (cur);
		return (0);
	}
	if (!check_var_key(cur->key))
		return (free_env_struct(cur), export_error("export", wrk->literal));
	cur->export = 1;
	new = ft_lstnew(cur);
	if (new == NULL)
		return (mem_error(), 1);
	ft_lstadd_back(&env->env_vars, new);
	return (0);
}

/**
 * @brief	Helper for export. Check if var key is valid,
 * 			return 1 of it isn't. Set flag to 1 if var exists.
 * 
 * @param wrk 
 * @param env 
 * @return int 
 */
static int	export_existing_var(t_cmd *wrk, t_env *env)
{
	t_list		*found_var;

	if (!check_var_key(wrk->literal))
	{
		export_error("export", wrk->literal);
		return (1);
	}
	found_var = get_env_var(env->env_vars, wrk->literal);
	if (found_var != NULL)
		((t_env_var *)found_var->content)->export = 1;
	return (0);
}

/**
 * @brief	Unset variables passed in the arguments list.
 * 			Returns 1 if a variable name does not match bash'
 * 			criteria, but keeps unsetting others if available.
 * 
 * @param cmd 
 * @param env 
 * @return int 
 */
int	unset(t_cmd *cmd, t_env *env)
{
	t_list	*found_var;
	t_cmd	*cur;
	t_list	*wrk_li;
	int		retval;

	wrk_li = cmd->args;
	retval = 0;
	while (wrk_li)
	{
		cur = (t_cmd *)wrk_li->content;
		if (!check_var_key(cur->literal))
			retval = export_error("unset", cur->literal);
		found_var = get_env_var(env->env_vars, cur->literal);
		if (found_var != NULL)
			ft_lstdel_item(&env->env_vars, found_var, free_env_struct);
		wrk_li = wrk_li->next;
	}
	return (retval << 8);
}

/**
 * @brief	Export variables in arg list. Set its export flag to 1 when its
 * 			already set, or make a new one if it isnt. If the variable
 * 			is new but no value is set, store it as empty 
 * 			(eg export new_var -> new_var=)
 * 			If a variable name is wrong it retuns 1 but keeps going on exporting
 * 			other vars
 * 
 * @param cmd 
 * @param env 
 * @return int 
 */
int	export_ceash(t_cmd *cmd, t_env *env)
{
	t_list		*wrk_li;
	int			retval;

	wrk_li = cmd->args;
	retval = 0;
	if (cmd->args == NULL)
		retval = print_export_list(cmd, env);
	else
	{
		while (wrk_li)
		{
			if (is_var(((t_cmd *)wrk_li->content)->literal, 0))
				retval += set_new_export_var((t_cmd *)wrk_li->content, env);
			else
				retval += export_existing_var((t_cmd *)wrk_li->content, env);
			wrk_li = wrk_li->next;
		}
	}
	if (retval > 0)
		return (1 << 8);
	return (0);
}
