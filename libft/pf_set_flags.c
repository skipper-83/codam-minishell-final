/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_set_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:30:28 by avan-and          #+#    #+#             */
/*   Updated: 2023/02/25 23:35:53 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/**
 * @brief	set flags in the flags struct according to the 
 * 			character passed. Return 1 of the passed character
 * 			is a flag, 0 if it isn't
 * 
 * @param c 
 * @param flags 
 * @return int 
 */
int	set_flags(char const c, t_flags *flags)
{
	if (c == '0')
		return (flags->zeroes = 1);
	if (c == '-')
		return (flags->left_adjust = 1);
	if (c == '#')
		return (flags->pound = 1);
	if (c == '+')
		return (flags->plus = 1);
	if (c == ' ')
		return (flags->space = 1);
	return (0);
}

/**
 * @brief	set the type and type modifiers of the conversion
 * 
 * @param input 
 * @param flags 
 * @param ilen 
 */
void	set_type(char const *input, t_flags *flags, size_t *ilen)
{
	while (input[*ilen] && ft_strchr(MODIFIERS, (input[*ilen])))
		flags->type_mod = input[(*ilen)++];
	if (ft_strchr(DOUBLE_MODIFIERS, input[*ilen - 1]))
	{
		if (input[*ilen - 2] == flags->type_mod)
			flags->type_mod = ft_toupper(flags->type_mod);
	}
	if (ft_strchr(CONVERSIONS, input[*ilen]))
		flags->type = input[(*ilen)];
}

/**
 * @brief Set the precision of the conversion
 * 
 * @param input 
 * @param flags 
 * @param ilen 
 */
void	set_precision_type(char const *input, t_flags *flags, size_t *ilen)
{
	if (input[*ilen] == '.')
	{
		flags->dot = 1;
		++(*ilen);
		if (ft_isdigit(input[*ilen]))
			flags->precision = ft_atoi(&input[*ilen]);
		while (ft_isdigit(input[*ilen]))
			++(*ilen);
		if (input[*ilen] == '*')
		{
			flags->precision = -1;
			++*(ilen);
		}
	}
	set_type(input, flags, ilen);
}
