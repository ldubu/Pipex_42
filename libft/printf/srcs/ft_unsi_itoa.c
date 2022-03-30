/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsi_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:56:51 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/04 17:56:51 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/ft_printf.h"

static long long	ft_charnum(unsigned int n, int *i)
{
	long long	d;

	d = 1;
	while (n / d > 9)
	{
		*i = *i + 1;
		d *= 10;
	}
	return (d);
}

char	*ft_unsi_itoa(unsigned int n)
{
	int				i;
	long long		d;
	char			*s;

	i = 0;
	d = ft_charnum(n, &i);
	s = (char *) malloc(sizeof(char) * (i + 2));
	if (s == NULL)
		return (s);
	i = 0;
	while (d > 0)
	{
		s[i++] = ((n % (d * 10)) / d) + 48;
		d /= 10;
	}
	s[i] = '\0';
	return (s);
}
