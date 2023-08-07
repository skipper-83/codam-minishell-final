/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:20:38 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:24:23 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief apply function f on all characters of string s
 * 
 * @param s 
 * @param f 
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
