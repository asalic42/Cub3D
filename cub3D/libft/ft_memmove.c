/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:14:40 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/25 15:02:52 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = n - 1;
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		while ((int) i > -1)
		{
			((char *)(dest))[i] = ((char *)(src))[i];
			i--;
		}
	}
	return (dest);
}

/* int main()
{
	memmove(((void*)0), ((void*)0), 5);
	ft_memmove(((void*)0), ((void*)0), 5);
	return 0;
} */