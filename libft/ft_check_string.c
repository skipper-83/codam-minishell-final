/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 23:01:08 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/13 23:09:24 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Checks if the characters in the string comply to the char test 
 * 			function passed as an argument. Returns 1 if ALL characters
 * 			comply to the test.
 * 
 * @param input 
 * @param check_func 
 * @return int 
 */
int	ft_check_string(char *input, int (*check_func)(int c))
{
	if (input == NULL || check_func == NULL)
		return (0);
	while (*input)
		if (!check_func(*(input++)))
			return (0);
	return (1);
}
