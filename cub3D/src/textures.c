/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:28:16 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/18 20:57:56 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	init_textures(char *path1, char *path2, char *path3, char *path4)
{
	t_textures_path	*textures;
	t_mlx_stuff		*mlx;
	t_tmp_pixel		tmp_p;

	mlx = get_mlx_ptr();
	textures = get_textures_instance();
	textures->xpm1.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, path1,
			&textures->xpm1.width, &textures->xpm1.height);
	textures->xpm1.xpm_data = mlx_get_data_addr(textures->xpm1.xpm,
			&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	textures->xpm2.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, path2,
			&textures->xpm2.width, &textures->xpm2.height);
	textures->xpm2.xpm_data = mlx_get_data_addr(textures->xpm2.xpm,
			&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	textures->xpm3.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, path3,
			&textures->xpm3.width, &textures->xpm3.height);
	textures->xpm3.xpm_data = mlx_get_data_addr(textures->xpm3.xpm,
			&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	textures->xpm4.xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, path4,
			&textures->xpm4.width, &textures->xpm4.height);
	textures->xpm4.xpm_data = mlx_get_data_addr(textures->xpm4.xpm,
			&tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
}
