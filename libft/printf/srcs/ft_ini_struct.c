/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:52:26 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/17 09:51:21 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_ini_struct(t_struct *f1)
{
	f1->minus_fla = 0;
	f1->plus_fla = 0;
	f1->space_fla = 0;
	f1->diese_fla = 0;
	f1->zero_fla = 0;
	f1->width = 0;
	f1->pre = -1;
	f1->types = '0';
	f1->size = 0;
	f1->len = 0;
	f1->i = 0;
	f1->null = 0;
	f1->is_zero = 0;
}
