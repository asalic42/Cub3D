/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:10:07 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/22 17:51:51 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*temp;

	temp = (unsigned char *)(s);
	i = 0;
	while (i < (int)(n))
	{
		if (temp[i] == (unsigned char)(c))
			return (temp + i);
		i++;
	}
	return (NULL);
}
