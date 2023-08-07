/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:10:08 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:24:54 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	copy up to dstlen - 1 characters from src to dst,
 * 			terminating dst with \0
 * 
 * @param dst 
 * @param src 
 * @param dstlen 
 * @return size_t 
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstlen)
{
	size_t	src_length;
	size_t	i;

	src_length = ft_strlen((char *)src);
	i = 0;
	if (dstlen > 0)
	{
		while (i < dstlen - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_length);
}
