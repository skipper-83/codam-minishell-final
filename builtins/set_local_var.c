/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_local_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:34:34 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 11:28:27 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Helper for set_local_var(). Sets the actual var
 * 
 * @param to_set 
 * @param env 
 * @return int 
 */
static int	set_var(t_env_var *to_set, t_env *env)
{
	t_list	*set_before;
	t_list	*new;

	set_before = get_env_var(env->env_vars, to_set->key);
	if (set_before != NULL)
	{
		free(((t_env_var *)set_before->content)->value);
		((t_env_var *)set_before->content)->value = to_set->value;
		free(to_set->key);
		free(to_set);
		return (1);
	}
	new = ft_lstnew(to_set);
	if (new == NULL)
		return (mem_error(), 0);
	ft_lstadd_back(&env->env_vars, new);
	return (1);
}

/**
 * @brief Store a local variable.
 * 
 * @param cmd 
 * @param env 
 * @return int 
 */
int	set_local_vars(t_cmd *cmd, t_env *env)
{
	t_list	*wrk_li;
	t_list	*buf;

	wrk_li = cmd->vars;
	while (wrk_li)
	{
		if (!set_var(wrk_li->content, env))
			return (1 << 8);
		buf = wrk_li;
		wrk_li = wrk_li->next;
		ft_lstdel_item(&cmd->vars, buf, NULL);
	}
	cmd->vars = NULL;
	return (0);
}
