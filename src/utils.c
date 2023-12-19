/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:36:44 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/19 15:12:55 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	key_press(int keycode, t_window *window)
{
	if (keycode == 65307)
		return (mlx_destroy_window(window->mlx_ptr, window->win_ptr));
	if (keycode == 'a') 
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2* PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (keycode == 'd')
	{
		pa += 0.1;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (keycode == 'w')
	{
		px += pdx;
		py += pdy;
	}
	if (keycode == 's')
	{
		px -= pdx;
		py -= pdy;
	}
	if (py > 640)
		py = 0;
	if (py < 0)
		py = 640;
	if (px > 640)
		px = 0;
	if (px < 0)
		px = 640;
	mlx_destroy_image(window->mlx_ptr, window->img_ptr);
	window->img_ptr = mlx_new_image(window->mlx_ptr, 1280, 640);
	window->img_data = (mlx_get_data_addr(window->img_ptr, &(window->bits),
				&(window->size_line_img), &(window->endian)));
	draw_player(window);
	return (0);
}

int	handle_no_event(void *window)
{
	(void)(window);
	return (0);
}

int	create_window(t_window *window)
{
	window->bits = 3;
	window->size_line_img = 1280;
	window->mlx_ptr = mlx_init();
	if (window->mlx_ptr == NULL)
		return (0);
	window->win_ptr = mlx_new_window(window->mlx_ptr, 1280, 640, "cub");
	if (window->win_ptr == NULL)
		return (perror("Une erreur s'est produite "), mlx_destroy_display
			(window->mlx_ptr), free(window->mlx_ptr), 0);
	window->img_ptr = mlx_new_image(window->mlx_ptr, 1280, 640);
	if (window->img_ptr == NULL)
		return (perror("Une erreur s'est produite "), mlx_destroy_window
			(window->mlx_ptr, window->win_ptr), mlx_destroy_display
			(window->mlx_ptr), free(window->mlx_ptr), 0);
	window->img_data = (mlx_get_data_addr(window->img_ptr, &(window->bits),
				&(window->size_line_img), &(window->endian)));
	if (window->img_data == NULL)
		return (perror("Une erreur s'est produite "), mlx_destroy_image
			(window->mlx_ptr, window->img_ptr), mlx_destroy_window
			(window->mlx_ptr, window->win_ptr), mlx_destroy_display
			(window->mlx_ptr), free(window->mlx_ptr), 0);
	px = 300;
	py = 300;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	return (1);
}

int	destroy_window(t_window *window)
{
	return (mlx_destroy_window(window->mlx_ptr, window->win_ptr));
}