/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:50:21 by asalic            #+#    #+#             */
/*   Updated: 2024/01/17 17:11:06 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/* Basic notation error cases for colors */
static int	is_wrong_notation(char *comp, char *str)
{
	char	*from_space;
	char	*until_space;
	int		i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i ++;
	until_space = cut_until(str + i, ' ');
	if (ft_strncmp(comp, until_space, ft_strlen(until_space) + \
		ft_strlen(comp)) != 0)
		return (print_error(RED "Error : wrong notation in the .cub file" NC));
	from_space = cut_from(str + i, ' ');
	if (!ft_strchr(from_space, ','))
		return (print_error(RED "Error : wrong colors in the .cub file" NC));
	return (1);
}

/* Loop on the rgb colors to check them */
int	loop_check_rgb(char *dot_split)
{
	int	i;

	i = 0;
	while (dot_split[i])
	{
		if (!ft_isdigit(dot_split[i]))
			return (print_error(RED "Error : wrong colors in the .cub file" \
			NC));
		i ++;
	}
	if (ft_atoi(dot_split) < 0 || ft_atoi(dot_split) > 255)
		return (print_error(RED "Error : wrong colors in the .cub file" NC));
	return (1);
}

/* Assign the floor and ceiling value to window struct */
int	window_floor_n_ceiling(t_window *window, char **dot_split, char *comp)
{
	long int	rgb_to_hexa;

	rgb_to_hexa = hexa_to_decimal(convert_rgb_to_hexa(dot_split));
	if (comp[0] == 'F')
		window->floor = rgb_to_hexa;
	else if (comp[0] == 'C')
	{
		window->ceiling = rgb_to_hexa;
		if (window->ceiling == window->floor)
			return (print_error(RED"Error : floor and ceiling has the same \
			color"NC));
	}
	return (1);
}

/*  Check if the color of the floor and the ceiling is not the same
	Check if the color is in rgb and exists */
int	is_good_color(char *comp, char *str, t_window *window)
{
	char	**dot_split;
	int		tour;
	int		i;

	if (!is_wrong_notation(comp, str))
		return (0);
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i ++;
	dot_split = ft_split(cut_from(str + i, ' '), ',');
	ft_printf("je suis la et split vaut : %s\n", dot_split[0]);
	tour = 0;
	while (dot_split[tour])
	{
		if (!loop_check_rgb(dot_split[tour]))
			return (0);
		tour ++;
	}
	if (tour != 3)
		return (print_error(RED "Error : wrong colors in the .cub file" NC));
	if (!window_floor_n_ceiling(window, dot_split, comp))
		return (0);
	return (1);
}
