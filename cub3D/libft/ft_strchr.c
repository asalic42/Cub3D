/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:45:13 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/22 17:51:04 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	if (c == '\0')
		return ((char *)(str) + ft_strlen((char *)(str)));
	while (str[i])
	{
		if (str[i] == (unsigned char)(c))
			return ((char *)(str) + i);
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	char s[] = "tripouille";

	printf("%s\n", ft_strchr(s, 'o' + 256));
	printf("%s\n", strchr(s, 'o' + 256));
} */