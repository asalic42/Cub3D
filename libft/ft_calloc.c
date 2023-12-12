/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:34:54 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/25 19:53:24 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*re;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (__SIZE_MAX__ / nmemb > size)
	{
		re = malloc(nmemb * size);
		if (!re)
			return (NULL);
	}
	else
		return (NULL);
	ft_bzero(re, nmemb * size);
	return (re);
}
