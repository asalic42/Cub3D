/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 08:56:17 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/22 17:51:12 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	i;

	i = 0;
	if ((int)(size) < 0)
		size = 2147483647;
	while (src[i] && i < (int)size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	return (ft_strlen((char *)(src)));
}
/* 
int	main(void)
{
	char src[] = "coucou";
	char dest[10]; memset(dest, 'A', 10);
	char src2[] = "coucou";
	char dest2[10]; memset(dest, 'A', 10);
	
	printf("%zu, %zu\n", ft_strlcpy(dest, src, -61), strlcpy(dest2, src2, -61));
	printf("ft_strlcpy : %s\nstrlcpy : %s", dest, dest2);
} */