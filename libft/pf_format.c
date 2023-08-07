/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:46:32 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/17 14:41:51 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*add_spaces(char *raw, t_flags *flags, size_t *slen, size_t len);

/**
 * @brief format the conversion's width using its width flags
 * 
 * @param raw 	the string to be formatted
 * @param flags	the flags to be applied
 * @param slen	pointer to the legth of the raw string, to be
 *				changed if the formatting changes the length
 * @return char* 
 */
char	*format_width(char *raw, t_flags *flags, size_t *slen)
{
	size_t	len;

	if (raw == NULL)
		return (NULL);
	if (!flags->width)
		return (raw);
	if ((size_t)flags->width <= *slen)
		return (raw);
	len = flags->width - *slen;
	return (add_spaces(raw, flags, slen, len));
}

/**
 * @brief 	norminette-induced function split, add the spaces/zeroes as 
 * 			described in flags
 * 
 * @param raw 
 * @param flags 
 * @param slen 
 * @param len 
 * @return char* 
 */
static char	*add_spaces(char *raw, t_flags *flags, size_t *slen, size_t len)
{
	char	fill_char;
	char	*spaces;

	if (flags->left_adjust)
	{
		spaces = make_spaces(len, ' ');
		if (spaces == NULL)
			return (free (raw), NULL);
		raw = stitch(raw, spaces, slen, len);
		return (raw);
	}
	if (flags->zeroes && !ft_strchr(CHAR_CONV, (flags->type)))
		fill_char = '0';
	else
		fill_char = ' ';
	spaces = make_spaces(len, fill_char);
	if (spaces == NULL)
		return (free(raw), NULL);
	raw = stitch(spaces, raw, &len, *slen);
	(*slen) = len;
	return (raw);
}

/**
 * @brief format the conversion's precision using its width flags
 * 
 s* @param raw 	the string to be formatted
 * @param flags	the flags to be applied
 * @param slen	pointer to the legth of the raw string, to be
 *				changed if the formatting changes the length
 * @return char* 
 */

char	*format_precision(char *raw, t_flags *flags, size_t *slen)
{
	size_t	len;
	char	*res;
	char	*spaces;

	if (!flags->dot)
		return (raw);
	flags->zeroes = 0;
	if (*raw == '0' && !flags->precision)
	{
		*slen = 0;
		return (free(raw), ft_strdup(""));
	}
	if ((size_t)flags->precision <= *slen)
		return (raw);
	len = flags->precision - *slen;
	spaces = make_spaces(len, '0');
	if (spaces == NULL)
		return (free(raw), NULL);
	res = stitch(spaces, raw, &len, *slen);
	*slen = len;
	return (res);
}

/**
 * @brief create string with len amount of fill_chars
 * 
 * @param len the length of the return string
 * @param fill_char the character to be used
 * @return char* 
 */
char	*make_spaces(size_t len, char fill_char)
{
	char	*res;

	if (len == 0)
		res = ft_strdup("");
	else
		res = ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	res = ft_memset(res, fill_char, len);
	return (res);
}
