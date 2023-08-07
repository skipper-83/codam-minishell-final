/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:46:14 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 17:17:20 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Return absolute value of number n
 * 
 * @param n 
 * @return int 
 */
int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

/**
 * @brief	Return absolute value of number n
 * 
 * @param n 
 * @return int 
 */
long	ft_labs(long n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

