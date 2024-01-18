/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:29:40 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/25 11:21:44 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((char *)(dest))[i] = ((char *)(src))[i];
		i++;
	}
	return (dest);
}

/* int main()
{
	char d1[] = "Bonjour comment ca va ?", d2[] = "Bonjour comment ca va ?";

	ft_memcpy(&d1[10], &d1, 13);
	memcpy(&d2[10], &d2, 13);
	for ( int i = 0 ; i < 22 ; ++i )
		printf( "%c", d1[i] );
	printf("\n");
	for ( int i = 0 ; i < 22 ; ++i )
		printf( "%c", d2[i] );
	return 0;
}
 */