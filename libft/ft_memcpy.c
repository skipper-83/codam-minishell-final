/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:34:03 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:20:47 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief copy n bytes from src to dst
 * 
 * @param dst 
 * @param src 
 * @param n 
 * @return void* 
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_c;
	char	*src_c;

	if (!dst || !src)
		return (NULL);
	dst_c = (char *)dst;
	src_c = (char *)src;
	while (n--)
		*(dst_c++) = *(src_c++);
	return (dst);
}
