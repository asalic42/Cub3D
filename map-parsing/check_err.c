/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:48 by asalic            #+#    #+#             */
/*   Updated: 2023/12/21 17:49:17 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	handle_error(t_data *data, char *map)
{
	error_files(data, map);
	if (!error_map(map))
		close_error(data, NULL);
	init_data(data, map);
	data->y = 0;
	data->x = 0;
	if (!map_up_n_down(data->ptr.map, data))
		close_error(data, NULL);
	if (!main_parse(data->ptr.map, data))
		close_error(data, "Error : wrong map\n");
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
int	close_wndo(t_data *data)
{
	int	i;

	i = 0;
	mlx_destroy_window(data->ptr.mlx, data->ptr.wndo);
	ft_printf(GREEN"Window is closing\n"NC);
	mlx_destroy_display(data->ptr.mlx);
	free(data->ptr.mlx);
	free_garbage();
	exit (EXIT_FAILURE);
}

//Close in case of error
void	close_error(t_data *data, char *error)
{
	if (error != NULL)
		ft_printf(RED"%s"NC, error);
	mlx_destroy_display(data->ptr.mlx);
	free(data->ptr.mlx);
	free_garbage();
	exit (EXIT_FAILURE);
}
