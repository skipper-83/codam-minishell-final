/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:54:40 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:25:40 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief compare n characters of s1 and s2, return diff
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n--)
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
	}
	return (0);
}
