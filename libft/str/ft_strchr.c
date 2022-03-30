/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:58:41 by ldubuche          #+#    #+#             */
/*   Updated: 2021/11/23 18:20:40 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*__strchr(const char *s, int c)
{
	char	a;
	char	*b;

	a = (char)c;
	b = (char *)s;
	while (*b)
	{
		if (a == *b)
			return (b);
		b++;
	}
	if (a == '\0')
		return (b);
	return (NULL);
}
