/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:42:22 by asalic            #+#    #+#             */
/*   Updated: 2024/01/09 15:19:39 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	init_count(char *mappy, t_parse *map, t_window *window)
{
	int	fd;

	fd = open(mappy, O_RDONLY);
	if (fd == -1)
		count_error(map, fd, window);
	map->buffer = get_next_line(fd);
	return (fd);
}

void	is_in_char_error(t_parse map, t_window *window, int fd, int width)
{
	if (map.buffer[width] != '1' && map.buffer[width] != '0' \
	&& map.buffer[width] != 'E' && map.buffer[width] != 'N' \
	&& map.buffer[width] != 'W' && map.buffer[width] != 'S' \
	&& map.buffer[width] != ' ')
		count_error(&map, fd, window);
}

//Count of width
void	countmap_x(char	*mappy, t_window *window)
{
	int			width;
	t_parse		map;
	int			fd;

	fd = open(mappy, O_RDONLY);
	if (fd == -1)
		count_error(&map, fd, window);
	map.buffer = get_next_line(fd);
	while (map.buffer)
	{
		width = 0;
		while (map.buffer[width] && map.buffer[width] != '\n')
		{
			is_in_char_error(map, window, fd, width);
			width ++;
		}
		if (window->data.ptr.width == 0 || width > window->data.ptr.width)
			window->data.ptr.width = width;
		map.buffer = get_next_line(fd);
	}
	map.buffer = NULL;
	close(fd);
	ft_printf("final width = %d\n", window->data.ptr.width);
}

//Count of height
int	countmap_y(char	*mappy, t_window *window)
{
	int			height;
	int			i;
	int			fd;
	t_parse		map;

	fd = init_count(mappy, &map, window);
	height = 1;
	i = 0;
	while (map.buffer[i] && map.buffer[i] != '\n')
	{
		is_in_char_error(map, window, fd, i);
		i ++;
		if (map.buffer && map.buffer[i] == '\n')
		{
			i = 0;
			height ++;
			map.buffer = get_next_line(fd);
		}
	}
	while (map.buffer)
		map.buffer = get_next_line(fd);
	close(fd);
	ft_printf("height = %d\n", height);
	return (height);
}

int	is_in_char(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'W' && c != 'E'
		&& c != 'S' && c != ' ')
		return (0);
	return (1);
}
