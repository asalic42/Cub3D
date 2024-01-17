/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:21:29 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/22 15:34:44 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rlst;
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = ft_lstnew((*f)(lst->content));
	if (!temp)
		return (NULL);
	rlst = temp;
	lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&temp, ft_lstnew((*f)(lst->content)));
		if (!temp->next)
		{
			ft_lstclear(&rlst, del);
			return (NULL);
		}
		temp = temp->next;
		lst = lst->next;
	}
	return (rlst);
}
