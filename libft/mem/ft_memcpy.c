/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:14:16 by ldubuche          #+#    #+#             */
/*   Updated: 2021/11/23 16:55:25 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*__memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cpdst;
	unsigned char	*cpsrc;

	cpdst = (unsigned char *)dst;
	cpsrc = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	while (n-- > 0)
	{
		*cpdst++ = *cpsrc++;
	}
	return (dst);
}
