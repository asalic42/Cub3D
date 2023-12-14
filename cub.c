/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:33:42 by asalic            #+#    #+#             */
/*   Updated: 2023/12/14 14:04:42 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int print_error(char *str)
{
    ft_printf("%s\n", str);
    return (1);
}

//Count of width
int	countmap_x(char	*mappy, t_data *data)
{
	int			width;
	t_parse	    map;
    int         fd;

	fd = open(mappy, O_RDONLY);
	if (fd == -1)
		count_error(data, &map, fd);
	width = 0;
	map.buffer = get_next_line(fd);
	while (map.buffer[width] && map.buffer[width] != '\n')
	{
		if (map.buffer[width] != '1' && map.buffer[width] != '0'
			&& map.buffer[width] != 'E' && map.buffer[width] != 'N'
			&& map.buffer[width] != 'W' && map.buffer[width] != 'S' &&
            map.buffer[width] != ' ')
			count_error(data, &map, fd);
		width ++;
	}
    while (map.buffer)
        map.buffer = get_next_line(fd);
    map.buffer = NULL;
	close(fd);
    ft_printf("width = %d\n", width);
	return (width);
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
	ft_printf("Error : Longueur infinie ou nulle\n");
	close_error(data);
}

//Close in case of error
void	close_error(t_data *data)
{
	mlx_destroy_display(data->ptr.mlx);
	free(data->ptr.mlx);
	exit (EXIT_FAILURE);
}

int main(int ac, char **av)
{
    t_parse parsing;
    t_data  data;

    if (ac != 2)
        return (print_error(RED "Error : not enought args\n" NC));
    start_garbage();
    data.ptr.mlx = mlx_init();
    if (!data.ptr.mlx)
        return (1);
    data.ptr.width = countmap_x(av[1], &data);
    data.ptr.height = countmap_y(av[1], &data);
    handle_error(&parsing, data.ptr.list, av[1]);
    data.ptr.map = ft_maptab(av[1], &data);
    if (main_parse(data.ptr.map, &data) == 1)
    {
        ft_printf("C'est faux");
        return (1);
    }
    data.ptr.wndo = mlx_new_window(data.ptr.mlx, data.ptr.width * 32,
			data.ptr.height * 32, "cub3D");
	if (data.ptr.wndo == NULL)
	{
		free(data.ptr.mlx);
		return (0);
	}
    // close_wndow(&data);
    return (0);
}
