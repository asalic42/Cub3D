/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:48 by asalic            #+#    #+#             */
/*   Updated: 2024/01/16 16:27:46 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	error_cases(void)
{
	free_garbage();
	exit(EXIT_FAILURE);
}

/* Check all cases of error in the parsing part */
void	handle_error(t_window *window, char *map)
{
	error_files(map);
	if (!is_mapfile(map, window))
		error_cases();
	if (!error_map(map))
		error_cases();
	init_data(window, map);
	window->data.y = 0;
	window->data.x = 0;
	if (!map_up_n_down(window->data.ptr.map, &window->data))
		error_cases();
	if (!main_parse(window->data.ptr.map, &window->data))
	{
		ft_printf(RED"Error : wrong map\n"NC);
		error_cases();
	}
}

static char	**set_direction_tab(void)
{
	char	**tab_dir;
	int		i;

	i = 0;
	tab_dir = ft_malloc(7*sizeof(char *));
	while (i < 6)
		tab_dir[i++] = ft_malloc(3*sizeof(char));
	tab_dir[0] = "NO";
	tab_dir[1] = "SO";
	tab_dir[2] = "WE";
	tab_dir[3] = "EA";
	tab_dir[4] = "F";
	tab_dir[5] = "C";
	return (tab_dir);
}

/* Check if the description of the textures are good */
int	is_mapfile(char *map, t_window *window)
{
	int	fd;
	char *buff;
	char **tab_dir;
	int i;

	fd = open(map, O_RDONLY);
	tab_dir = set_direction_tab();
	buff = get_next_line(fd);
	i = 0;
	while (buff && i < 6)
	{
		if (buff[0] && buff[0] != '\n' && buff[0] != ' ' && buff[0] != '\t')
		{	
			if (i > 3 && !is_good_color(tab_dir[i], buff, window))
				break ;
			if (i < 4 && !is_good_txture(tab_dir[i], buff, window))
				break ;
			i ++;
		}
		buff = get_next_line(fd);
	}
	close(fd);
	if (i < 6)
		return (0);
	return (1);
}

/* Check if all element of the map are valid (1, 0, N/S/E/W) */
int	error_map(char *map)
{
	char	*check_line;
	int		len_player;
	t_parse	parser;
	int		i;

	parser.fd = open(map, O_RDONLY);
	len_player = -1;
	check_line = loop_gnl(&parser);
	while (check_line)
	{
		i = -1;
		while (check_line[++i] && check_line[i] != '\n')
		{
			if (!is_in_char(check_line[i]))
				return (print_error(RED "Error : forbidden element\n"NC));
			len_player = only_one_thing(check_line, i, len_player);
			if (len_player == 1)
				return (0);
		}
		check_line = get_next_line(parser.fd);
	}
	if (len_player == -1)
		return (print_error(RED "Error : no player detected\n" NC));
	close(parser.fd);
	return (1);
}

/* Check if there is only one player */
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
