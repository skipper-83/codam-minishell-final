/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:59:35 by avan-and          #+#    #+#             */
/*   Updated: 2023/06/29 23:18:30 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief delete the content of one item from list using pointed function del
 * 
 * @param lst 
 * @param del 
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	if (del != NULL)
		del(lst->content);
	lst->content = NULL;
	free(lst);
}
