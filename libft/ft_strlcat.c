/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:34:36 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:24:39 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief add src to dst up to dstsize - 1 characters
 * 
 * @param dst 
 * @param src 
 * @param dstsize 
 * @return size_t 
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_length;
	size_t	src_length;
	size_t	i;

	i = 0;
	src_length = ft_strlen(src);
	if (!dstsize && !dst)
		return (src_length);
	dst_length = ft_strlen(dst);
	if (dst_length >= dstsize)
		return (dstsize + src_length);
	while (dstsize - (dst_length + 1 + i) > 0 && src[i])
	{
		dst[dst_length + i] = src[i];
		i++;
	}
	dst[dst_length + i] = '\0';
	return (dst_length + src_length);
}
