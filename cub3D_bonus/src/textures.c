/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:28:16 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/23 18:06:46 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	init_textures_two(t_window *window, char *door)
{
	t_textures_path	*textures;
	t_mlx_stuff		*mlx;
	t_tmp_pixel		tmp_p;

	mlx = get_mlx_ptr();
	textures = get_textures_instance();
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 50, 200, 0xFF00AA, \
		"Loading east texture ...");
	textures->xpm4.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, window->east,
			&textures->xpm4.width, &textures->xpm4.height);
	textures->xpm4.xpm_data = mlx_get_data_addr(textures->xpm4.xpm,
			&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 50, 250, 0xFF00AA, \
		"Loading door texture...");
	textures->xpm_door.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, door,
			&textures->xpm_door.width, &textures->xpm_door.height);
	textures->xpm_door.xpm_data = mlx_get_data_addr(textures->xpm_door.xpm, \
		&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
}

void	init_textures(t_window *window, char *door)
{
	t_textures_path	*textures;
	t_mlx_stuff		*mlx;
	t_tmp_pixel		tmp_p;

	mlx = get_mlx_ptr();
	textures = get_textures_instance();
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 50, 50, 0xFF00AA, \
		"Loading north texture ...");
	textures->xpm1.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, window->north,
			&textures->xpm1.width, &textures->xpm1.height);
	textures->xpm1.xpm_data = mlx_get_data_addr(textures->xpm1.xpm,
			&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 50, 100, 0xFF00AA, \
		"Loading west texture ...");
	textures->xpm2.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, window->west,
			&textures->xpm2.width, &textures->xpm2.height);
	textures->xpm2.xpm_data = mlx_get_data_addr(textures->xpm2.xpm,
			&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 50, 150, 0xFF00AA, \
		"Loading south texture ...");
	textures->xpm3.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, window->south,
			&textures->xpm3.width, &textures->xpm3.height);
	textures->xpm3.xpm_data = mlx_get_data_addr(textures->xpm3.xpm,
			&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	init_textures_two(window, door);
}
