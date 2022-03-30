/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:20:54 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/17 14:27:39 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*__strrchr(const char *s, int c)
{
	char	a;
	int		b;

	a = (char) c;
	b = 0;
	while (s[b])
		b++;
	if (a == '\0')
		return ((char *) s + b);
	while (--b >= 0)
	{
		if (*s == a)
			return ((char *) s);
		s++;
	}
	return (NULL);
}
