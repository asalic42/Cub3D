/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:38:31 by asalic            #+#    #+#             */
/*   Updated: 2024/01/23 16:31:58 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
			i ++;
		}
		buf = get_next_line(parser->fd);
	}
	return (buf);
}

//If value == SPACE : check if around him, there is only 1
// or SPACE or limits of the map
int	is_contour(int x, int y, char **map, t_data *data)
{
	if (x < 0 || y < 0)
		return (1);
	if (map[data->y][data->x] == ' ' && (x < data->ptr.width && \
	y < data->ptr.height && map[y][x] && map[y][x] != '1' && map[y][x] != ' '))
		return (0);
	else if (map[data->y][data->x] == '0' && (x < data->ptr.width && \
	y < data->ptr.height && !map[y][x]))
		return (0);
	return (1);
}

int	contour_check(t_data *data, char **map)
{
	if (!is_contour(data->x -1, data->y, map, data))
		return (0);
	if (!is_contour(data->x, data->y +1, map, data))
		return (0);
	if (!is_contour(data->x, data->y -1, map, data))
		return (0);
	if (!is_contour(data->x +1, data->y, map, data))
		return (0);
	return (1);
}

int	is_space(t_data *data, char **map)
{
	if (map[data->y][data->x] == ' ' || map[data->y][data->x] == '0')
	{
		if (!contour_check(data, map))
			return (0);
	}
	return (1);
}

int	is_door_access(t_data *data, char **map)
{
	ft_printf("cette fonction marche \n");
	if (map[data->y][data->x -1] != '1' && map[data->y][data->x -1] != '1' \
	&& map[data->y +1][data->x] == '1' && map[data->y -1][data->x] == '1')
		return (1);
	if (map[data->y -1][data->x] != '1' && map[data->y +1][data->x] != '1' \
	&& map[data->y][data->x +1] == '1' && map[data->y][data->x -1] == '1')
		return (1);
	return (0);
}

int	main_parse(char **map, t_data *data)
{
	data->y = 0;
	while (map[data->y] && data->y < data->ptr.height)
	{
		data->x = 0;
		while (map[data->y][data->x] && data->x < data->ptr.width)
		{
			if (data->y == 0 || data->y == data->ptr.height -1 || data->x == 0
				|| data->x == data->ptr.width -1 || !map[data->y][data->x +1])
			{
				if (map[data->y][data->x] != '1' \
				&& map[data->y][data->x] != ' ')
					return (0);
				if (!is_space(data, map))
					return (0);
			}
			if (!is_space(data, map))
				return (0);
			if (map[data->y][data->x] == 'D' && !is_door_access(data, map))
				return (0);
			data->x ++;
		}
		data->y ++;
	}
	return (1);
}
