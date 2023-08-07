/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:52:09 by avan-and          #+#    #+#             */
/*   Updated: 2023/07/05 16:56:20 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief 	move len bytes from src to dst
 * 			move backwards if address of dst is larger than address of src
 * 			to avoid data destruction
 * 
 * @param dst 
 * @param src 
 * @param len 
 * @return void* 
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_c;
	char	*src_c;

	if (!dst && !src)
		return (NULL);
	dst_c = (char *)dst;
	src_c = (char *)src;
	if (dst > src)
	{
		while (len--)
			dst_c[len] = src_c[len];
	}
	else
	{
		while (len--)
			*(dst_c++) = *(src_c++);
	}
	return (dst);
}
