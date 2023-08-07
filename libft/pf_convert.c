/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:45:02 by avan-and          #+#    #+#             */
/*   Updated: 2022/10/24 16:45:47 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/**
 * @brief convert argument to string
 * 
 * @param ap argument pointer list
 * @param flags the argument pointer list (ie the args after the input string)
 * @param slen struct with flags set for current conversion
 * @return char* 
 */
char	*convert_string(va_list *ap, t_flags *flags, size_t *slen)
{
	char	*res;
	char	*conv;

	conv = va_arg(*ap, char *);
	if (conv == NULL)
		res = ft_strdup(NULL_RETURN);
	else
		res = ft_strdup(conv);
	if (res == NULL)
		return (NULL);
	*slen = ft_strlen(res);
	if (flags->dot && (size_t)flags->precision < ft_strlen(res))
		res = submem_and_free(res, 0, flags->precision, slen);
	if (res == NULL)
		return (NULL);
	res = format_width(res, flags, slen);
	return (res);
}

/**
 * @brief convert argument to char
 * 
 * @param ap argument pointer list
 * @param flags the argument pointer list (ie the args after the input string)
 * @param slen struct with flags set for current conversion
 * @return char* 
 */
char	*convert_char(va_list *ap, t_flags *flags, size_t *slen)
{
	char	*res;
	char	c;

	c = va_arg(*ap, int);
	res = (char *)malloc(sizeof(char));
	if (res == NULL)
		return (NULL);
	*res = c;
	*slen = 1;
	return (format_width(res, flags, slen));
}

/**
 * @brief convert argument to hex
 * 
 * @param ap argument pointer list
 * @param flags the argument pointer list (ie the args after the input string)
 * @param slen struct with flags set for current conversion
 * @return char* 
 */
char	*convert_hex(va_list *ap, t_flags *flags, size_t *slen)
{
	unsigned long long	number;
	char				*base;
	char				*ret;

	if (flags->type == 'p')
		number = (size_t)va_arg(*ap, void *);
	else
		number = select_type_mod_int(ap, flags);
	base = "0123456789abcdef";
	if (flags->type == 'X')
		base = "0123456789ABCDEF";
	ret = ft_uitoa_base(number, base);
	if (ret == NULL)
		return (NULL);
	*slen = ft_strlen(ret);
	return (format_pound(ret, flags, slen));
}

/**
 * @brief convert argument to dec
 * 
 * @param ap argument pointer list
 * @param flags the argument pointer list (ie the args after the input string)
 * @param slen struct with flags set for current conversion
 * @return char* 
 */
char	*convert_decimal(va_list *ap, t_flags *flags, size_t *slen)
{
	size_t	number;
	char	*res;

	number = select_type_mod_int(ap, flags);
	if (flags->type == 'u')
		res = ft_uitoa_base(number, "0123456789");
	else
	{
		if (flags->type_mod == 'H')
			number = (char)number;
		if (flags->type_mod == 'h')
			number = (short)number;
		res = ft_llitoa(number);
	}
	if (res == NULL)
		return (NULL);
	*slen = ft_strlen(res);
	return (format_sign(res, flags, slen));
}

char	*convert_float(va_list *ap, t_flags *flags, size_t *slen)
{
	long double	number;
	char		*res;

	if (flags->type_mod == 'l' || flags->type_mod == 'L')
		number = va_arg(*ap, long double);
	else
		number = va_arg(*ap, double);
	if (!flags->dot)
		flags->precision = 6;
	res = ft_ftoa(number, flags->precision);
	if (res == NULL)
		return (NULL);
	*slen = ft_strlen(res);
	return (format_sign(res, flags, slen));
}
