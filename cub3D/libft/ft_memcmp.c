/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:32:35 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/25 11:27:38 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1c;
	unsigned char	*s2c;

	i = 0;
	s1c = (unsigned char *)(s1);
	s2c = (unsigned char *)(s2);
	while (i < n && s1c[i] == s2c[i])
		i++;
	if (i >= n)
		return (0);
	if (s1c[i] > s2c[i] && i < n)
		return (1);
	return (-1);
}
