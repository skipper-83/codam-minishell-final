/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_middle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:01:31 by albertvanan       #+#    #+#             */
/*   Updated: 2023/04/26 14:35:55 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_middle(t_list *new, t_list *prev, t_list *next)
{
	prev->next = new;
	new->next = next;
}
