/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:49:57 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:25:32 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief 	apply function f to each character of string s,
 * 			passing the index of the character to the function
 * 			and returning a string with the function applied
 * 
 * @param s 
 * @param f 
 * @return char* 
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	size_t	i;

	if (!s)
		return (NULL);
	ret = (char *)ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		ret[i] = f(i, s[i]);
		i++;
	}
	return (ret);
}
