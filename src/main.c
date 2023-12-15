/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/15 18:03:28 by rciaze           ###   ########.fr       */
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
	int r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo, disT;
	t_line line;
	ra = pa - DR * 64;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	for (r = 0; r<128; r++)
	{	
		dof = 0;
		float disH = 1000000; // Big value so that the first intersection is always smaller
		float hx = px; // We set the x coordinates of the intersection to the player's x coordinates
		float hy = py; // We set the y coordinates of the intersection to the player's y coordinates
		float aTan = -1/tan(ra); // We calculate the tangent of the angle

		if (ra > PI) // looking up
		{	
			ry = (((int)py / 64) * 64) - 0.0001; // We substract a very small value to avoid rounding errors
			rx = (py - ry) * aTan + px; // We calculate the x coordinate of the intersection
			yo = -64; // We set the y offset to -64
			xo = -yo * aTan; // We calculate the x offset
		}

		if (ra < PI) // looking down
		{
			ry = (((int)py / 64) * 64) + 64; // We add 64 to avoid rounding errors
			rx = (py - ry) * aTan + px; // We calculate the x coordinate of the intersection
			yo = 64; // We set the y offset to 64
			xo = -yo * aTan; // We calculate the x offset
		}
		
		if (ra == 0 || ra == PI) // looking straight left or right
		{
			rx = px; // We set the x coordinate of the intersection to the player's x coordinate
			ry = py; // We set the y coordinate of the intersection to the player's y coordinate
			dof = 10; // We set the depth of field to 10 to stop the loop
		}
		
		while (dof < 10) // Checking for horizontal intersections
		{
			mx = (int)(rx) / 64; // Map x coordinate
			my = (int) (ry) / 64; // Map y coordinate
			mp = my * map_x + mx; // Position on map
			if (mp > 0 && mp < map_x * map_y && map[mp] == 1) // If there is a wall
			{
				dof = 10; // Stop the loop
				hx = rx; // Save the x coordinates of the intersection
				hy = ry; // Save the y coordinates of the intersection
				disH = distance(px, py, hx, hy, ra); // Calculate the distance between the player and the intersection
			}
			else
			{
				rx += xo; // If there is no wall, we move to the next intersection
				ry += yo; // same
				dof += 1; // continue the loop
			}
		}
	
		// same initialization as above
		dof = 0; 
		float disV = 1000000;  
		float vx = px; 
		float vy = py; 
		float nTan = -tan(ra);

		if (ra > PI2 && ra<PI3) // Looking left 
		{
			// same as above
			rx = (((int)px / 64) * 64) - 0.0001; 
			ry = (px - rx) * nTan + py; 
			xo = -64; 
			yo = -xo * nTan; 
		}
	
		if (ra < PI2 || ra > PI3) // Looking right
		{
			// same as above
			rx = (((int)px / 64) * 64) + 64; 
			ry = (px - rx) * nTan + py; 
			xo = 64; 
			yo = -xo * nTan; 
		}

		if (ra == 0 || ra == PI) // Looking straight up or down
		{
			// same as above
			ry = py; 
			rx = px; 
			dof = 10; 
		}
	
		while (dof < 10)
		{
			mx = (int)(rx) / 64; // Map x coordinate
			my = (int) (ry) / 64; // Map y coordinate
			mp = my * map_x + mx; // Position on map
			if (mp > 0 && mp < map_x * map_y && map[mp] == 1) // If there is a wall
			{
				dof = 10; // Stop the loop
				vx = rx; // Save the x coordinates of the intersection
				vy = ry; // Save the y coordinates of the intersection
				disV = distance(px, py, vx, vy, ra); // Calculate the distance between the player and the intersection
			}
			else
			{
				rx += xo; // If there is no wall, we move to the next intersection
				ry += yo; // same
				dof += 1; // continue the loop
			}
		}
	
		unsigned int color = 0;

		// We compare the distances to the horizontal and vertical intersections

		if (disV < disH) // If the vertical intersection is closer
		{
			rx = vx; // We set the x coordinates of the intersection to the vertical intersection's x coordinates
			ry = vy; // We set the y coordinates of the intersection to the vertical intersection's y coordinates
			disT = disV; // We set the distance to the intersection to the vertical intersection's distance
			color = mlx_get_color_value(img->mlx_ptr, 0x0000A0); // We set the color to blue
		}
		else if (disH < disV) // If the horizontal intersection is closer
		{
			rx = hx; // We set the x coordinates of the intersection to the horizontal intersection's x coordinates
			ry = hy; // We set the y coordinates of the intersection to the horizontal intersection's y coordinates
			disT = disH ; // We set the distance to the intersection to the horizontal intersection's distance
			color = mlx_get_color_value(img->mlx_ptr, 0x0000FF); // We set the color to light blue
		}
	
		draw_line(init_rectangle(rx-1, ry-1, rx+2, ry+2), img->img_ptr, 0x00FF00, 0); // We draw a small square at the intersection
		
		line = init_line(px, py, rx, ry); // We initialize the line that will draw the ray 
		line.width = 1;
		draw_line(line, img->img_ptr, 0x000050, 64); // We draw the line
	
		float ca = pa - ra; // We calculate the angle between the player's angle and the ray's angle

		if (ca < 0) // We make sure the angle is between 0 and 2*PI
			ca += 2 * PI; // We add 2*PI if the angle is negative

		if (ca > 2 * PI) // We make sure the angle is between 0 and 2*PI
			ca -= 2 * PI; // We substract 2*PI if the angle is positive

		disT = disT * cos(ca); // We multiply the distance to the intersection by the cosine of the angle between the player's angle and the ray's angle
	
		float lineH = (map_s * 500) / disT; // 500 is the max height of a line
		if (lineH > 500) // If the line is too big, we cut it.
			lineH = 500;
		float lineO = 320 - lineH / 2; // line offset (to center it)

		line = init_line(r * 5 + 640, lineH + lineO, r * 5 + 640, lineO); // 5 is the width of the line, 640 is the center of the screen
		line.width = 5;
		draw_line(line, img->img_ptr, color, 0);

		ra += DR; // We increment the angle
		if (ra < 0) // We make sure the angle is between 0 and 2*PI
			ra += 2 * PI;
		if (ra > 2 * PI) // We make sure the angle is between 0 and 2*PI
			ra -= 2 * PI;
	}
}

void draw_player(t_window *window) 
{	
	t_line line;
	
	//unsigned color = mlx_get_color_value(window->mlx_ptr, 0x555555);
	
	draw_line(init_rectangle(0, 0, 640, 640), window->img_ptr, mlx_get_color_value(window->mlx_ptr, 0x555555), 0);
	draw_line(init_rectangle(640, 0, 1280, 320), window->img_ptr, mlx_get_color_value(window->mlx_ptr, 0x651684), 0);
	draw_line(init_rectangle(640, 320, 1280, 640), window->img_ptr, mlx_get_color_value(window->mlx_ptr, 0x665464), 0);
	
	if (px > 630)
		px = 10;
	if (py > 630)
		py = 10;
	if (px < 10)
		px = 630;
	if (py < 10)
		py = 630;
	draw_map();
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


