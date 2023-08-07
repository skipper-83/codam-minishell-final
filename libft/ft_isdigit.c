/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:21:09 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:17:03 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief take an int and check if its a number '1' -> '9'
 * 
 * @param c 
 * @return int 
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
