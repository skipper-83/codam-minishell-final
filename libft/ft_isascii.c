/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:44:26 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:16:54 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief take an int and return if its ascii (0 - 127 decimal)
 * 
 * @param c 
 * @return int 
 */
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
