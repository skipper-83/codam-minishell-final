/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:02:35 by albertvanan       #+#    #+#             */
/*   Updated: 2022/11/17 13:56:02 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief 	returns n to the power of exp
 * 			where exp >=0
 * 
 * @param n 
 * @param exp 
 * @return int
 */
int	ft_pow(int n, int exp)
{
	if (exp > 0)
		return (n * ft_pow(n, exp - 1));
	else
		return (1);
}
