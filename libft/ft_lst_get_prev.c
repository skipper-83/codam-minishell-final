/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get_prev.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:27:34 by avan-and          #+#    #+#             */
/*   Updated: 2023/08/07 14:30:04 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_get_prev(t_list *head, t_list *cur)
{
	t_list	*ret;

	ret = head;
	while (ret && ret->next != cur)
		ret = ret->next;
	return (ret);
}
