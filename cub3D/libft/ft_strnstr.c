/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:48:16 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/25 15:12:14 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *big, char const *little, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!*little)
		return ((char *)(big));
	while (i < len && (big[i]))
	{
		j = 0;
		while (big[i + j] && little[j] == big[i + j] && i + j < len)
		{
			j++;
			if (!little[j])
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	char big[30] = "aaabcabcd";
	char little[10] = "aabc";

	printf("%s\n", ft_strnstr(big, "a", -1));
	printf("%s\n\n", strnstr(big, "a", -1));
	printf("%s\n", ft_strnstr(big, little, -1));
	printf("%s\n\n", strnstr(big, little, -1));
	printf("%s\n", ft_strnstr(big, "aaabc", 5));
	printf("%s\n\n", strnstr(big, "aaabc", 5));
	printf("%s\n", ft_strnstr("aaaab", "aaab", 5));
	printf("%s\n", strnstr("aaaab", "aaab", 5));
} */