/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:48:28 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/04 11:48:28 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/ft_printf.h"

void	ft_putargs(t_struct *f1, char *str)
{
	int	space_nbr;

	if (f1->space_fla == 1 && f1->width == 0 && f1->types != 's'
		&& str[0] != '-')
	{	
		ft_putchar(' ');
		f1->len = f1->len + 1;
	}
	space_nbr = ft_space_nbr(f1, str);
	if (f1->minus_fla == 1)
	{
		ft_write_arg(f1, str);
		ft_putspace(f1, space_nbr);
	}
	else if (f1->zero_fla == 1 && f1->pre == -1)
	{
		ft_putzero(f1, space_nbr - ft_sign(f1, str));
		ft_write_arg(f1, str);
	}
	else
	{
		f1->zero_fla = 0;
		ft_putspace(f1, space_nbr);
		ft_write_arg(f1, str);
	}
}

void	ft_putspace(t_struct *f1, int n)
{
	while (n-- > 0)
	{
		ft_putchar(' ');
		f1->len = f1->len + 1;
	}
}

int	ft_space_nbr(t_struct *f1, char *str)
{
	int	n;

	n = 0;
	if (f1->width != 0 || f1->pre != f1->size)
		n = ft_spc_nbr2(f1, n);
	if (f1->diese_fla == 1)
		n = n - 2;
	if (str[0] == '-' && f1->types != 's' && f1->pre >= f1->size)
		n = n - 1;
	if (f1->is_zero == 1 && f1->width > 0)
		n = n + 1;
	if (f1->types == 'c' && f1->width != 0 && str[0] == 0)
		n = n - 1;
	return (n);
}

void	ft_putzero(t_struct *f1, int n)
{
	while (n-- > 0)
	{
		ft_putchar('0');
		f1->len = f1->len + 1;
	}
}

int	ft_spc_nbr2(t_struct *f1, int n)
{
	if (f1->width >= f1->pre || f1->types == 's')
	{
		if ((f1->size < f1->pre && f1->types != 's') || (f1->size > f1->pre
				&& f1->types == 's'))
			n = f1->width - f1->pre;
		else if ((f1->size >= f1->pre) || (f1->size < f1->pre
				&& f1->types == 's'))
			n = f1->width - f1->size ;
	}
	else if (f1->types == 's' && f1->size > f1->width
		&& f1->width > f1->pre)
		n = f1->width - f1->pre;
	return (n);
}
