/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:29:13 by albertvanan       #+#    #+#             */
/*   Updated: 2023/01/04 01:07:48 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief round float value
 * 
 * @param val 
 * @return int 
 */
int	ft_round(float val)
{
	float	temp;

	temp = (val - (int)val) * 10;
	if (temp >= 5)
		return ((int)val + 1);
	return ((int)val);
}
