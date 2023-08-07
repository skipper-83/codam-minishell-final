/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:02:01 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/11 11:10:21 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_value(char *base, int radix, char digit)
{
	int	res;

	res = 0;
	while (res < radix)
	{
		if (ft_tolower(base[res]) == ft_tolower(digit))
			return (res);
		res++;
	}
	return (-1);
}

/**
 * @brief	Convert a string with an unsigned value in base [base] with 
 * 			prefix [prefix] to unsigned int. Case insensitive.
 * 			Ex: ft_atou_base("0XFF", "0123456789abcdef", "0x") = 255
 * 
 * @param str 
 * @param base 
 * @param prefix 
 * @return unsigned int 
 */
size_t	ft_atou_base(char *str, char *base, char *prefix)
{
	unsigned int	res;
	int				radix;
	int				digit;

	res = 0;
	radix = ft_strlen(base);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*prefix)
	{
		if (ft_tolower(*str) != ft_tolower(*prefix))
			return (0);
		prefix++;
		str++;
	}
	while (*str)
	{
		digit = digit_value(base, radix, *str);
		if (digit < 0)
			return (res);
		res = (res * radix) + digit;
		str++;
	}
	return (res);
}
