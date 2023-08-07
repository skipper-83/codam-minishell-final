/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:58:35 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/20 23:21:59 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits(signed long long n, int ret);
static void	fill_numbers(int len, int sign, long double n, char *ret);
static void	fill_float(int prec, char *ret, int len, long double after_point);

/**
 * @brief float to ascii
 * 
 * @param n 
 * @param precision 
 * @return char* 
 */
char	*ft_ftoa(long double n, int precision)
{
	char		*ret;
	int			len;
	int			sign;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = digits((signed long long)n, 0) + sign;
	if (precision > 0)
		len += precision + 1;
	ret = (char *)ft_calloc(sizeof(char), len + 1);
	if (!ret)
		return (NULL);
	fill_numbers(len - precision - 1, sign, n, ret);
	if (sign)
		n *= -1;
	fill_float(precision, ret, len, n - (long long int)n);
	if (sign)
		ret[0] = '-';
	return (ret);
}

/**
 * @brief 	norminette-induced function split,
 * 			add the integral digits to the return string
 * 
 * @param len 
 * @param sign 
 * @param n 
 * @param ret 
 */
static void	fill_numbers(int len, int sign, long double n, char *ret)
{
	while (--len + 1 - sign)
	{
		if (sign)
			ret[len] = (signed long long) n % 10 * -1 + '0';
		else
			ret[len] = (signed long long) n % 10 + '0';
		n /= 10;
	}
}

/**
 * @brief	norminette-induced function split,
 * 			add the float digits to the return string
 * 			(remove digits added to avoid int overflow)
 * 
 * @param prec 
 * @param ret 
 * @param len 
 * @param after_point 
 */
static void	fill_float(int prec, char *ret, int len, long double after_point)
{
	if (prec > 0)
		ret[len - prec - 1] = '.';
	while (prec > 0)
	{
		after_point *= 10;
		ret[len - prec] = (unsigned int)after_point % 10 + '0';
		after_point -= (int)after_point;
		--prec;
	}
}

/**
 * @brief count the number of digits in int n
 * 
 * @param n 
 * @param ret 
 * @return int 
 */
static int	digits(signed long long n, int ret)
{
	if (n / 10)
		ret += digits(n / 10, ret);
	return (ret + 1);
}
