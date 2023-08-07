/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:14:03 by avan-and          #+#    #+#             */
/*   Updated: 2023/08/07 22:19:36 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include "btree.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_cll
{
	void			*content;
	struct s_cll	*next;
	struct s_cll	*prev;
}	t_cll;

//
// CHAR FUNCTIONS

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

//
// STRING FUNCTIONS

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstlen);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *str, const char *to_find, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
t_list	*ft_split_to_list(char const *str, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_check_string(char *input, int (*check_func)(int c));

//
// MEM FUNCTIONS

void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);

//
// NUMBER FUNCTIONS

int		ft_atoi(const char *str);
long	ft_atoli(const char *str);
size_t	ft_atosizet(const char *str, int *sign);
char	*ft_itoa(int n);
char	*ft_llitoa(long long int n);
char	*ft_uitoa_base(unsigned long long n, char *base);
char	*ft_llitoa(long long int n);
char	*ft_ftoa(long double n, int precision);
size_t	ft_atou_base(char *str, char *base, char *prefix);
int		ft_pow(int n, int exp);
int		ft_round(float val);
int		ft_abs(int n);
long	ft_labs(long n);
int		ft_max(int a, int b);
int		ft_min(int a, int b);

//
// WRITE FUNCTIONS

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_printf(const char *input, ...);
int		ft_sprintf(char *ret, const char *input, ...);
char	*ft_msprintf(const char *input, ...);
int		ft_dprintf(int fd, const char *input, ...);

//
// LIST FUNCTIONS

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *nw);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *nw);
void	ft_lstadd_middle(t_list *new, t_list *prev, t_list *next);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstdel_item(t_list **head, t_list *to_remove, void (*del)(void *));
t_list	*ft_lst_get_prev(t_list *head, t_list *cur);

//
// FILE FUNCTIONS

char	*get_next_line(int fd);

//
// CIRCULAR LINKED LIST FUNCTONS

void	ft_cll_del(t_cll *head, void (*del)(void *));
void	ft_cll_del_one(t_cll **head, t_cll *to_del);
int		ft_cll_add(t_cll **head, void *content);
int		ft_cll_length(t_cll *list);
void	ft_clliter(t_cll *head, void (*f)(void *));

#endif