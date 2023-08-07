/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:28:18 by avan-and          #+#    #+#             */
/*   Updated: 2022/10/20 11:31:49 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief make new list and assign *content to its content pointer
 * 
 * @param content 
 * @return t_list* 
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*ret;

	ret = (t_list *)malloc(sizeof(t_list));
	if (!ret)
		return (NULL);
	ret->content = content;
	ret->next = NULL;
	return (ret);
}
