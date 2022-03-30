/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:29:28 by ldubuche          #+#    #+#             */
/*   Updated: 2022/02/16 10:39:51 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__putnbr(int n)
{
	unsigned int	num;

	if (n < 0)
	{
		__putchar('-');
		num = -n;
	}
	else
		num = n;
	if (num > 9)
		__putnbr(num / 10);
	__putchar((num % 10 + 48));
}
