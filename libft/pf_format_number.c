/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:39:20 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/17 14:40:52 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*add_sign(char *raw, t_flags *flags, size_t *slen, char *signifier);

/**
 * @brief		format the conversion's sign using its width flags
 * 				and the value of the decimal number 
 * 
 * @param raw 	the string to be formatted
 * @param flags	the flags to be applied
 * @param slen	pointer to the legth of the raw string, to be
 *				changed if the formatting changes the length
 * @return char* 
 */
char	*format_sign(char *raw, t_flags *flags, size_t *slen)
{
	char	*signifier;

	signifier = ft_calloc(2, sizeof(char));
	if (signifier == NULL)
		return (free(raw), NULL);
	if (*raw == '-')
	{
		signifier[0] = '-';
		raw = submem_and_free(raw, 1, *slen - 1, slen);
		if (raw == NULL)
			return (free(signifier), NULL);
	}
	else if (flags->plus)
		signifier[0] = '+';
	else if (flags->space)
		signifier[0] = ' ';
	else
	{
		free(signifier);
		return (format_width(format_precision(raw, flags, slen), flags, slen));
	}
	return (add_sign(raw, flags, slen, signifier));
}

/**
 * @brief 	norminette-induced function split, add the sign as
 * 			described by flags
 * 
 * @param raw 
 * @param flags 
 * @param slen 
 * @param signifier 
 * @return char* 
 */
static char	*add_sign(char *raw, t_flags *flags, size_t *slen, char *signifier)
{
	size_t	len;

	len = 1;
	if (flags->zeroes && !flags->dot && signifier[0] && flags->width)
	{
		flags->width--;
		raw = format_width(raw, flags, slen);
	}
	else
		raw = format_precision(raw, flags, slen);
	raw = stitch(signifier, raw, &len, (*slen)++);
	return (format_width(raw, flags, slen));
}

/**
 * @brief add pound character to hex number supplied as string
 * 
 * @param raw 	the string to be formatted
 * @param flags	the flags to be applied
 * @param slen	pointer to the legth of the raw string, to be
 *				changed if the formatting changes the length
 * @return char* 
 */
char	*format_pound(char *raw, t_flags *flags, size_t *slen)
{
	size_t	len;
	char	*prefix;

	if (*raw == '0' && flags->type != 'p')
		return (format_width(format_precision(raw, flags, slen), flags, slen));
	raw = format_precision(raw, flags, slen);
	if (!flags->pound && flags->type != 'p')
		return (format_width(raw, flags, slen));
	if (flags->zeroes)
	{
		flags->width = flags->width - 2;
		if (flags->width < 0)
			flags->width = 0;
		raw = format_width(raw, flags, slen);
	}
	len = 2;
	if (flags->type == 'x' || flags->type == 'p')
		prefix = ft_strdup("0x");
	else
		prefix = ft_strdup ("0X");
	if (prefix == NULL)
		return (free(raw), NULL);
	raw = stitch(prefix, raw, &len, *slen);
	*slen = len;
	return (format_width(raw, flags, slen));
}
