/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:59:52 by avan-and          #+#    #+#             */
/*   Updated: 2023/07/14 01:21:55 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# define NULL_RETURN "(null)"
# define CHAR_CONV "sc"
# define MODIFIERS "hljztL"
# define DOUBLE_MODIFIERS "hl"
# define CONVERSIONS "cspdiuxXf%"
# define UNSIGNED_CONVERSIONS "uxX"
# define DECIMAL_CONVERSIONS "uid"

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_flags
{
	int		zeroes;
	int		left_adjust;
	int		pound;
	int		plus;
	int		space;
	int		width;
	int		dot;
	int		precision;
	char	type_mod;
	char	type;
}	t_flags;

// PARSE

int		ft_printf(const char *input, ...);
int		ft_sprintf(char *ret, const char *input, ...);
char	*pf_parse(const char *input, va_list *ap, size_t *rlen);
char	*pf_convert(char const *input, va_list *ap, size_t *ilen, size_t *len);

// SET FLAGS

int		set_flags(char const c, t_flags *flags);
void	set_precision_type(char const *input, t_flags *flags, size_t *ilen);

// UTIL

char	*stitch(char *s1, char *s2, size_t *len1, size_t len2);
char	*select_conversion(va_list *ap, t_flags *flags, size_t *slen);
size_t	select_type_mod_int(va_list *ap, t_flags *flags);
char	*submem_and_free(char *raw, size_t start, size_t len, size_t *slen);

// CONVERT

char	*convert_string(va_list *ap, t_flags *flags, size_t *slen);
char	*convert_char(va_list *ap, t_flags *flags, size_t *slen);
char	*convert_hex(va_list *ap, t_flags *flags, size_t *slen);
char	*convert_decimal(va_list *ap, t_flags *flags, size_t *slen);
char	*convert_float(va_list *ap, t_flags *flags, size_t *slen);

// FORMAT

char	*format_width(char *raw, t_flags *flags, size_t *slen);
char	*format_precision(char *raw, t_flags *flags, size_t *slen);
char	*make_spaces(size_t len, char fill_char);

// FORMAT NUMBER

char	*format_sign(char *raw, t_flags *flags, size_t *slen);
char	*format_pound(char *raw, t_flags *flags, size_t *slen);

#endif