/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:03:25 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/25 15:00:11 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	destsize;
	size_t	return_value;

	destsize = 0;
	if (!size)
		return (ft_strlen((char *)(src)));
	while (destsize < size && dst[destsize])
		destsize++;
	return_value = destsize + ft_strlen((char *)(src));
	i = destsize;
	while (destsize + 1 < size && src[destsize - i])
	{
		dst[destsize] = src[destsize - i];
		destsize++;
	}
	if (i < size)
		dst[destsize] = '\0';
	return (return_value);
}
