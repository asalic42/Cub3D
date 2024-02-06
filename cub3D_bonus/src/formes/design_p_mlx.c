/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:16:59 by wolf              #+#    #+#             */
/*   Updated: 2024/02/06 18:32:20 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	update_mlx_infos(void *mlx_ptr, void *win_ptr, void *img_ptr)
{
	t_mlx_stuff	*mlx_infos;

	mlx_infos = mlx_instance();
	mlx_infos->mlx_ptr = mlx_ptr;
	mlx_infos->win_ptr = win_ptr;
	mlx_infos->img_ptr = img_ptr;
}

void	*get_mlx_ptr(void)
{
	t_mlx_stuff	*mlx_infos;

	mlx_infos = mlx_instance();
	return (mlx_infos->mlx_ptr);
}

void	*get_win_ptr(void)
{
	t_mlx_stuff	*mlx_infos;

	mlx_infos = mlx_instance();
	return (mlx_infos->win_ptr);
}

static void	free_textures(t_mlx_stuff *mlx_infos)
{
	t_textures_path	*textures;

	textures = get_textures_instance();
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm1.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm2.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm3.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm4.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm_door.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm_ennemy.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm_ennemy_animated.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm_ennemy_dead.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm_weapon.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm_weapon_firing1.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm_weapon_firing2.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm_weapon_firing3.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm_weapon_firing4.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm_weapon_firing5.xpm);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm_weapon_firing6.xpm);
}

void	free_mlx_infos(void)
{
	t_mlx_stuff		*mlx_infos;

	mlx_infos = mlx_instance();
	free_textures(mlx_infos);
	if (mlx_infos->img_ptr)
		mlx_destroy_image(mlx_infos->mlx_ptr, mlx_infos->img_ptr);
	mlx_destroy_window(mlx_infos->mlx_ptr, mlx_infos->win_ptr);
	ft_printf(GREEN"Window is closing\n"NC);
	mlx_destroy_display(mlx_infos->mlx_ptr);
	free(mlx_infos->mlx_ptr);
	free_garbage();
}
