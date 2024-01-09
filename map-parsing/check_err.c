/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:48 by asalic            #+#    #+#             */
/*   Updated: 2024/01/09 13:33:43 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	*simple_tab_int(char **char_map, t_window *window)
{
	int *int_map;
	int	x;
	int y;
	int	i;

	y = 0;
	i = 0;
	int_map = ft_malloc((window->data.ptr.height * window->data.ptr.width) * \
	sizeof(int));
	while (y < window->data.ptr.height)
	{
		x = 0;
		while (x < window->data.ptr.width)
		{
			
			if (char_map[y][x] == 'N' || char_map[y][x] == 'E' || char_map[y][x] == 'W' || char_map[y][x] == 'S')
				int_map[i] = 2;
			else if (char_map[y][x] == ' ' || char_map[y][x] == '\0')
				int_map[i] = 0;
			else
				int_map[i] = char_map[y][x] - 48;
			ft_printf("%d,", int_map[i]);
			i ++;
			x ++;
		}
		ft_printf("\n");
		y ++;
	}
	return (int_map);
}

void	handle_error(t_window *window, char *map)
{
	error_files(window, map);
	if (!error_map(map))
		close_error(window, NULL);
	init_data(window, map);
	window->data.y = 0;
	window->data.x = 0;
	if (!map_up_n_down(window->data.ptr.map, &window->data))
		close_error(window, NULL);
	if (!main_parse(window->data.ptr.map, &window->data))
		close_error(window, "Error : wrong map\n");
}

//Check if all element of the map are valid (1, 0, N/S/E/W)
int	error_map(char *map)
{
	char	*check_line;
	int		len_player;
	int		fd;
	int		i;

	fd = open(map, O_RDONLY);
	len_player = -1;
	check_line = get_next_line(fd);
	while (check_line)
	{
		i = 0;
		while (check_line[i] && check_line[i] != '\n')
		{
			if (!is_in_char(check_line[i]))
				return (print_error(RED "Error : forbidden element\n"NC));
			len_player = only_one_thing(check_line, i, len_player);
			if (len_player == 1)
				return (0);
			i++;
		}
		check_line = get_next_line(fd);
	}
	if (len_player == -1)
		return (print_error(RED "Error : no player detected\n" NC));
	close(fd);
	return (1);
}

//Check if there is only one player
int	only_one_thing(char *check_line, int i, int len_player)
{
	if (check_line[i] == 'N' || check_line[i] == 'S' \
	|| check_line[i] == 'W' || check_line[i] == 'E')
	{
		if (len_player == -1)
			return (0);
		else
		{
			ft_printf(RED"Error : too much players detected in the map\n"NC);
			return (1);
		}
	}
	return (len_player);
}

//Close and free everything
int	close_wndo(t_window *window)
{
	int	i;

	i = 0;
	mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	ft_printf(GREEN"Window is closing\n"NC);
	mlx_destroy_display(window->mlx_ptr);
	free(window->mlx_ptr);
	free_garbage();
	exit (EXIT_FAILURE);
}

//Close in case of error
void	close_error(t_window *window, char *error)
{
	if (error != NULL)
		ft_printf(RED"%s"NC, error);
	mlx_destroy_display(window->mlx_ptr);
	free(window->mlx_ptr);
	free_garbage();
	exit (EXIT_FAILURE);
}
