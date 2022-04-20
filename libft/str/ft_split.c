/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:02 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/20 11:12:00 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	__wordnumber(char *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s != c)
			words++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (words);
}

static char	*__free_tab(char **tab, int i)
{
	int	j;

	j = 0;
	while (j <= i)
		free(tab[j++]);
	free(tab);
	return (NULL);
}

static char	*__wordalloc(char *s, char c, char **tab, int i)
{
	char	*word;
	int		num_c;

	num_c = 0;
	while (s[num_c] && s[num_c] != c)
		num_c++;
	word = (char *) malloc(sizeof(char) * num_c + 1);
	if (!word)
	{
		__free_tab(tab, i);
		return (NULL);
	}
	num_c = 0;
	while (*s && *s != c)
		word[num_c++] = *s++;
	word[num_c] = '\0';
	return (word);
}

char	**__split(char *s, char c)
{
	char	**tab;
	int		i;

	i = 0;
	tab = (char **) malloc(sizeof(char *) * (__wordnumber(s, c) + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			tab[i] = __wordalloc(s, c, tab, i);
			if (!tab[i++])
				return (NULL);
		}
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
