/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:25:43 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:24:30 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief join s1 and s2 in newly allocated string
 * 
 * @param s1 
 * @param s2 
 * @return char* 
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*ret_addr;

	if (!s1 || !s2)
		return (NULL);
	ret = (char *)ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (NULL);
	ret_addr = ret;
	while (*s1)
		*(ret++) = *(s1++);
	while (*s2)
		*(ret++) = *(s2++);
	return (ret_addr);
}
