/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:55:52 by avan-and          #+#    #+#             */
/*   Updated: 2023/08/07 15:13:48 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"

/**
 * @brief Sorts the envp char array passed to it alphabetically
 * 
 * @param envp 
 */
static void	sort_env(char **envp)
{
	int		i;
	int		len;
	char	*buf;

	i = 0;
	while (envp[i + 1])
	{
		len = ft_min(ft_strlen(envp[i]), ft_strlen(envp[i + 1]));
		if (ft_strncmp(envp[i], envp[i + 1], len) > 0)
		{
			buf = envp[i];
			envp[i] = envp[i + 1];
			envp[i + 1] = buf;
			i = 0;
		}
		else
			i++;
	}
}

/**
 * @brief Prints the list of exported variables. Prepends "declare -x" to 
 * 			it and adds quotes just like bash.
 * 
 * @param cmd 
 * @param env 
 * @return int 
 */
int	print_export_list(t_cmd *cmd, t_env *env)
{
	char	**env_arr;
	char	*cur;
	int		i;

	i = 0;
	env_arr = make_env_arr(env, cmd);
	if (env_arr == NULL)
		return (mem_error(), 1);
	sort_env(env_arr);
	while (env_arr[i])
	{
		cur = ft_strchr(env_arr[i], '=');
		cur[0] = 0;
		ft_printf("declare -x %s=", env_arr[i]);
		ft_printf("\"%s\"\n", &cur[1]);
		i++;
	}
	free_2d_arr(env_arr);
	return (0);
}
