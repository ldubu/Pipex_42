/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sign.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:10:06 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/21 12:10:30 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_sign(t_struct *f1, char *str)
{
	if (str[0] == '-')
	{
		ft_putchar('-');
		f1->i = 1;
		if (f1->zero_fla == 1)
			f1->size = f1->size - 1;
		if (f1->pre > 0)
			f1->pre = f1->pre + 1;
		f1->len = f1->len + 1;
	}
	else if (f1->plus_fla)
	{
		ft_putchar('+');
		f1->len = f1->len + 1;
		return (1);
	}
	return (0);
}
