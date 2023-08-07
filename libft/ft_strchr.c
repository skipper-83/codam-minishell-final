/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:11:39 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:23:58 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief return string pointer on first occurance of c
 * 
 * @param str 
 * @param c 
 * @return char* 
 */
char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char) c)
			return ((char *)str);
		str++;
	}
	if (*str == (unsigned char)c)
		return ((char *)str);
	return (NULL);
}
