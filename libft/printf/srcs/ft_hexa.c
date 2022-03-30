/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:03:45 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/04 18:03:45 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/ft_printf.h"

char	*ft_hexa(unsigned int n)
{
	char	*hexa;
	char	*str;
	char	*temp;
	char	*temp2;

	temp2 = NULL;
	hexa = "0123456789abcdef";
	if (n / 16 == 0)
	{
		str = ft_c_to_str(hexa[n]);
		if (!str)
			return (NULL);
		return (str);
	}
	temp = ft_hexa(n / 16);
	if (!temp)
		return (ft_freestr(temp, temp2));
	temp2 = ft_c_to_str(hexa[n % 16]);
	if (!temp2)
		return (ft_freestr(temp, temp2));
	str = ft_strjoin(temp, temp2);
	if (!str)
		return (NULL);
	ft_freestr(temp, temp2);
	return (str);
}
