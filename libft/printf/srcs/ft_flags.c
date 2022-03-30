/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:02:30 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/04 11:02:30 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_flags(va_list ptr, const char **str, int len)
{
	char		types;
	t_struct	f1;

	if (**str == '%')
	{
		ft_putchar('%');
		(*str)++;
		return (++len);
	}
	ft_ini_struct(&f1);
	ft_symbols(&f1, str);
	ft_width_precision(&f1, str);
	types = *(ft_strrchr("cspdiuxX", **str));
	if (types)
	{
		f1.types = types;
		(*str)++;
	}
	f1.len = len;
	ft_args_to_str(&f1, ptr);
	len = f1.len;
	return (len);
}

void	ft_symbols(t_struct *f1, const char **str)
{
	while (ft_strrchr("-+0# ", **str) != NULL)
	{
		if (**str == '-')
			f1->minus_fla = 1;
		else if (**str == '+')
			f1->plus_fla = 1;
		else if (**str == ' ')
			f1->space_fla = 1;
		else if (**str == '0')
			f1->zero_fla = 1;
		else if (**str == '#')
			f1->diese_fla = 1;
		(*str)++;
	}
}

void	ft_width_precision(t_struct *f1, const char **str)
{
	while (ft_strrchr("0123456789", **str) != NULL)
	{
		f1->width = f1->width * 10 + **str - '0';
		(*str)++;
	}
	if (**str == '.')
	{
		f1->pre = 0;
		(*str)++;
		while (ft_strrchr("0123456789", **str) != NULL)
		{
			f1->pre = f1->pre * 10 + **str - '0';
			(*str)++;
		}
	}
}

void	ft_args_to_str(t_struct *f1, va_list ptr)
{
	char	*str_args;

	str_args = NULL;
	if (f1->types == 'c')
		str_args = ft_c_to_str(va_arg(ptr, int));
	else if (f1->types == 's')
		str_args = ft_str_ptr(1, va_arg(ptr, char *), f1);
	else if (f1->types == 'p')
		str_args = ft_str_ptr(2, ft_address(va_arg(ptr, unsigned long)), f1);
	else if (f1->types == 'd' || f1->types == 'i')
		str_args = ft_pre(ft_itoa(va_arg(ptr, int)), f1);
	else if (f1->types == 'u')
		str_args = ft_pre(ft_unsi_itoa(va_arg(ptr, unsigned int)), f1);
	else if (f1->types == 'x')
		str_args = ft_pre(ft_hexa(va_arg(ptr, unsigned int)), f1);
	else if (f1->types == 'X')
		str_args = ft_toupper(ft_pre(ft_hexa(va_arg(ptr, unsigned int)), f1));
	if (str_args != NULL)
		f1->size = ft_strlen(str_args);
	if (f1->types == 's' && f1->pre == -1)
		f1->pre = f1->size;
	f1->len = f1->len;
	ft_putargs(f1, str_args);
}

char	*ft_str_ptr(int type, char *str, t_struct *f1)
{
	int	strlen;

	if (type == 1)
	{
		if (str != NULL)
			str = ft_strcpy(str, ft_strlen(str));
		else
		{
			str = ft_strcpy("(null)", 7);
			f1->null = 1;
		}
	}
	else if (type == 2)
	{
		strlen = ft_strncmp("0x0", str, 4);
		if (strlen == 0)
		{
			free(str);
			str = ft_strcpy(OS_NULL, 6);
		}
	}
	return (str);
}
