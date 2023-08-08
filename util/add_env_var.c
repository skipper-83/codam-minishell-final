/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:37:14 by avan-and          #+#    #+#             */
/*   Updated: 2023/08/08 13:03:43 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env_var(t_env *env, char *key, char *value, int export)
{
	t_list		*var_li;
	t_env_var	*var;

	var = malloc(sizeof(t_env_var));
	var_li = ft_lstnew(var);
	if (var == NULL || var_li == NULL)
		return (mem_error(), 0);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	var->export = export;
	if (var->key == NULL || var->value == NULL)
		return (mem_error(), 0);
	ft_lstadd_back(&env->env_vars, var_li);
	return (1);
}
