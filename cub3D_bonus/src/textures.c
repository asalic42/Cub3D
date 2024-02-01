/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:28:16 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/01 20:41:02 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	init_textures_two(t_window *window, char *door, char *ennemy, t_mlx_stuff *mlx)
{
	t_textures_path	*textures;
	t_tmp_pixel		tmp_p;
	int				i;

	textures = get_textures_instance();
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 50, 200, 0xFF00AA, \
		"Loading east texture ...");
	textures->xpm4.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, window->east,
			&textures->xpm4.width, &textures->xpm4.height);
	textures->xpm4.xpm_data = mlx_get_data_addr(textures->xpm4.xpm,
			&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 50, 250, 0xFF00AA, \
		"Loading door texture...");
	textures->xpm_door.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, door, \
		&textures->xpm_door.width, &textures->xpm_door.height);
	textures->xpm_door.xpm_data = mlx_get_data_addr(textures->xpm_door.xpm, \
		&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	textures->xpm_ennemy.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, ennemy, \
		&textures->xpm_ennemy.width, &textures->xpm_ennemy.height);
	textures->xpm_ennemy.xpm_data = mlx_get_data_addr(textures->xpm_ennemy.xpm, \
		&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);

	textures->xpm_weapon.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/weapon.xpm", \
		&textures->xpm_weapon.width, &textures->xpm_weapon.height);
	textures->xpm_weapon.xpm_data = mlx_get_data_addr(textures->xpm_weapon.xpm, \
		&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	
	textures->xpm_weapon_firing.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/weapon_firing.xpm", \
		&textures->xpm_weapon_firing.width, &textures->xpm_weapon_firing.height);
	textures->xpm_weapon_firing.xpm_data = mlx_get_data_addr(textures->xpm_weapon_firing.xpm, \
		&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	
	textures->xpm_ennemy_dead.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/ennemy_dead.xpm", \
		&textures->xpm_ennemy_dead.width, &textures->xpm_ennemy_dead.height);
	textures->xpm_ennemy_dead.xpm_data = mlx_get_data_addr(textures->xpm_ennemy_dead.xpm, \
		&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	i = -1;
	while (++i < window->ennemies_count)	
		window->ennemies[i].tex = &textures->xpm_ennemy;
}

void	init_textures(t_window *window, char *door, char *ennemy)
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
	init_textures_two(window, door, ennemy, mlx);
}
