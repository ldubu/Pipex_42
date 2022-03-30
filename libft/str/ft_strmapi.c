/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:02 by ldubuche          #+#    #+#             */
/*   Updated: 2022/02/14 10:37:37 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*__strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*scpy;
	int		size;
	int		i;

	i = 0;
	size = __strlen(s);
	scpy = (char *) malloc(sizeof(char) * (size +1));
	if (!scpy)
		return (NULL);
	while (s[i])
	{
		scpy[i] = f(i, s[i]);
		i++;
	}
	scpy[i] = '\0';
	return (scpy);
}
