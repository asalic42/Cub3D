/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:16:59 by wolf              #+#    #+#             */
/*   Updated: 2024/01/16 16:22:38 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_mlx_stuff	*mlx_instance(void)
{
	static t_mlx_stuff	instance;

	return (&instance);
}

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

void	free_mlx_infos(void)
{
	t_mlx_stuff		*mlx_infos;
	t_textures_path	*textures;

	mlx_infos = mlx_instance();
	textures = get_textures_instance();
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm1);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm2);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm3);
	mlx_destroy_image(mlx_infos->mlx_ptr, textures->xpm4);
	if (mlx_infos->img_ptr)
		mlx_destroy_image(mlx_infos->mlx_ptr, mlx_infos->img_ptr);
	mlx_destroy_window(mlx_infos->mlx_ptr, mlx_infos->win_ptr);
	ft_printf(GREEN"Window is closing\n"NC);
	mlx_destroy_display(mlx_infos->mlx_ptr);
	free(mlx_infos->mlx_ptr);
	free_garbage();
}