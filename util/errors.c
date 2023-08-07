/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:31:32 by albertvanan       #+#    #+#             */
/*   Updated: 2023/06/08 13:07:16 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Funcion to save some characters on those mem error return lines
 * 
 */
void	mem_error(void)
{
	ft_putendl_fd(ERR_MEM, 2);
}

/**
 * @brief	Function to throw informative error when there is
 * 			a parse error encountered. 
 * 
 * @param param 
 * @param description 
 */
void	parse_error(void *param, char *description)
{
	ft_putstr_fd("Parse error near token ", 2);
	if (param != NULL)
		ft_putstr_fd(((t_cmd *)param)->literal, 2);
	else
		ft_putstr_fd("\\n", 2);
	if (description != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(description, 2);
	}
	ft_putchar_fd('\n', 2);
}
