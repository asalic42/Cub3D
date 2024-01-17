/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:39:45 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/22 17:51:19 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;
	int	boolean;
	int	mem;

	boolean = 0;
	i = 0;
	if (c == '\0')
		return ((char *)(str) + ft_strlen((char *)(str)));
	while (str[i])
	{
		if (str[i] == (unsigned char)(c))
		{
			boolean = 1;
			mem = i;
		}
		i++;
	}
	if (boolean)
		return ((char *)(str) + mem);
	return (NULL);
}

/* int	main(void)
{
	char s[] = "tripouille";

	printf("%s\n", ft_strrchr(s, 'o' + 256));
	printf("%s\n", strrchr(s, 'o' + 256));
} */