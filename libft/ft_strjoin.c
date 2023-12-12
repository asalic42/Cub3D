/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:22:59 by rciaze            #+#    #+#             */
/*   Updated: 2022/12/05 11:28:59 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	str = malloc(((ft_strlen((char *)s1))
				+ ft_strlen((char *)s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[i - ft_strlen((char *)s1)])
	{	
		str[i] = s2[-ft_strlen((char *)s1) + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/* 
int	main(void)
{
	char	s[]="premiere chaine", s2[]="deuxieme chaine";

	printf("%s", ft_strjoin(s, s2));
} */