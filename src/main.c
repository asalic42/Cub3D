/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/12 21:34:11 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

float px=100, py=100;
int map_x=8, map_y=8, map_s=64;
int map[]=          
	{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,	
	};


void draw_player(t_window *window) 
{	
	unsigned color = mlx_get_color_value(window->mlx_ptr, 0x555555);
	for (int i = 0; i < 1024*512 * 4; i+= 4){
		window->img_data[i] = (char)(color);
		window->img_data[i+1] = (char)(color >> 8);
		window->img_data[i+2] = (char)(color >> 16);
	}
	draw_map();
	draw_line(init_rectangle(px, py, px+10, py+10), window->img_ptr,0xFFFF00);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr, 0, 0);
	
}

void draw_map(void)
{
	int x, y, x0, y0;
	t_mlx_stuff *img = get_mlx_ptr();
	for (y = 0; y < map_y; y++)
	{
		y0 = y * map_s;
		for (x = 0; x < map_x; x++)
		{
			x0 = x * map_s;
			if (map[y * map_x + x] == 1)
				draw_line(init_rectangle(x0, y0, x0 + map_s, y0 + map_s), img->img_ptr, 0x000000);
			else
				draw_line(init_rectangle(x0, y0, x0 + map_s, y0 + map_s), img->img_ptr, 0xC0C0C0);
			//draw_line(init_rectangle(x0, 0, x0, y0 + map_s), img->img_ptr, 0xFF00FF);
		}
		draw_line(init_rectangle(0, y0, x0 + map_s, y0), img->img_ptr, 0x0000FF);
	}
}

int main() {
	t_window	window;


	if (!create_window(&window))
		return (0);

	update_mlx_infos(&window.mlx_ptr, &window.win_ptr, &window.img_ptr);
	draw_player(&window);
	mlx_loop_hook(window.mlx_ptr, &handle_no_event, &window);
	mlx_hook(window.win_ptr, 17, KeyPressMask, &destroy_window, &window);
	mlx_hook(window.win_ptr, 2, KeyPressMask, &key_press, &window);
	mlx_loop(window.mlx_ptr);
	return (1);
}


