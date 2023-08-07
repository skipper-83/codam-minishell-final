/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 14:22:19 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/07/13 17:10:23 by eluse         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Used by make_env_list: returns the position of the first equializer	
 * 			character in the input string.
 * 
 * @param input 
 * @return int 
 */
static int	get_equalizer_position(char	*input)
{
	int	res;

	res = 0;
	while (input[res] && input[res] != '=')
		res++;
	return (res);
}

/**
 * @brief	Make a list from the envp array passed to the main.
 * 
 * @param envp 
 * @return t_list* 
 */
t_list	*make_env_list(char **envp)
{
	int			i;
	int			eq_pos;
	t_list		*res;
	t_list		*wrk_li;
	t_env_var	*var;

	i = 0;
	res = NULL;
	while (envp[i])
	{
		eq_pos = get_equalizer_position(envp[i]);
		var = malloc(sizeof(t_env_var));
		if (var == NULL)
			return (mem_error(), NULL);
		var->key = ft_substr(envp[i], 0, eq_pos);
		var->value = ft_strdup(&envp[i][eq_pos + 1]);
		var->export = 1;
		wrk_li = ft_lstnew(var);
		if (wrk_li == NULL || var->key == NULL || var->value == NULL)
			return (mem_error(), NULL);
		ft_lstadd_front(&res, wrk_li);
		i++;
	}
	return (res);
}

/**
 * @brief Free an env struct
 * 
 * @param param 
 */
void	free_env_struct(void *param)
{
	t_env_var	*var;

	var = (t_env_var *)param;
	free(var->key);
	free(var->value);
	free(var);
}

/**
 * @brief	Get the t_list containting the t_env_var with key [key]
 * 			returns NULL if not found.
 * 
 * @param env 
 * @param key 
 * @return t_list* 
 */
t_list	*get_env_var(t_list	*env, char *key)
{
	char	*var_key;

	while (env)
	{
		var_key = ((t_env_var *)env->content)->key;
		if (!ft_strcmp(var_key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief	Returns the value of the env variable with key [key]
 * 			as a char *. Returns NULL if not found.
 * 
 * @param env_var_list
 * @param key 
 * @return char* 
 */
char	*get_env_value(t_list	*env_var_list, char *key)
{
	char	*var_key;

	while (env_var_list)
	{
		var_key = ((t_env_var *)env_var_list->content)->key;
		if (!ft_strcmp(var_key, key))
			return (((t_env_var *)env_var_list->content)->value);
		env_var_list = env_var_list->next;
	}
	return (NULL);
}
