/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:15:59 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:20:26 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief check if c occurs in the first n bytes of s
 * 
 * @param s 
 * @param c 
 * @param n 
 * @return void* 
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_char;

	s_char = s;
	while (n--)
	{
		if (*s_char == (unsigned char) c)
			return ((void *)s_char);
		s_char++;
	}
	return (NULL);
}
