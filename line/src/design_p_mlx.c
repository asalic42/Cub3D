/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:16:59 by wolf              #+#    #+#             */
/*   Updated: 2023/12/12 20:06:13 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/basique_mlx_needed.h"

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
	t_mlx_stuff	*mlx_infos;

	mlx_infos = mlx_instance();
	mlx_destroy_window(mlx_infos->mlx_ptr, mlx_infos->win_ptr);
	if (mlx_infos->img_ptr)
		mlx_destroy_image(mlx_infos->mlx_ptr, mlx_infos->img_ptr);
	mlx_destroy_display(mlx_infos->mlx_ptr);
	free(mlx_infos->mlx_ptr);
}