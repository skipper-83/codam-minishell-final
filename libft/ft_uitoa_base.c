/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:28:15 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 17:37:35 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits_base(unsigned long long int n, int ret, int base_len);

/**
 * @brief		turn an unsinged number of max llu size to ascii with
*	 			the base provide in base
 * 
 * @param n 	the number to be converted
 * @param base	string with the digits used in base. Each char should be
 * 				used only once (this is not checked), string length
 * 				is radix
 * @return char* 
 */
char	*ft_uitoa_base(unsigned long long int n, char *base)
{
	char	*ret;
	int		len;
	int		base_len;

	base_len = ft_strlen(base);
	len = digits_base(n, 0, base_len);
	ret = (char *)ft_calloc(sizeof(char), len + 1);
	if (ret == NULL)
		return (NULL);
	while (len)
	{
		ret[len - 1] = base[n % base_len];
		n /= base_len;
		len--;
	}
	return (ret);
}

/**
 * @brief	return amount of digits of number n in base base
 * 			function is recursive, pass ret as 0 in first call
 * 
 * @param n 
 * @param ret 
 * @param base_len 
 * @return int 
 */
static int	digits_base(unsigned long long int n, int ret, int base_len)
{
	if (n / base_len)
		ret += digits_base(n / base_len, ret, base_len);
	return (ret + 1);
}
