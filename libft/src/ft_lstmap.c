/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:09:09 by deladia           #+#    #+#             */
/*   Updated: 2019/04/14 17:31:18 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlst;
	t_list	*tmp;
	t_list	*begin;

	tmp = f(lst);
	newlst = ft_lstnew(tmp->content, tmp->content_size);
	begin = newlst;
	lst = lst->next;
	while (lst)
	{
		tmp = f(lst);
		newlst->next = ft_lstnew(tmp->content, tmp->content_size);
		lst = lst->next;
		newlst = newlst->next;
	}
	return (begin);
}
