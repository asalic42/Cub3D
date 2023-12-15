/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:48 by asalic            #+#    #+#             */
/*   Updated: 2023/12/15 15:57:17 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

int	handle_error(t_data *data, char *map)
{
	if (!error_map(map))
		return (0);
	error_files(data, map);
	return (1);
}

//Check if all element of the map are valid (1, 0, N/S/E/W)
int		error_map(char *map)
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
			{
				ft_printf(RED "Error : forbidden element\n"NC);
				return (0);
			}
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
	if (check_line[i] == 'N' || check_line[i] == 'S'
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
