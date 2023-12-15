/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:42:22 by asalic            #+#    #+#             */
/*   Updated: 2023/12/15 15:46:44 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

//Count of width
void	countmap_x(char	*mappy, t_data *data)
{
	int			width;
	t_parse	    map;
    int         fd;

	fd = open(mappy, O_RDONLY);
	if (fd == -1)
		count_error(data, &map, fd);
	map.buffer = get_next_line(fd);
	while (map.buffer)
	{
		width = 0;
		while (map.buffer[width] && map.buffer[width] != '\n')
		{
			if (map.buffer[width] != '1' && map.buffer[width] != '0'
				&& map.buffer[width] != 'E' && map.buffer[width] != 'N'
				&& map.buffer[width] != 'W' && map.buffer[width] != 'S' &&
    	        map.buffer[width] != ' ')
				count_error(data, &map, fd);
			width ++;
		}
		if (data->ptr.width == 0 || width > data->ptr.width)
			data->ptr.width = width;
        map.buffer = get_next_line(fd);
	}
    map.buffer = NULL;
	close(fd);
    ft_printf("final width = %d\n", data->ptr.width);
}

//Count of height
int	countmap_y(char	*mappy, t_data *data)
{
	int			height;
    int         i;
    int         fd;
	t_parse	    map;

	fd = open(mappy, O_RDONLY);
	if (fd == -1)
		count_error(data, &map, fd);
    map.buffer = get_next_line(fd);
	height = 1;
    i = 0;
	while (map.buffer[i] && map.buffer[i] != '\n')
	{
		if (map.buffer[i] != '1' && map.buffer[i] != '0'
			&& map.buffer[i] != 'N' && map.buffer[i] != 'E'
			&& map.buffer[i] != 'W' && map.buffer[i] != 'S'
            && map.buffer[i] != ' ')
			count_error(data, &map, fd);
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
    map.buffer = NULL;
	close(fd);
    ft_printf("height = %d\n", height);
	return (height);
}

//Error of 
void	count_error(t_data *data, t_parse *map, int fd)
{
	if (map->buffer)
		free(map->buffer);
	if (fd != -1)
    {
        while (map->buffer)
            map->buffer = get_next_line(fd);
        map->buffer = NULL;
        ft_printf("je suis close bro\n");
		close(fd);
    }
	ft_printf(RED"Error : Longueur infinie ou nulle\n"NC);
	close_error(data);
}

int	is_in_char(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'W' && c != 'E'
		&& c != 'S' && c != ' ')
		return (0);
	return (1);
}
