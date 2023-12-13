/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/13 20:40:03 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

float px=100, py=100, pdx = 0, pdy = 0, pa = 0;
int map_x=10, map_y=10, map_s=64;
int map[]=          
	{
	1,1,1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,1,1,1,0,1,
	1,0,1,0,0,1,0,1,0,1,
	1,0,0,0,0,1,0,1,0,1,
	1,0,0,0,0,1,0,1,0,1,
	1,0,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,
	};

float	distance(float ax, float ay, float bx, float by, float ang)
{
	(void)(ang);
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void cast_ray() 
{
	t_mlx_stuff *img = get_mlx_ptr();;
	//void *new_img = mlx_new_image(img->mlx_ptr, 512, 512);
	int r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo, disT;
	t_line line;
	ra = pa - DR * 60;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	for (r = 0; r<120; r++)
	{	
		dof = 0;
		float disH = 1000000;
		float hx = px;
		float hy = py;
		float aTan = -1/tan(ra);
		if (ra > PI)
		{
			ry = (((int)py / 64) * 64) - 0.0001;
			rx = (py - ry) * aTan + px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int)py / 64) * 64) + 64;
			rx = (py - ry) * aTan + px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 10;
		}
		while (dof < 10)
		{
			mx = (int)(rx) / 64;
			my = (int) (ry) / 64;
			mp = my * map_x + mx;
			if (mp > 0 && mp < map_x * map_y && map[mp] == 1)
			{
				dof = 10;
				hx = rx;
				hy = ry;
				disH = distance(px, py, hx, hy, ra);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
	
		dof = 0;
		float disV = 1000000;
		float vx = px;
		float vy = py;
		float nTan = -tan(ra);
		if (ra > PI2 && ra<PI3)
		{
			rx = (((int)px / 64) * 64) - 0.0001;
			ry = (px - rx) * nTan + py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < PI2 || ra > PI3)
		{
			rx = (((int)px / 64) * 64) + 64;
			ry = (px - rx) * nTan + py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			ry = py;
			rx = px;
			dof = 10;
		}
		while (dof < 10)
		{
			mx = (int)(rx) / 64;
			my = (int) (ry) / 64;
			mp = my * map_x + mx;
			if (mp > 0 && mp < map_x * map_y && map[mp] == 1)
			{
				dof = 10;
				vx = rx;
				vy = ry;
				disV = distance(px, py, vx, vy, ra);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		unsigned int color = 0;
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
			color = mlx_get_color_value(img->mlx_ptr, 0x0000A0);
		}
		else if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH ;
			color = mlx_get_color_value(img->mlx_ptr, 0x0000FF);
		}
		line = init_line(px, py, rx, ry);
		line.width = 3;
		draw_line(line, img->img_ptr, 0x0000FF, 64);
		float ca = pa - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		disT = disT * cos(ca);
		float lineH = (map_s * 640) / disT;
		float lineO = 320 - lineH / 2;
		if (lineH > 640)
			lineH = 640;
		line = init_line(r * 5 + 658, lineH + lineO, r * 5 + 658, lineO);
		line.width = 5;
		draw_line(line, img->img_ptr, color, 0);
		ra += DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}

void draw_player(t_window *window) 
{	
	t_line line;
	
	unsigned color = mlx_get_color_value(window->mlx_ptr, 0x555555);
	for (int i = 0; i < 1280*640 * 4; i+= 4){
		window->img_data[i] = (char)(color);
		window->img_data[i+1] = (char)(color >> 8);
		window->img_data[i+2] = (char)(color >> 16);
	}
	draw_map();
	if (px > 630)
		px = 10;
	if (py > 630)
		py = 10;
	if (px < 10)
		px = 630;
	if (py < 10)
		py = 630;
	cast_ray();
	draw_line(init_rectangle(px - 5, py - 5, px+5, py+5), window->img_ptr,0xFFFF00, 5);
	
	line = init_line(px, py, px + pdx * 5, py + pdy * 5);
	line.width = 2;
	draw_line(line, window->img_ptr, 0xFFFF00, 1);
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
				draw_line(init_rectangle(x0, y0, x0 + map_s - 3, y0 + map_s - 1), img->img_ptr, 0x0F0F0F, 0);
			else
				draw_line(init_rectangle(x0, y0, x0 + map_s - 3, y0 + map_s - 1), img->img_ptr, 0xC0C0C0, 0);
		}
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


