/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:18:44 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/14 01:23:06 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/**
 * @brief	As dprintf, but homebrewn. 
 * 			Writes input string with all parameters passed
 * 			(Width, precision, #- 0 work as do l, ll h, hh and z)
 * 			Return length of the string written
 * 
 * @param input 
 * @param ... 
 * @return int 
 */
int	ft_dprintf(int fd, const char *input, ...)
{
	va_list	ap;
	char	*res;
	size_t	rlen;

	va_start(ap, input);
	rlen = 0;
	res = pf_parse(input, &ap, &rlen);
	va_end(ap);
	if (res == NULL)
		return (-1);
	rlen = write(fd, res, rlen);
	free(res);
	return (rlen);
}
