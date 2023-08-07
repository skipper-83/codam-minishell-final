/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:43:48 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/05 16:56:53 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returns the literal of a command node.
 * 
 * @param param 
 * @return char* 
 */
char	*get_lit(void *param)
{
	return (((t_cmd *)param)->literal);
}

/**
 * @brief	Used as pointed function in list_to_arr, takes the env list
 * 			and combines the keys and values into a string with "key=value"
 * 
 * @param param 
 * @return char* 
 */
char	*make_env_arr_item(void *param)
{
	t_env_var	*env_var;
	char		*res;
	int			len;
	int			i;

	env_var = (t_env_var *)param;
	len = ft_strlen(env_var->key) + ft_strlen(env_var->value) + 1;
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (mem_error(), NULL);
	res[len] = 0;
	ft_strlcpy(&res[0], env_var->key, ft_strlen(env_var->key) + 1);
	i = ft_strlen(env_var->key);
	res[i] = '=';
	i++;
	ft_strlcpy(&res[i], env_var->value, ft_strlen(env_var->value) + 1);
	return (res);
}

/**
 * @brief	Make 2D char array from list, used to format argv and envp arguments
 * 			for execve. Use pointed function in second argument to obtain the 
 * 			correct char * for each array.
 * 
 * 			Usage:
 * 			for argv: list_to_arr([head of arg list], get_lit)
 * 			free only the array, as the items are freed when the command list is 
 * 			freed
 * 
 * 			for envp: list_to_arr([head of env list], make_arr_env)
 * 			use free_2d_arr to free the resulting char** array, as make_arr_env 
 * 			allocates memory to combine the key and value pairs in to key=value
 * 
 * @param list 	the list to be converted into a char**
 * @param get_char_from_lstitem function that returns a char from the content 
 * 								void * in the list item
 * @return char** 
 */
char	**list_to_arr(t_list *list, char *(*get_char_from_lstitem)(void *param))
{
	int		size;
	int		i;
	char	**res;

	size = ft_lstsize(list);
	res = malloc(sizeof(char *) * (size + 1));
	i = 0;
	if (res == NULL)
		return (mem_error(), NULL);
	res[size] = NULL;
	while (list)
	{
		res[i] = get_char_from_lstitem(list->content);
		if (res[i] == NULL)
			return (mem_error(), free_2d_arr(res), NULL);
		list = list->next;
		i++;
	}
	return (res);
}

/**
 * @brief Frees 2d array
 * 
 * @param arr 
 */
void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
