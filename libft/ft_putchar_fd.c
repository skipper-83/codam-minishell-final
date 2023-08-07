/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:26:19 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:21:19 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief write character c to filedescriptor fd
 * 
 * @param c 
 * @param fd 
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
