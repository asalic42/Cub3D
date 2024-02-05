/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:34 by asalic            #+#    #+#             */
/*   Updated: 2024/02/05 18:54:26 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

/* Loop of gnl while it isn't the description of the map */
char	*loop_gnl(t_parse *parser)
{
	int		i;
	char	*buf;

	i = 0;
	buf = get_next_line(parser->fd);
	while (buf)
	{
		i = 0;
		while (buf[i])
		{
			while (buf[i] && (buf[i] == ' ' || buf[i] == '\t'))
				i ++;
			if (buf[i] == 'N' || buf[i] == 'S' || buf[i] == 'W' \
			|| buf[i] == 'E' || buf[i] == 'F' || buf[i] == 'C')
				break ;
			else if (buf && buf[i] == '1')
				return (buf);
			else if (buf[i] && buf[i] != ' ' && buf[i] != '\t' && buf[i] \
			!= '\n')
				return (NULL);
			i ++;
		}
		buf = get_next_line(parser->fd);
	}
	return (buf);
}

int	print_error(char *str)
{
	ft_printf(RED"%s\n"NC, str);
	return (0);
}

int	init_data(t_window *window, char *av)
{
	window->data.x = 0;
	window->data.y = 0;
	window->data.ptr.width = 0;
	window->data.ptr.height = countmap_y(av);
	if (!countmap_x(av, window))
		return (0);
	ft_maptab(av, &window->data, window);
	return (1);
}

int		ft_double_len(char **str)
{
	int i;
	int j;
	int	count;
	
	count = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{	
			count ++;
			j ++;
		}
		i ++;
	}
	return (count);
}

char	**ft_strdup_double(char **str)
{
	char **dest;
	int i;
	int	j;

	i = 0;
	dest = ft_malloc(ft_double_len(str) * sizeof(char *));
	while (str[i])
	{
		j = 0;
		dest[i] = ft_malloc((ft_strlen(str[i]) +1) * sizeof(char));
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
