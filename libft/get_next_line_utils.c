/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:32:18 by albertvanan       #+#    #+#             */
/*   Updated: 2022/12/25 15:49:19 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief 	join s1 and s2 in newly allocated string
 * 			free s1
 * 
 * @param s1 
 * @param s2 
 * @return char* 
 */
char	*gnl_strjoin(char *s1, char *s2, size_t s1_len, size_t s2_len)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (s2 == NULL)
		return (s1);
	ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (ret == NULL)
		return (free(s1), NULL);
	ret[s1_len + s2_len] = 0;
	while (i < s1_len)
	{
		ret[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
		ret[i++] = *(s2++);
	return (free(s1), ret);
}

/**
 * @brief	return substring from s, starting from start with length len
 * 			allocate proper memory for return value
 * 
 * @param s 
 * @param start 
 * @param len 
 * @return char* 
 */
char	*gnl_substr(char *s, unsigned int start, size_t len, int must_free)
{
	size_t	ret_len;
	size_t	s_len;
	char	*ret;

	if (s == NULL)
		return (NULL);
	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		ret_len = 0;
	else if (s_len - start <= len)
		ret_len = s_len - start;
	else
		ret_len = len;
	ret = (char *)malloc(sizeof(char) * (ret_len + 1));
	if (ret == NULL)
		return (free(s), NULL);
	ret[ret_len] = 0;
	while (ret_len--)
		ret[ret_len] = s[start + ret_len];
	if (must_free)
		free(s);
	return (ret);
}

/**
 * @brief	Initialize struct for [fd], set thread
 * 			and metadata on 0
 * 
 * @param fd 
 * @return t_file* 
 */
t_file	*add_file(t_file **head, int fd)
{
	t_file	*file;
	t_file	*last;

	last = *head;
	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	file->thread = NULL;
	file->len = 0;
	file->last_nl = 0;
	file->next = NULL;
	file->fd = fd;
	if (*head == NULL)
		return (file->prev = NULL, *head = file);
	while (last->next)
		last = last->next;
	return (file->prev = last, last->next = file);
}

/**
 * @brief	return file struct with fd [fd]
 * 
 * @param head 
 * @param fd 
 * @return t_file* 
 */
t_file	*find_file(t_file *head, int fd)
{
	while (head)
	{
		if (head->fd == fd)
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * @brief	delete file struct passed,
 * 			reset head if file struct to be deleted is the head
 * 
 * @param head 
 * @param to_delete 
 */
void	del_file(t_file **head, t_file *to_delete)
{
	if (to_delete == NULL)
		return ;
	if (to_delete == *head)
		*head = (*head)->next;
	if (to_delete->prev)
		to_delete->prev->next = to_delete->next;
	if (to_delete->next)
		to_delete->next->prev = to_delete->next;
	free(to_delete);
}
