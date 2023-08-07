/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:37:51 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:20:00 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*free_all(t_list **lst, void *cur_content, void (*del)(void *));

/**
 * @brief 	create new list with function f applied on content of each node of lst
 * 			use function del if malloc fails and new list must be deleted
 * 
 * @param lst 
 * @param f 
 * @param del 
 * @return t_list* 
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*cur;
	void	*cur_content;

	if (!lst || !f || !del)
		return (NULL);
	cur_content = f(lst->content);
	res = ft_lstnew(cur_content);
	if (!res)
		return (free_all(&res, cur_content, del));
	lst = lst->next;
	while (lst)
	{
		cur_content = f(lst->content);
		cur = ft_lstnew(cur_content);
		if (!cur)
			return (free_all(&res, cur_content, del));
		ft_lstadd_back(&res, cur);
		lst = lst->next;
	}
	return (res);
}

/**
 * @brief	free the list being worked on as well
 * 			as the content of the current list item,
 * 			which is not yet part of the list to be
 * 			deleted
 * 
 * @param lst 
 * @param cur_content 
 * @param del 
 * @return t_list* 
 */
static t_list	*free_all(t_list **lst, void *cur_content, void (*del)(void *))
{
	ft_lstclear(lst, del);
	del(cur_content);
	return (NULL);
}
