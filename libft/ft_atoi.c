/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:31:03 by avan-and          #+#    #+#             */
/*   Updated: 2023/08/07 22:52:47 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief take ascii string and convert number in it to INT
 * 
 * @param str 
 * @return int 
 */
int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	sign = 1;
	result = 0;
	i = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (ft_isdigit(str[i]))
	{
		if (i > 19)
			return ((int)(((unsigned int) sign * -1) - 1) / 2);
		result = result * 10 + str[i] - '0' ;
		i++;
	}
	return (result * sign);
}

/**
 * @brief take ascii string and convert number in it to INT
 * 
 * @param str 
 * @return int 
 */
long	ft_atoli(const char *str)
{
	long	sign;
	long	result;
	int		i;

	sign = 1;
	result = 0;
	i = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (ft_isdigit(str[i]))
	{
		if (i > 19)
			return ((int)(((unsigned int) sign * -1) - 1) / 2);
		result = result * 10 + str[i] - '0' ;
		i++;
	}
	return (result * sign);
}

/**
 * @brief Returns a number as a size_t. Pass pointer to int
 * 		to get the original sign, so you can use it to check really 
 * 		big numbers.
 * 
 * @param str 
 * @param sign 
 * @return size_t 
 */
size_t	ft_atosizet(const char *str, int *sign)
{
	size_t	result;
	int		i;

	*sign = 0;
	result = 0;
	i = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0' ;
		i++;
	}
	return (result);
}
