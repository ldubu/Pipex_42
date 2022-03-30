/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:00:34 by ldubuche          #+#    #+#             */
/*   Updated: 2022/02/08 13:00:34 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*__lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*__lstnew(void *content);
t_list	*__lstlast(t_list *lst);

int		__lstsize(t_list *lst);

void	__lstdelone(t_list *lst, void (*del)(void *));
void	__lstclear(t_list **lst, void (*del)(void *));
void	__lstadd_front(t_list	**alst, t_list *new);
void	__lstiter(t_list *lst, void (*f)(void *));
void	__lstadd_back(t_list **alst, t_list *new);

#endif