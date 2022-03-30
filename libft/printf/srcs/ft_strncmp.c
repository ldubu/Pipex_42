/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:27:01 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/13 10:45:19 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (*c2 && *c1 && n > 0)
	{
		if (*c1 != *c2)
		{
			return (*c1 - *c2);
		}
		c1++;
		c2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*c1 - *c2);
}
