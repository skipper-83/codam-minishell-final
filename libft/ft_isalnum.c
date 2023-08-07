/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:21:09 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:16:32 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief allocate count * size bytes and fill with zeroes
 * 
 * @param c 
 * @return int 
 */
int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
