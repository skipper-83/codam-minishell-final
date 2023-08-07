/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:53:11 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 17:10:49 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	return substring from s, starting from start with length len
 * 			allocate proper memory for return value
 * 
 * @param s 
 * @param start 
 * @param len 
 * @return char* 
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	ret_len;
	size_t	s_len;
	char	*ret;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		ret_len = 0;
	else if (s_len - start <= len)
		ret_len = s_len - start;
	else
		ret_len = len;
	ret = (char *)ft_calloc(sizeof(char), ret_len + 1);
	if (ret == NULL)
		return (NULL);
	while (ret_len--)
		ret[ret_len] = s[start + ret_len];
	return (ret);
}
