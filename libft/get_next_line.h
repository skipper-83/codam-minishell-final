/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:12:50 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/11 11:56:30 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_file{
	char			*thread;
	int				fd;
	int				len;
	int				last_nl;
	struct s_file	*next;
	struct s_file	*prev;
}	t_file;

// GET NEXT LINE

char	*get_next_line(int fd);
int		find_newline(t_file *file);
char	*return_line(t_file **head, t_file **file, int nl);
char	*read_file(t_file **head, t_file **file, char *buffer);

// UTILS

char	*gnl_strjoin(char *s1, char *s2, size_t s1_len, size_t s2_len);
char	*gnl_substr(char *s, unsigned int start, size_t len, int must_free);
t_file	*add_file(t_file **head, int fd);
t_file	*find_file(t_file *head, int fd);
void	del_file(t_file **head, t_file *to_delete);

#endif