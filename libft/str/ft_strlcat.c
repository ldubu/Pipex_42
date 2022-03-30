/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:24:17 by ldubuche          #+#    #+#             */
/*   Updated: 2021/11/23 17:40:14 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	__strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s;
	size_t	d;
	size_t	i;

	s = 0;
	d = 0;
	i = 0;
	while (src[s])
		s++;
	while (dst[d])
		d++;
	if (d < dstsize)
	{
		while (src[i] && i < dstsize - d - 1)
		{
			dst[d + i] = src[i];
			i++;
		}
		dst[d + i] = '\0';
		return (d + s);
	}
	return (dstsize + s);
}
