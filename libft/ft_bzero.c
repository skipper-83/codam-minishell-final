/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:34:51 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:16:06 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief write n zeroed bytes to string s
 * 
 * @param s 
 * @param n 
 */
void	ft_bzero(void *s, size_t n)
{
	char	*s_c;

	s_c = s;
	while (n--)
	{
		*(s_c++) = '\0';
	}
}
