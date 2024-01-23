/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:42:22 by asalic            #+#    #+#             */
/*   Updated: 2024/01/23 14:36:56 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	init_count(char *mappy, t_parse *map)
{
	map->fd = open(mappy, O_RDONLY);
	if (map->fd == -1)
		count_error(map, map->fd);
	map->buffer = loop_gnl(map);
	ft_printf("buff : %s\n", map->buffer);
	return (map->fd);
}

void	is_in_char_error(t_parse map, int fd, int width)
{
	if (map.buffer[width] != '1' && map.buffer[width] != '0' \
	&& map.buffer[width] != 'E' && map.buffer[width] != 'N' \
	&& map.buffer[width] != 'W' && map.buffer[width] != 'S' \
	&& map.buffer[width] != ' ' && map.buffer[width] != 'D')
		count_error(&map, fd);
}

//Count of width
void	countmap_x(char	*mappy, t_window *window)
{
	int			width;
	t_parse		map;

	map.fd = open(mappy, O_RDONLY);
	if (map.fd == -1)
		count_error(&map, map.fd);
	map.buffer = loop_gnl(&map);
	while (map.buffer)
	{
		width = 0;
		while (map.buffer[width] && map.buffer[width] != '\n')
		{
			is_in_char_error(map, map.fd, width);
			width ++;
		}
		if (window->data.ptr.width == 0 || width > window->data.ptr.width)
			window->data.ptr.width = width;
		map.buffer = get_next_line(map.fd);
	}
	map.buffer = NULL;
	close(map.fd);
	ft_printf("final width = %d\n", window->data.ptr.width);
}

//Count of height
int	countmap_y(char	*mappy)
{
	int			height;
	int			i;
	t_parse		map;

	map.fd = init_count(mappy, &map);
	height = 0;
	i = 0;
	while (map.buffer && map.buffer[i] && map.buffer[i] != '\n')
	{
		is_in_char_error(map, map.fd, i);
		i ++;
		if (map.buffer && (map.buffer[i] == '\0' || map.buffer[i] == '\n'))
		{
			i = 0;
			height ++;
			map.buffer = get_next_line(map.fd);
		}
	}
	while (map.buffer)
		map.buffer = get_next_line(map.fd);
	close(map.fd);
	ft_printf("height = %d\n", height);
	return (height);
}

int	is_in_char(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'W' && c != 'E'
		&& c != 'S' && c != ' ' && c != 'D')
		return (print_error(RED "Error : forbidden element\n"NC));
	return (1);
}
