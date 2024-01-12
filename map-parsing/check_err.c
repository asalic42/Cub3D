/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:48 by asalic            #+#    #+#             */
/*   Updated: 2024/01/12 12:21:19 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int is_good_txture(char *comp, char *str, t_window *window)
{
	char *from_space;
	char *until_space;
	int fd;

	until_space = cut_until(str, ' ');
	if (ft_strncmp(comp, until_space, ft_strlen(until_space)) != 0)
		return (print_error(RED "Error : wrong notation in the .cub file" NC));
	from_space = cut_from(str, ' ');
	fd = open(from_space, O_RDONLY);
	if (fd <= 0)
		return (print_error(RED "Error : wrong texture file" NC));
	if (comp[0] == 'N')
		window->north = from_space;
	else if (comp[0] == 'S')
		window->south = from_space;
	else if (comp[0] == 'W')
		window->west = from_space;
	else if (comp[0] == 'E')
		window->east = from_space;
	close(fd);
	return (1);
}

char	*convert_hexa(unsigned int nb, char *base)
{
	int		i;
	int		c;
	char	*str;
	

	c = how_many_digits3(nb);
	str = ft_malloc((c + 1) * sizeof(char));
	i = c;
	if (i == 1)
	{
		while (i >= 0)
		{
			str[i] = '0';
			i --;
		}
		str[c+1] = '\0';
	}
	else
	{
		while (i-- > 0)
		{
			str[i] = base[nb%16];
			nb /= 16;
		}
		str[c] = '\0';
	}
	return (str);
}

char	*convert_rgb_to_hexa(char **rgb)
{
	char	*buf;
	int		hexa;
	int		i;

	hexa = 0;
	i = 0;
	buf = NULL;
	while (rgb[i])
	{
		hexa = ft_atoi(rgb[i]);
		if (!buf)
			buf = convert_hexa(hexa, "0123456789ABCDEF");
		else
			buf = ft_strjoin(buf, convert_hexa(hexa, "0123456789ABCDEF"));
		i ++;
	}
	return (buf);
}

#include <stdio.h>

int hexCharToDecimal(char hexChar)
{
	ft_printf("char = %c\n", hexChar);
    if (hexChar >= '0' && hexChar <= '9')
        return hexChar - '0';
	else if (hexChar >= 'A' && hexChar <= 'F')
        return hexChar - 'A' + 10;
	else
        return -1;
}

long hexadecimalToDecimal(const char *hexadecimal)
{
    long result = 0;

    while (*hexadecimal != '\0')
	{
        int digitValue = hexCharToDecimal(*hexadecimal);
        if (digitValue == -1)
		{
            ft_printf("Caractère non hexadécimal trouvé : %c\n", *hexadecimal);
            return -1;
        }
        result = result * 16 + digitValue;
        hexadecimal++;
    }
    return result;
}

int	is_good_color(char *comp, char *str, t_window *window)
{
	char	*from_space;
	long int rgb_to_hexa;
	char	**dot_split;
	char	*until_space;
	int		tour;
	int		i;
	
	(void)*window;
	until_space = cut_until(str, ' ');
	if (ft_strncmp(comp, until_space, ft_strlen(until_space) + ft_strlen(comp)) != 0)
		return (print_error(RED "Error : wrong notation in the .cub file" NC));
	from_space = cut_from(str, ' ');
	if (!ft_strchr(from_space, ','))
		return (print_error(RED "Error : wrong colors in the .cub file" NC));
	dot_split = ft_split(from_space, ',');
	tour = 0;
	while (dot_split[tour])
	{
		i = 0;
		while (dot_split[tour][i])
		{
			if (!ft_isdigit(dot_split[tour][i]))
				return (print_error(RED "Error : wrong colors in the .cub file" NC));
			i ++;
		}
		if (ft_atoi(dot_split[tour]) < 0 || ft_atoi(dot_split[tour]) > 255)
			return (print_error(RED "Error : wrong colors in the .cub file" NC));
		tour ++;
	}
	if (tour != 3)
		return (print_error(RED "Error : wrong colors in the .cub file" NC));
	rgb_to_hexa = hexadecimalToDecimal(convert_rgb_to_hexa(dot_split));
	ft_printf("rgb to hexa = %d\n", rgb_to_hexa);
	if (comp[0] == 'F')
		window->floor = rgb_to_hexa;
	else if (comp[0] == 'C')
	{
		window->ceiling = rgb_to_hexa;
	}
	return (1);
}

int	is_mapfile(char *map, t_window *window)
{
	int	fd;
	char *buff;
	char *tab_dir[6];
	int i;

	fd = open(map, O_RDONLY);
	tab_dir[0] = "NO";
	tab_dir[1] = "SO";
	tab_dir[2] = "WE";
	tab_dir[3] = "EA";
	tab_dir[4] = "F";
	tab_dir[5] = "C";
	buff = get_next_line(fd);
	i = 0;
	while (buff && i < 6)
	{
		if (buff[0] && buff[0] != '\n' && buff[0] != ' ' && buff[0] != '\t')
		{	
			if (i > 3 && !is_good_color(tab_dir[i], buff, window))
			{
				close(fd);
				return (0);
			}
			if (i < 4 && !is_good_txture(tab_dir[i], buff, window))
			{
				close(fd);
				return (0);
			}
			i ++;
		}
		buff = get_next_line(fd);
	}
	close(fd);
	return (1);
}

void	handle_error(t_window *window, char *map)
{
	error_files(window, map);
	if (!is_mapfile(map, window))
		close_error(window, NULL);
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

char	*loop_gnl(t_parse *parser)
{
	int i;
	char *buf;

	i = 0;
	buf = get_next_line(parser->fd);
	while (buf)
	{
		i = 0;
		ft_printf("line : %s\n", buf);
		while (buf[i])
		{
			if (buf[0] == 'N' || buf[0] == 'S' || buf[0] == 'W' || buf[0] == 'E' \
				|| buf[0] == 'F' || buf[0] == 'C')
				break ;
			else if (buf && buf[i] == '1')
				return (buf);
			i ++;
		}
		free(buf);
		buf = get_next_line(parser->fd);
	}
	return(buf);
}

//Check if all element of the map are valid (1, 0, N/S/E/W)
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
		ft_printf("%s\n", check_line);
		while (check_line[++i] && check_line[i] != '\n')
		{
			if (!is_in_char(check_line[i]))
				return (print_error(RED "Error : forbidden element\n"NC));
			len_player = only_one_thing(check_line, i, len_player);
			if (len_player == 1)
				return (0);
		}
		free(check_line);
		check_line = get_next_line(parser.fd);
	}
	if (len_player == -1)
		return (print_error(RED "Error : no player detected\n" NC));
	close(parser.fd);
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
