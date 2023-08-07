/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:00:09 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:21:11 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief take a char* and write len instances of c to it
 * 
 * @param b 
 * @param c 
 * @param len 
 * @return void* 
 */
void	*ft_memset(void *b, int c, size_t len)
{
	char	*new;

	new = b;
	c = (unsigned char) c;
	while (len)
	{
		*(new++) = c;
		len--;
	}
	return (b);
}
