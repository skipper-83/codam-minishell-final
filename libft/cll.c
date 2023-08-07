/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cll.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:17:00 by albertvanan       #+#    #+#             */
/*   Updated: 2023/04/01 22:35:21 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	delete full stack
 *
 * @param head
 */
void	ft_cll_del(t_cll *head, void (*del)(void *))
{
	t_cll	*work;
	t_cll	*to_delete;

	if (head == NULL)
		return ;
	work = head;
	while (work->next != head)
	{
		to_delete = work;
		work = to_delete->next;
		if (del != NULL)
			del(to_delete->content);
		free(to_delete);
	}
	if (del != NULL)
		del(work->content);
	free(work);
}

/**
 * @brief	delete [to_del] from stack [head]
 * 			if [to_del] is [head], change head to
 * 			next item
 * 			if [to_del] is the only item, set [head]
 * 			to NULL
 *
 * @param head
 * @param to_del
 */
void	ft_cll_del_one(t_cll **head, t_cll *to_del)
{
	if (to_del == *head)
	{
		if (to_del->next == *head)
		{
			free(to_del);
			*head = NULL;
			return ;
		}
		*head = (*head)->next;
	}
	to_del->prev->next = to_del->next;
	to_del->next->prev = to_del->prev;
	free(to_del);
}

/**
 * @brief 	add item to stack [head]
 * 			if [head] is NULL, point prev and next to head
 * 			return 0 on malloc fail
 *
 * @param head
 * @param val
 * @return int
 */
int	ft_cll_add(t_cll **head, void *content)
{
	t_cll	*new;

	new = malloc(sizeof(t_cll));
	if (new == NULL)
		return (0);
	if (*head != NULL)
	{
		new->next = *head;
		new->prev = (*head)->prev;
		(*head)->prev->next = new;
		(*head)->prev = new;
	}
	else
	{
		new->next = new;
		new->prev = new;
	}
	new->content = content;
	*head = new;
	return (1);
}

/**
 * @brief Return the length of a circular linked list
 * 
 * @param list 
 * @return int 
 */
int	ft_cll_length(t_cll *list)
{
	t_cll	*start;
	int		len;

	len = 0;
	if (list == NULL)
		return (len);
	len++;
	start = list;
	list = list->next;
	while (list != start)
	{
		list = list->next;
		len++;
	}
	return (len);
}

/**
 * @brief Iterate over a circular linked list [head]
 * 			and apply function [f] on their content
 * 			member
 * 
 * @param head 
 * @param f 
 */
void	ft_clliter(t_cll *head, void (*f)(void *))
{
	t_cll	*start;

	if (head == NULL)
		return ;
	start = head;
	f(head->content);
	head = head->next;
	while (head != start)
	{
		f(head->content);
		head = head->next;
	}
}
