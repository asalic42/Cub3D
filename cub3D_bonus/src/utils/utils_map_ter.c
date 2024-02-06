/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_ter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:07:27 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 19:07:54 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

char	**ft_strdup_double(char **str)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	dest = ft_malloc(ft_double_len(str) * sizeof(char *));
	while (str[i])
	{
		j = 0;
		dest[i] = ft_malloc((ft_strlen(str[i]) + 1) * sizeof(char));
		while (str[i][j])
		{
			dest[i][j] = str[i][j];
			j ++;
		}
		dest[i][j] = '\0';
		i ++;
	}
	return (dest);
}

int	is_in_char(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'W' && c != 'E'
		&& c != 'S' && c != ' ' && c != 'D' && c != 'B')
		return (print_error(RED "Error : forbidden element\n"NC));
	return (1);
}
