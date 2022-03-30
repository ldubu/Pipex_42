/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:19:10 by ldubuche          #+#    #+#             */
/*   Updated: 2021/11/23 17:11:43 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*__memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*cpdst;
	unsigned char	*cpsrc;

	cpdst = (unsigned char *) dst;
	cpsrc = (unsigned char *) src;
	if (!dst && !src)
		return (NULL);
	if (cpsrc < cpdst)
	{
		while (len--)
			*(cpdst + len) = *(cpsrc + len);
		return (dst);
	}
	while (len--)
		*cpdst++ = *cpsrc++;
	return (dst);
}
