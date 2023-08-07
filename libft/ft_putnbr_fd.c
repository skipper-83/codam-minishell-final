/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:36:29 by avan-and          #+#    #+#             */
/*   Updated: 2022/11/02 11:22:12 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_digit(int n, int fd);

/**
 * @brief write int n to filedescriptor fd
 * 
 * @param n 
 * @param fd 
 */
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	put_digit(n, fd);
}

/**
 * @brief	recursively write all digits of n
 * 			to filedescriptor fd
 * 
 * @param n 
 * @param fd 
 */
static void	put_digit(int n, int fd)
{
	if (n / 10)
		put_digit(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}
