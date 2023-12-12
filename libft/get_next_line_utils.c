/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:38:34 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/12 20:01:18 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	int i;
	int j;
	char		 *str;
	int			 len2;

	len2 = ft_strlen(s);
	if (!s)
		return (NULL);
	if (len == 0 || (size_t)start > (size_t)len2)
		return (free((void *)s), NULL);
	if (len > len2 - start)
		len = len2 - start;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (i - start < len && s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	return (free((void *)s), str);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		len;

	len = ft_strlen(s1);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	str = malloc(((len) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[i - len])
	{	
		str[i] = s2[-len + i];
		i++;
	}
	str[i] = '\0';
	return (free(s1), free(s2), str);
}

char	*ft_strdup_gnl(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

