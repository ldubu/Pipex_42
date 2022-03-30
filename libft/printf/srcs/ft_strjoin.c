/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:46:52 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/04 18:46:52 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/ft_printf.h"

char	*ft_strjoin(char const *s1, char const*s2)
{
	char	*new_s;
	size_t	size;
	int		i;

	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	new_s = (char *) malloc(sizeof(char) * (size + 1));
	if (!new_s)
		return (NULL);
	while (*s1)
		new_s[i++] = *s1++;
	while (*s2)
		new_s[i++] = *s2++;
	new_s[i] = '\0';
	return (new_s);
}
