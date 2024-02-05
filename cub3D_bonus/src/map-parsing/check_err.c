/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:48 by asalic            #+#    #+#             */
/*   Updated: 2024/02/05 16:57:41 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

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
	if (!ennemy_parse(window->data.ptr.map, window))
		error_cases();
}

static char	**set_direction_tab(void)
{
	char	**tab_dir;
	int		i;

	i = 0;
	tab_dir = ft_malloc(7 * sizeof(char *));
	while (i < 6)
		tab_dir[i++] = ft_malloc(3 * sizeof(char));
	tab_dir[0] = "NO";
	tab_dir[1] = "SO";
	tab_dir[2] = "WE";
	tab_dir[3] = "EA";
	tab_dir[4] = "F";
	tab_dir[5] = "C";
	return (tab_dir);
}

int	is_buffer_good(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && (buf[i] == ' ' || buf[i] == '\t') && buf[i] != '\n')
	{
		i ++;
		if (!buf[i])
			return (0);
	}
	if (buf[i] == '\n')
		return (0);
	return (1);
}

/* Check if the description of the textures are good */
int	is_mapfile(char *map, t_window *window)
{
	int		fd;
	int		i;
	char	*buff;
	char	**tab_dir;

	fd = open(map, O_RDONLY);
	tab_dir = set_direction_tab();
	buff = get_next_line(fd);
	i = 0;
	while (buff && i < 6)
	{
		if (is_buffer_good(buff))
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
