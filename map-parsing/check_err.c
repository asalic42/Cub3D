/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:48 by asalic            #+#    #+#             */
/*   Updated: 2023/12/13 20:54:14 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

int	handle_error(t_parse* parsing, t_listmap *list, char *map)
{
	(void) *parsing;
	int fd;

	fd = open(map, O_RDONLY);
	if (error_map(fd))
		return (1);
	is_good_map(list, map);
	return (0);
}

//Check if all element of the map are valid (1, 0, N/S/E/W)
int		error_map(int fd)
{
	char	*check_line;
	int		len_player;
	int		i;

	len_player = -1;
	check_line = get_next_line(fd);
	while (check_line)
	{
		i = 0;
		while (check_line[i] && check_line[i] != '\n')
		{
			if (check_line[i] != '1' && check_line[i] != '0' && check_line[i] != 'N' 
			&& check_line[i] != 'W' && check_line[i] != 'E' && check_line[i] != 'S')
			{
				ft_printf(RED "Error : forbidden element\n"NC);
				return (1);
			}
			len_player = only_one_thing(check_line, i, len_player);
			if (len_player == 1)
				return (1);
			i++;
		}
		check_line = get_next_line(fd);
	}
	return (0);
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
