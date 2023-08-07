/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:48:18 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 20:32:39 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief allocate count * size bytes and fill with zeroes
 * 
 * @param count 
 * @param size 
 * @return void* 
 */
void	*ft_calloc(size_t count, size_t size)
{
	char	*ret;
	size_t	i;
	size_t	width;

	width = size * count;
	if (width > 0 && width / count != size)
		return (NULL);
	i = 0;
	ret = (char *)malloc(width);
	if (ret == NULL)
		return (NULL);
	while (i < width)
		ret[i++] = 0;
	return (ret);
}
