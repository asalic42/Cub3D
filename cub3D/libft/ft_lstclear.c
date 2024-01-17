/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:18:32 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/22 17:51:46 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*d_list;
	int		i;

	if (lst == NULL)
		return ;
	i = ft_lstsize(*lst);
	d_list = *(lst);
	while (i-- > 0)
	{
		(*del)(d_list->content);
		temp = d_list->next;
		free(d_list);
		d_list = temp;
	}
	*lst = NULL;
}
