/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:48 by asalic            #+#    #+#             */
/*   Updated: 2024/01/08 16:51:20 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
