/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:38:00 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:38:47 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	trim characters in set from string s1, 
 * 			return newly allocated trimmed string
 * 
 * @param s1 
 * @param set 
 * @return char* 
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ret;

	if (!s1 || !set)
		return (NULL);
	if (!*s1)
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (ft_strchr(set, s1[end - 1]) && end > start)
		end--;
	ret = ft_substr(s1, start, end - start);
	if (!ret)
		return (NULL);
	return (ret);
}
