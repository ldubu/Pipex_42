/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:49:38 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/05 10:49:38 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_strrchr(const char *s, int c)
{
	char	a;
	int		b;

	a = (char)c;
	b = 0;
	while (s[b])
		b++;
	if (a == '\0')
		return ((char *)s + b);
	while (--b >= 0)
	{
		if (*s == a)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
