/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:02 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/17 14:22:56 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*__lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_l;
	t_list	*first;

	new_l = __lstnew(f(lst->content));
	if (!new_l)
		return (NULL);
	first = new_l;
	lst = lst->next;
	while (lst)
	{
		new_l->next = __lstnew(f(lst->content));
		if (!new_l)
		{
			__lstclear(&first, del);
			return (NULL);
		}
		new_l = new_l->next;
		lst = lst->next;
	}
	return (first);
}
