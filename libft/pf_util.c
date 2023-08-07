/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 23:44:20 by avan-and          #+#    #+#             */
/*   Updated: 2023/04/27 21:25:55 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/**
 * @brief 		add s1 and s2 together in newly allocated string
 * 				free s1 and s2
 * 				store length of new string in len1, which was passed
 * 				as a pointer
 * 
 * @param s1 
 * @param s2 
 * @param len1 
 * @param len2 
 * @return char* 
 */
char	*stitch(char *s1, char *s2, size_t *len1, size_t len2)
{
	char	*res;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (free(s1), free(s2), NULL);
	res = (char *)malloc(sizeof(char) * (*len1 + len2));
	if (res == NULL)
		return (free(s1), free(s2), NULL);
	ft_memcpy(res, s1, *len1);
	ft_memcpy(&res[*len1], s2, len2);
	(*len1) += len2;
	return (free(s1), free(s2), res);
}

/**
 * @brief Branch to the conversion to the correct handler function
 * 
 * @param ap the argument pointer list (ie the args after the input string)
 * @param flags struct with flags set for current conversion
 * @param slen sublength counter passed as pointer so length of return 
 * 				string is known
 * @return char* conversion with flags applied as string
 */
char	*select_conversion(va_list *ap, t_flags *flags, size_t *slen)
{
	if (flags->width == -1)
		flags->width = va_arg(*ap, int);
	if (flags->precision == -1)
		flags->precision = va_arg(*ap, int);
	if (flags->type == 's')
		return (convert_string(ap, flags, slen));
	if (flags->type == 'c')
		return (convert_char(ap, flags, slen));
	if (flags->type == 'x' || flags->type == 'X' || flags->type == 'p')
		return (convert_hex(ap, flags, slen));
	if (flags->type == 'f')
		return (convert_float(ap, flags, slen));
	if (ft_strchr(DECIMAL_CONVERSIONS, flags->type))
		return (convert_decimal(ap, flags, slen));
	if (flags->type == '%')
	{
		*slen = 1;
		return (format_width(ft_strdup("%"), flags, slen));
	}
	return (NULL);
}

/**
 * @brief	cast input number into the correct width
 * 			as specified by flags
 * 
 * @param ap 
 * @param flags 
 * @return unsigned long long 
 */
size_t	select_type_mod_int(va_list *ap, t_flags *flags)
{
	int	h;

	if (flags->type_mod == 'l' || flags->type_mod == 'L')
		return ((size_t)va_arg(*ap, long unsigned int));
	if (flags->type_mod == 'L')
		return ((size_t)va_arg(*ap, long long unsigned int));
	if (flags->type_mod == 'h')
	{
		h = (short)va_arg(*ap, int) & 0x0000ffff;
		return ((size_t)h);
	}
	if (flags->type_mod == 'H')
	{
		h = va_arg(*ap, int) & 0x000000ff;
		return ((size_t)h);
	}
	if (flags->type_mod == 'z')
		return ((size_t)va_arg(*ap, size_t));
	else if (ft_strchr(UNSIGNED_CONVERSIONS, flags->type))
		return ((size_t)va_arg(*ap, unsigned int));
	else
		return (va_arg(*ap, int));
}

/**
 * @brief	return subset of car *raw of length len, starting froms start
 * 			do not add null terminator
 * 
 * @param raw 
 * @param start 
 * @param len 
 * @param slen 
 * @return char* 
 */
char	*submem_and_free(char *raw, size_t start, size_t len, size_t *slen)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * len);
	if (res == NULL)
		*slen = 0;
	else
	{
		ft_memcpy(res, &raw[start], len);
		*slen = len;
	}
	free (raw);
	return (res);
}
