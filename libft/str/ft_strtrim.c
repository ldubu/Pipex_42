/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:02 by ldubuche          #+#    #+#             */
/*   Updated: 2022/02/14 10:37:38 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	__isin(char c, const char *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*__strtrim(char const *s1, char const *set)
{
	char	*new_s;
	int		size;
	int		i;

	i = 0;
	size = __strlen(s1);
	size--;
	while (size > 0 && __isin(s1[size], set))
		size--;
	size++;
	while (*s1 && size > 0 && __isin(*s1++, set))
		size--;
	new_s = (char *) malloc(sizeof(char) * (size + 1));
	if (!new_s)
		return (NULL);
	s1--;
	while (size-- > 0)
		new_s[i++] = *s1++;
	new_s[i] = '\0';
	return (new_s);
}
