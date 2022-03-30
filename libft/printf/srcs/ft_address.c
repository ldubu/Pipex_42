/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_address.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:01:28 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/11 17:21:32 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_address(unsigned long n)
{
	char	*hexa;
	char	*str;
	char	*temp;
	char	*temp2;

	temp2 = NULL;
	hexa = "0123456789abcdef";
	if (n / 16 == 0)
	{
		str = ft_ini_strjoin("0x", hexa[n]);
		if (!str)
			return (NULL);
		return (str);
	}
	temp = ft_address(n / 16);
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

char	*ft_freestr(char *temp, char *temp2)
{
	if (temp)
		free(temp);
	if (temp2)
		free(temp2);
	return (NULL);
}

char	*ft_ini_strjoin(char *s, char c)
{
	char	*temp;
	char	*str;

	temp = ft_c_to_str(c);
	str = ft_strjoin(s, temp);
	free(temp);
	return (str);
}
