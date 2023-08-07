/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:05:46 by avan-and          #+#    #+#             */
/*   Updated: 2023/05/17 16:21:03 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief 	delete list from node lst on with pointed function del,
			set pointer to lst to NULL
 * 
 * @param lst 
 * @param del 
 */
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*next;

	if (lst == NULL)
		return ;
	cur = *lst;
	while (cur)
	{
		next = cur->next;
		if (del != NULL)
			del (cur->content);
		free (cur);
		cur = next;
	}
	*lst = NULL;
}
