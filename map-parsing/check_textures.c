/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:47:57 by asalic            #+#    #+#             */
/*   Updated: 2024/01/16 16:44:52 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/* Check if N/S/E/W aren't the same textures */
static int	is_same_texture(t_window *window, char *new_one, char dir)
{
	if (dir == 'S')
	{
		if (ft_strncmp(window->north, new_one, ft_strlen(window->north) + \
		ft_strlen(new_one)) == 0)
			return (print_error(RED "Error : Same textures" NC));
	}
	else if (dir == 'W')
	{
		if (ft_strncmp(window->north, new_one, ft_strlen(window->north) + \
		ft_strlen(new_one)) == 0 || ft_strncmp(window->south, new_one, \
		ft_strlen(window->south) + ft_strlen(new_one)) == 0)
			return (print_error(RED "Error : Same textures" NC));
	}
	else if (dir == 'E')
	{
		if (ft_strncmp(window->north, new_one, ft_strlen(window->north) + \
		ft_strlen(new_one)) == 0 || ft_strncmp(window->west, new_one, \
		ft_strlen(window->west) + ft_strlen(new_one)) == 0 || \
		ft_strncmp(window->south, new_one, ft_strlen(window->south) + \
		ft_strlen(new_one)) == 0)
			return (print_error(RED "Error : Same textures" NC));
	}
	return (1);
}

/* Check if the textures exists and if yes, assign them into struct window */
int	is_good_txture(char *comp, char *str, t_window *window)
{
	char	*from_space;
	char	*until_space;
	int		fd;

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
	if (!is_same_texture(window, from_space, comp[0]))
		return (0);
	return (1);
}

/* Create a chain until we encounter the cut in the chain */
char	*cut_until(char *str, char cut)
{
	int		i;
	char	*new_cut;

	i = 0;
	while (str[i] && str[i] != cut)
		i ++;
	new_cut = ft_malloc((i +1) * sizeof(char));
	i = 0;
	while (str[i] && str[i] != cut)
	{
		new_cut[i] = str[i];
		i ++;
	}
	new_cut[i] = '\0';
	return (new_cut);
}

/* Create a chain from the cut (exclude) to the end of str */
char	*cut_from(char *str, char cut)
{
	int		i;
	char	*new_cut;
	int		j;

	i = 0;
	while (str[i] && str[i] != cut)
		i ++;
	if (str[i] == cut)
		i ++;
	j = 0;
	new_cut = ft_malloc(ft_strlen(str + i) * sizeof(char));
	while (str[i] && str[i] != '\n')
		new_cut[j++] = str[i++];
	new_cut[j] = '\0';
	return (new_cut);
}
