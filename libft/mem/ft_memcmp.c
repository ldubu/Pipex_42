/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:02 by ldubuche          #+#    #+#             */
/*   Updated: 2021/11/23 12:43:48 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	__memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cps1;
	unsigned char	*cps2;

	cps1 = (unsigned char *) s1;
	cps2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (n-- > 0)
	{
		if (*cps1 != *cps2)
			return (*cps1 - *cps2);
		cps1++;
		cps2++;
	}
	return (0);
}
