/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:42:01 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/22 17:51:43 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	c;

	c = '\0';
	i = 0;
	if (!s)
		return ;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
}

/* int	main(void)
{
	char t[] = "test test";
	printf("%s%c", t, '\n');
	ft_bzero(t, 3);
	printf( t);
	return 0;
} */
