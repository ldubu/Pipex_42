/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:02 by ldubuche          #+#    #+#             */
/*   Updated: 2022/02/14 10:37:33 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n < 0)
	{
		__putchar_fd('-', fd);
		num = -n;
	}
	else
		num = n;
	if (num > 9)
		__putnbr_fd(num / 10, fd);
	__putchar_fd((num % 10 + 48), fd);
}
