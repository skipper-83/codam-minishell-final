/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:14:41 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:24:16 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief copy s1 into newly allocated string
 * 
 * @param s1 
 * @return char* 
 */
char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	i;

	if (!s1)
		return (NULL);
	ret = (char *)ft_calloc(sizeof(char), (ft_strlen (s1) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	return (ret);
}
