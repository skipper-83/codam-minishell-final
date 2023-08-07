/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_item.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:53:46 by albertvanan       #+#    #+#             */
/*   Updated: 2023/06/29 23:18:30 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_item(t_list **head, t_list *to_remove, void (*del)(void *))
{
	t_list	*prev;

	prev = *head;
	if (to_remove == *head)
		*head = (*head)->next;
	else
	{
		while (prev->next != to_remove)
		{
			prev = prev->next;
		}
		prev->next = to_remove->next;
	}
	ft_lstdelone(to_remove, del);
}
