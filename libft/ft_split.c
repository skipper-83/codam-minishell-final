/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:44:57 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/25 23:35:35 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copy_word(const char *s1, int len)
{
	char	*ret;
	int		i;

	if (!s1)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i] && i < len)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

static int	add_word_item(t_list **words, const char *str, int start, int len)
{
	t_list	*item;
	char	*word;

	word = copy_word(&str[start], len);
	if (word == NULL)
		return (ft_lstclear(words, free), 0);
	item = ft_lstnew(word);
	if (item == NULL)
		return (free(word), ft_lstclear(words, free), 0);
	ft_lstadd_front(words, item);
	return (1);
}

static int	find_words(const char *str, char c, t_list **words)
{
	int		start;
	int		len;

	start = 0;
	len = 0;
	*words = NULL;
	while (str[start])
	{
		while (str[start] && str[start] == c)
			start++;
		if (str[start])
		{
			len = 0;
			while (str[start + len] && str[start + len] != c)
				len++;
			if (!add_word_item(words, str, start, len))
				return (ft_lstclear(words, free), 0);
			start += len;
		}
	}
	return (1);
}

char	**ft_split(char const *str, char c)
{
	char	**ret;
	t_list	*words;
	t_list	*head;
	int		count;

	if (!find_words(str, c, &words))
		return (NULL);
	count = ft_lstsize(words);
	ret = malloc((count + 1) * sizeof(char *));
	if (ret == NULL)
		return (ft_lstclear(&words, free), NULL);
	ret[count] = 0;
	while (words)
	{
		count--;
		head = words;
		ret[count] = (char *)head->content;
		words = head->next;
		free (head);
	}
	return (ret);
}
