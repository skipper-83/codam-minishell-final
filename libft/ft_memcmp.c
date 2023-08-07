/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:00:14 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:20:33 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief compare n bytes of memory between s1 and 2 and return the diff
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*s1_char;
	char	*s2_char;

	s1_char = (char *)s1;
	s2_char = (char *)s2;
	while (n--)
	{
		if (*s1_char != *s2_char)
			return ((unsigned char)*s1_char - (unsigned char)*s2_char);
		s1_char++;
		s2_char++;
	}
	return (0);
}
