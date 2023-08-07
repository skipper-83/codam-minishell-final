/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:11:06 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 15:50:05 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Helper for expand(), gets the value associated with the key
 * 			if the key is '?' return the stringified last return value,
 * 			else look it up in the env_vars struct.
 * 
 * @param key 
 * @param env 
 * @param value 
 */
static void	get_value(char *key, t_env *env, char **value)
{
	char	*last_exit;

	if (key[0] == '?')
	{
		last_exit = ft_itoa(env->last_exit);
		if (last_exit == NULL)
			*value = NULL;
		else
			*value = ft_strjoin(last_exit, &key[1]);
		free (last_exit);
	}
	else
	{
		*value = get_env_value(env->env_vars, key);
		if (*value == NULL)
			*value = ft_strdup("");
		else
			*value = ft_strdup(*value);
	}
	free (key);
}

/**
 * @brief	Called when the parser sees a dollar sign. If there is no literal after
 * 			the dollar sign, the sign is treated as a literal. 
 * 			Otherwise, the dollar sign is deleted, and the literal after it is 
 * 			replaced by the value found with get_env_value(), or with "" is no 
 * 			value was found.
 * 
 * @param cmd 
 * @param env 
 * @return int 
 */
int	expand(t_list **cmd, t_env *env)
{
	t_list	*buf;
	char	*value;
	char	*key;

	if ((*cmd)->next == NULL || \
			((*cmd)->next && ((t_cmd *)(*cmd)->next->content)->type != LITERAL))
	{
		((t_cmd *)(*cmd)->content)->type = LITERAL;
		return (1);
	}
	buf = *cmd;
	*cmd = (*cmd)->next;
	ft_lstdel_item(&env->cmd_list, buf, free_cmd_struct);
	key = ((t_cmd *)(*cmd)->content)->literal;
	get_value(key, env, &value);
	((t_cmd *)(*cmd)->content)->literal = value;
	if (!value[0])
	{
		buf = *cmd;
		*cmd = (*cmd)->next;
		ft_lstdel_item(&env->cmd_list, buf, free_cmd_struct);
	}
	return (1);
}
