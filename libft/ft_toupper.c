/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:05:56 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:32:09 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief check if number is lower case alpha and concert it to uppercase
 * 
 * @param c 
 * @return int 
 */
int	ft_toupper(int c)
{
	if ((unsigned char)c >= 'a' && (unsigned char)c <= 'z')
		c -= 32;
	return (c);
}
