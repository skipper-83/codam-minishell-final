/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:47:58 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:17:14 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief take an int and check if its printable
 * 
 * @param c 
 * @return int 
 */
int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}
