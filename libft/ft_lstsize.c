/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:43:47 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:20:18 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief return size of lst
 * 
 * @param lst 
 * @return int 
 */
int	ft_lstsize(t_list *lst)
{
	int	ret;

	if (!lst)
		return (0);
	ret = 1;
	while (lst->next)
	{
		lst = lst->next;
		ret++;
	}
	return (ret);
}
