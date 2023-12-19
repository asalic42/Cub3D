/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/19 17:21:48 by rciaze           ###   ########.fr       */
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

float	distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

typedef struct s_all_stuff_for_ray_casting
{
	int				r;
	int				mx;
	int				my;
	int				mp;
	int				dof;
	float			rx;
	float			ry;
	float			ra;
	float			xo;
	float			yo;
	float			disH;
	float			disT;
	float			hx;
	float			hy;
	float			aTan;
	float			disV;
	float			vx;
	float			vy;
	float			nTan;
	float			ca;
	float			lineH;
	float			lineO;
	t_line			line;
	unsigned int	color;
} t_all_stuff_for_ray_casting;


void cast_ray() 
{
	t_mlx_stuff *img = get_mlx_ptr();;
	t_all_stuff_for_ray_casting	all_stuff;
	all_stuff.ra = pa - DR * 64;
	if (all_stuff.ra < 0)
		all_stuff.ra += 2 * PI;
	if (all_stuff.ra > 2 * PI)
		all_stuff.ra -= 2 * PI;
	for (all_stuff.r = 0; all_stuff.r<128; all_stuff.r++)
	{	
		all_stuff.dof = 0;
		all_stuff.disH = 1000000; // Big value so that the first intersection is always smaller
		all_stuff.hx = px; // We set the x coordinates of the intersection to the player's x coordinates
		all_stuff.hy = py; // We set the y coordinates of the intersection to the player's y coordinates
		all_stuff.aTan = -1/tan(all_stuff.ra); // We calculate the tangent of the angle

		if (all_stuff.ra > PI) // looking up
		{	
			all_stuff.ry = (((int)py / 64) * 64) - 0.0001; // We substract a very small value to avoid rounding errors
			all_stuff.rx = (py - all_stuff.ry) *all_stuff.aTan + px; // We calculate the x coordinate of the intersection
			all_stuff.yo = -64; // We set the y offset to -64
			all_stuff.xo = -all_stuff.yo * all_stuff.aTan; // We calculate the x offset
		}

		if (all_stuff.ra < PI) // looking down
		{
			all_stuff.ry = (((int)py / 64) * 64) + 64; // We add 64 to avoid rounding errors
			all_stuff.rx = (py - all_stuff.ry) * all_stuff.aTan + px; // We calculate the x coordinate of the intersection
			all_stuff.yo = 64; // We set the y offset to 64
			all_stuff.xo = -all_stuff.yo * all_stuff.aTan; // We calculate the x offset
		}
		
		if (all_stuff.ra == 0 || all_stuff.ra == PI) // looking straight left or right
		{
			all_stuff.rx = px; // We set the x coordinate of the intersection to the player's x coordinate
			all_stuff.ry = py; // We set the y coordinate of the intersection to the player's y coordinate
			all_stuff.dof = 10; // We set the depth of field to 10 to stop the loop
		}
		
		while (all_stuff.dof < 10) // Checking for horizontal intersections
		{
			all_stuff.mx = (int)(all_stuff.rx) / 64; // Map x coordinate
			all_stuff.my = (int) (all_stuff.ry) / 64; // Map y coordinate
			all_stuff.mp = all_stuff.my * map_x + all_stuff.mx; // Position on map
			if (all_stuff.mp > 0 && all_stuff.mp < map_x * map_y && map[all_stuff.mp] == 1) // If there is a wall
			{
				all_stuff.dof = 10; // Stop the loop
				all_stuff.hx = all_stuff.rx; // Save the x coordinates of the intersection
				all_stuff.hy = all_stuff.ry; // Save the y coordinates of the intersection
				all_stuff.disH = distance(px, py, all_stuff.hx, all_stuff.hy); // Calculate the distance between the player and the intersection
			}
			else
			{
				all_stuff.rx += all_stuff.xo; // If there is no wall, we move to the next intersection
				all_stuff.ry += all_stuff.yo; // same
				all_stuff.dof += 1; // continue the loop
			}
		}
	
		// same initialization as above
		all_stuff.dof = 0; 
		all_stuff.disV = 1000000;  
		all_stuff.vx = px; 
		all_stuff.vy = py; 
		all_stuff.nTan = -tan(all_stuff.ra);

		if (all_stuff.ra > PI2 && all_stuff.ra<PI3) // Looking left 
		{
			// same as above
			all_stuff.rx = (((int)px / 64) * 64) - 0.0001; 
			all_stuff.ry = (px - all_stuff.rx) * all_stuff.nTan + py; 
			all_stuff.xo = -64; 
			all_stuff.yo = -all_stuff.xo * all_stuff.nTan; 
		}
	
		if (all_stuff.ra < PI2 || all_stuff.ra > PI3) // Looking right
		{
			// same as above
			all_stuff.rx = (((int)px / 64) * 64) + 64; 
			all_stuff.ry = (px - all_stuff.rx) * all_stuff.nTan + py; 
			all_stuff.xo = 64; 
			all_stuff.yo = -all_stuff.xo * all_stuff.nTan; 
		}

		if (all_stuff.ra == 0 || all_stuff.ra == PI) // Looking straight up or down
		{
			// same as above
			all_stuff.ry = py; 
			all_stuff.rx = px; 
			all_stuff.dof = 10; 
		}
	
		while (all_stuff.dof < 10)
		{
			all_stuff.mx = (int)(all_stuff.rx) / 64; // Map x coordinate
			all_stuff.my = (int) (all_stuff.ry) / 64; // Map y coordinate
			all_stuff.mp = all_stuff.my * map_x + all_stuff.mx; // Position on map
			if (all_stuff.mp > 0 && all_stuff.mp < map_x * map_y && map[all_stuff.mp] == 1) // If there is a wall
			{
				all_stuff.dof = 10; // Stop the loop
				all_stuff.vx = all_stuff.rx; // Save the x coordinates of the intersection
				all_stuff.vy = all_stuff.ry; // Save the y coordinates of the intersection
				all_stuff.disV = distance(px, py, all_stuff.vx, all_stuff.vy); // Calculate the distance between the player and the intersection
			}
			else
			{
				all_stuff.rx += all_stuff.xo; // If there is no wall, we move to the next intersection
				all_stuff.ry += all_stuff.yo; // same
				all_stuff.dof += 1; // continue the loop
			}
		}
	

		// We compare the distances to the horizontal and vertical intersections

		if (all_stuff.disV < all_stuff.disH) // If the vertical intersection is closer
		{
			all_stuff.rx = all_stuff.vx; // We set the x coordinates of the intersection to the vertical intersection's x coordinates
			all_stuff.ry = all_stuff.vy; // We set the y coordinates of the intersection to the vertical intersection's y coordinates
			all_stuff.disT = all_stuff.disV; // We set the distance to the intersection to the vertical intersection's distance
			all_stuff.color = mlx_get_color_value(img->mlx_ptr, 0x0000A0); // We set the color to blue
		}
		else if (all_stuff.disH < all_stuff.disV) // If the horizontal intersection is closer
		{
			all_stuff.rx = all_stuff.hx; // We set the x coordinates of the intersection to the horizontal intersection's x coordinates
			all_stuff.ry = all_stuff.hy; // We set the y coordinates of the intersection to the horizontal intersection's y coordinates
			all_stuff.disT = all_stuff.disH ; // We set the distance to the intersection to the horizontal intersection's distance
			all_stuff.color = mlx_get_color_value(img->mlx_ptr, 0x0000FF); // We set the color to light blue
		}
	
		draw_line(init_rectangle(all_stuff.rx - 1, all_stuff.ry - 1 , all_stuff.rx + 2, all_stuff.ry + 2), img->img_ptr, 0x00FF00, 0); // We draw a small square at the intersection
		
		all_stuff.line = init_line(px, py, all_stuff.rx, all_stuff.ry); // We initialize the line that will draw the ray 
		all_stuff.line.width = 1;
		draw_line(all_stuff.line, img->img_ptr, 0x000050, 64); // We draw the line
	
		all_stuff.ca = pa - all_stuff.ra; // We calculate the angle between the player's angle and the ray's angle

		if (all_stuff.ca < 0) // We make sure the angle is between 0 and 2*PI
			all_stuff.ca += 2 * PI; // We add 2*PI if the angle is negative

		if (all_stuff. > 2 * PI) // We make sure the angle is between 0 and 2*PI
			all_stuff. -= 2 * PI; // We substract 2*PI if the angle is positive

		all_stuff.disT = all_stuff.disT * cos(all_stuff.ca); // We multiply the distance to the intersection by the cosine of the angle between the player's angle and the ray's angle
	
		all_stuff.lineH = (map_s * 500) / all_stuff.disT; // 500 is the max height of a line
		if (all_stuff.lineH > 500) // If the line is too big, we cut it.
			all_stuff.lineH = 500;
		all_stuff.lineO = 320 - all_stuff.lineH / 2; // line offset (to center it)

		all_stuff.line = init_line(all_stuff.r * 5 + 640, all_stuff.lineH + all_stuff.lineO, all_stuff.r * 5 + 640, lineO); // 5 is the width of the line, 640 is the center of the screen
		all_stuff.line.width = 5;
		draw_line(all_stuff.line, img->img_ptr, all_stuff.color, 0);

		all_stuff.ra += DR; // We increment the angle
		if (all_stuff.ra < 0) // We make sure the angle is between 0 and 2*PI
			all_stuff.ra += 2 * PI;
		if (all_stuff.ra > 2 * PI) // We make sure the angle is between 0 and 2*PI
			all_stuff.ra -= 2 * PI;
	}
}

void draw_player(t_window *window) 
{	
	t_line line;
	
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
	int x;
	int y;
	int x0;
	int y0;
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


