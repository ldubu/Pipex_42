/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:02 by ldubuche          #+#    #+#             */
/*   Updated: 2022/02/14 10:42:08 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	__charnum(unsigned int n, int *i)
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

char	*__itoa(int n)
{
	int				i;
	long long		d;
	int				sign;
	char			*s;
	unsigned int	num;

	i = 0;
	sign = 0;
	if (n < 0 && sign++ >= 0)
		num = -n;
	else
		num = n;
	d = __charnum(num, &i);
	s = (char *) malloc(sizeof(char) * (i + sign + 2));
	if (s == NULL)
		return (s);
	if (sign == 1)
		s[0] = '-';
	while (d > 0)
	{
		s[sign++] = ((num % (d * 10)) / d) + 48;
		d /= 10;
	}
	s[sign] = '\0';
	return (s);
}
