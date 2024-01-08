/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:34:54 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/19 14:22:35 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*re;

	if (nmemb == 0 || size == 0)
		return (ft_malloc(0));
	if (__SIZE_MAX__ / nmemb > size)
	{
		re = ft_malloc(nmemb * size);
		if (!re)
			return (NULL);
	}
	else
		return (NULL);
	ft_bzero(re, nmemb * size);
	return (re);
}
