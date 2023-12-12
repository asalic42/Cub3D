/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:59:40 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/22 17:51:01 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	how_many_words(char const *s, char c)
{
	int	i;
	int	words_count;

	words_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
			i++;
		if (s[i - 1] != c)
			words_count++;
	}
	return (words_count);
}

void	free_all(char **str, int wordc)
{
	int	i;

	i = 0;
	while (i <= wordc)
		free(str[i]);
	free(str);
}

char	**attribution(char const *s, char c, char **str, int wordc)
{
	int	i;
	int	start;
	int	len;
	int	j;

	j = 0;
	i = 0;
	while (j < wordc)
	{
		len = 0;
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i++])
			len++;
		str[j] = ft_substr(s, start, len);
		if (!str[j])
		{
			free_all(str, wordc);
			return (NULL);
		}
		j++;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**fs;
	int		wordc;

	wordc = how_many_words(s, c);
	fs = malloc((how_many_words(s, c) + 1) * sizeof(char *));
	if (!fs)
		return (NULL);
	return (attribution(s, c, fs, wordc));
}

/* int	main(void)
{
	char	*str = "Ceci, mon pote, est un test";
	char	**s;
	int		i;
	
	i = 0;
	s = ft_split(str, ' ');
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
	//printf("%s", s[6]);
	return (0);
} */