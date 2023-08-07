/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:12:42 by albertvanan       #+#    #+#             */
/*   Updated: 2022/12/25 15:49:15 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief	Read next line from file descriptor
 * 			until newline or EOF
 * 
 * @param fd 
 * @return char* 
 */
char	*get_next_line(int fd)
{
	char			*buffer;
	static t_file	*head;
	t_file			*file;
	char			*ret;

	file = find_file(head, fd);
	if (file == NULL)
		file = add_file(&head, fd);
	if (file == NULL)
		return (NULL);
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (buffer == NULL)
		return (free(file->thread), del_file(&head, file), file = NULL, NULL);
	if (file->thread)
	{
		if (find_newline(file) >= 0)
			return (free(buffer), return_line(&head, &file, file->last_nl));
	}
	ret = read_file(&head, &file, buffer);
	if (ret == NULL)
		return (del_file(&head, file), file = NULL, ret);
	return (ret);
}

/**
 * @brief 	Return position of next newline, set file->last_nl
 * 			to that position to avoid going over the same substring
 * 			twice
 * 
 * @param file 
 * @return int 
 */
int	find_newline(t_file *file)
{
	while (file->thread[file->last_nl])
	{
		if (file->thread[file->last_nl] == '\n')
			return (file->last_nl);
		++(file->last_nl);
	}
	return (-1);
}

/**
 * @brief Return a single line
 * 
 * @param file 
 * @param nl 
 * @return char* 
 */
char	*return_line(t_file **head, t_file **file, int nl)
{
	char	*ret;

	ret = gnl_substr((*file)->thread, 0, nl + 1, 0);
	if (ret == NULL)
		return (del_file(head, *file), *file = NULL, NULL);
	(*file)->thread = gnl_substr((*file)->thread, nl + 1, (*file)->len - nl, 1);
	if ((*file)->thread == NULL)
		return (del_file(head, *file), *file = NULL, free(ret), NULL);
	(*file)->len = (*file)->len - (nl + 1);
	(*file)->last_nl = 0;
	return (ret);
}

/**
 * @brief	Read from fd until newline is encountered in buffer
 * 			return first full line. If eof is reached, return last
 * 			bit of the file even if there is no newline anymore
 * 
 * @param f 
 * @param buf 
 * @return char* 
 */
char	*read_file(t_file **head, t_file **f, char *buf)
{
	int		read_res;
	char	*ret;

	read_res = read((*f)->fd, buf, BUFFER_SIZE);
	while (read_res > 0)
	{
		(*f)->thread = gnl_strjoin((*f)->thread, buf, (*f)->len, read_res);
		if ((*f)->thread == NULL)
			return (free(buf), NULL);
		(*f)->len += read_res;
		if (find_newline(*f) >= 0)
			return (free(buf), return_line(head, f, (*f)->last_nl));
		read_res = read((*f)->fd, buf, BUFFER_SIZE);
	}
	if (read_res < 0)
		return (free((*f)->thread), free(buf), NULL);
	if ((*f)->thread && (*f)->len > 0)
	{
		ret = gnl_substr((*f)->thread, 0, (*f)->len, 1);
		return (free(buf), (*f)->thread = NULL, ret);
	}
	return (free((*f)->thread), free(buf), NULL);
}
