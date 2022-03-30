/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:02 by ldubuche          #+#    #+#             */
/*   Updated: 2022/02/14 10:37:31 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*__memchr(const void *s, int c, size_t n)
{
	unsigned char	uc;
	unsigned char	*cs;

	uc = (unsigned char) c;
	cs = (unsigned char *) s;
	while (n-- > 0)
	{
		if (*cs == uc)
			return ((void *) cs);
		cs++;
	}
	return (NULL);
}
