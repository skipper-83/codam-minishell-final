/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:11:39 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:31:20 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief return string pointer on last occurance of c
 * 
 * @param str 
 * @param c 
 * @return char* 
 */
char	*ft_strrchr(const char *str, int c)
{
	size_t	i;

	i = ft_strlen(str) + 1;
	while (i--)
	{
		if (str[i] == (unsigned char) c)
			return ((char *) &str[i]);
	}
	return (NULL);
}
