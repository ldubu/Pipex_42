/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:20:24 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/21 12:16:53 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_write_arg(t_struct *f1, char *str)
{
	ft_check_sign_diese(f1, str);
	ft_chara(f1, str);
	if (f1->is_zero == 1)
		f1->is_zero = 2;
	else if (f1->types != 's' && f1->pre >= f1->size)
		ft_write_arg2(f1, str);
	else if (f1->types == 's' && f1->pre < f1->size)
	{
		if (f1->null != 1)
			while ((f1->pre)-- > 0)
				ft_gagner_3_lignes(f1, str);
	}
	else
	{
		while (str[f1->i])
			ft_gagner_3_lignes(f1, str);
	}
	if (str != NULL)
		free(str);
}

void	ft_gagner_3_lignes(t_struct *f1, char *str)
{
	ft_putchar(str[f1->i]);
	f1->i = f1->i + 1;
	f1->len = f1->len + 1;
}

void	ft_chara(t_struct *f1, char *str)
{
	if (f1->types == 'c' && str[0] == 0)
	{
		ft_putchar('\0');
		f1->len = f1->len + 1;
	}
}

void	ft_check_sign_diese(t_struct *f1, char *str)
{
	if (f1->zero_fla == 0 && str != NULL && (f1->types == 'i'
			|| f1->types == 'd'))
		ft_sign(f1, str);
	if (f1->diese_fla && (f1->types == 'x' || f1->types == 'X')
		&& ft_strncmp(str, "0", 2))
	{
		if (f1->types == 'x')
			ft_putstr(("0x"));
		else
			ft_putstr("0X");
		f1->len = f1->len + 2;
	}
}

void	ft_write_arg2(t_struct *f1, char *str)
{
	while ((f1->pre)-- > f1->size)
	{
		ft_putchar('0');
		f1->len = f1->len + 1;
	}
	while (str[f1->i])
		ft_gagner_3_lignes(f1, str);
}
