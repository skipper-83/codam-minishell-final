/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 13:48:19 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/05 10:46:02 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Makes a new cmd struct for a var set command (eg only var=1 is passed)
 * 			Adds this struct to the correct place in the command list.
 * 
 * @param the_command 
 * @param env 
 * @param prev 
 * @return int 
 */
int	make_var_set_cmd(t_cmd **the_command, t_env *env, t_list *prev)
{
	t_cmd	*res;
	t_list	*new_item;
	char	*lit;

	res = ft_calloc(1, sizeof(t_cmd));
	lit = ft_strdup("VAR_SET");
	if (res == NULL || lit == NULL)
		return (mem_error(), 0);
	res->literal = lit;
	res->is_var_setter = 1;
	*the_command = res;
	new_item = ft_lstnew(res);
	if (new_item == NULL)
		return (free_cmd_struct(res), mem_error(), 0);
	if (prev == NULL || prev->content == NULL)
		ft_lstadd_front(&env->cmd_list, new_item);
	else
		ft_lstadd_middle(new_item, prev, prev->next);
	return (1);
}

/**
 * @brief	Takes input in the vorm of varname=value and returns
 * 			a t_env_var struct with with 
 * 			var->key = varname
 * 			var->value = value
 * 
 * @param input 
 * @return t_env_var* 
 */
t_env_var	*make_var(char *input)
{
	int			i;
	t_env_var	*var;

	i = 0;
	while (input[i] != '=')
		i++;
	input[i] = 0;
	var = ft_calloc(1, sizeof(t_env_var));
	if (var == NULL)
		return (mem_error(), NULL);
	var->key = ft_strdup(input);
	var->value = ft_strdup(&input[i + 1]);
	input[i] = '=';
	if (var->key == NULL || var->value == NULL)
		return (mem_error(), NULL);
	return (var);
}

/**
 * @brief	Add a variable setter to the list.
 * 
 * @param vars 
 * @param cmd 
 * @param cmd_list 
 * @return int 
 */
int	add_var(t_list **vars, t_list **cmd, t_list **cmd_list)
{
	t_env_var	*var;
	t_list		*var_li;
	t_list		*wrk_li;

	var = make_var(((t_cmd *)(*cmd)->content)->literal);
	if (var == NULL)
		return (0);
	var_li = ft_lstnew(var);
	if (var_li == NULL)
		return (mem_error(), 0);
	ft_lstadd_back(vars, var_li);
	wrk_li = *cmd;
	*cmd = (*cmd)->next;
	ft_lstdel_item(cmd_list, wrk_li, free_cmd_struct);
	return (1);
}

/**
 * @brief	Checks if input conforms to bash rules for a variable name
 * 			(only alfanumeric and underscore, at least one letter)
 * 
 * @param input 
 * @return int 
 */
int	check_var_key(char *input)
{
	int	has_alfa;

	has_alfa = 0;
	while (*input)
	{
		if (ft_isalpha(*input))
			has_alfa = 1;
		if (!ft_isalnum(*input) && *input != '_')
			return (0);
		input++;
	}
	if (!has_alfa)
		return (0);
	return (1);
}

/**
 * @brief	Checks if an input literal is a variable declaration (ie var1=value)
 * 			optional: checks if the key conforms to the bash rules for a variable name
 * 			(only alfanum and backslash, at least one character)
 * 
 * @param input the string to be checked
 * @param check_key if set to 1 function will check if key conforms to bash rules
 * @return int 
 */
int	is_var(char *input, int check_key)
{
	char	*eq;
	int		ret;

	eq = ft_strchr(input, '=');
	if (eq == NULL)
		return (0);
	if (input[0] == '=')
		return (0);
	if (check_key)
	{
		eq[0] = 0;
		ret = check_var_key(input);
		eq[0] = '=';
		return (ret);
	}
	return (1);
}
