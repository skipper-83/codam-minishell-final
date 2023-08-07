/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:05:56 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:31:55 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief check if number is upper case alpha and concert it to lowercase
 * 
 * @param c 
 * @return int 
 */
int	ft_tolower(int c)
{
	if ((unsigned char)c >= 'A' && (unsigned char)c <= 'Z')
		c += 32;
	return (c);
}
