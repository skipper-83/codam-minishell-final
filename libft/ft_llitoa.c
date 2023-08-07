/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:28:15 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 21:49:24 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits(long long int n, int ret);

/**
 * @brief	turn number n of max lon long int size 
 * 			into ascii
 * 
 * @param n 
 * @return char* 
 */
char	*ft_llitoa(long long int n)
{
	char	*ret;
	int		len;
	int		sign;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = digits(n, 0) + sign;
	ret = (char *)ft_calloc(sizeof(char), len + 1);
	if (ret == NULL)
		return (NULL);
	while (len - sign)
	{
		if (sign)
			ret[len - 1] = n % 10 * -1 + '0';
		else
			ret[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	if (sign)
		ret[0] = '-';
	return (ret);
}

static int	digits(long long int n, int ret)
{
	if (n / 10)
		ret += digits(n / 10, ret);
	return (ret + 1);
}
