/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:08:20 by okraus            #+#    #+#             */
/*   Updated: 2024/02/11 09:48:29 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static void	ft_big_swap(int a[3], int b[3], unsigned int c[2])
{
	ft_swap(&a[0], &a[1]);
	ft_swap(&b[0], &b[1]);
	ft_uswap(&c[0], &c[1]);
}

static unsigned int	ft_mix_colour2(unsigned int d[2], unsigned int rgb[4],
	unsigned int c[2])
{
	unsigned int	r[4];

	if ((c[0] & 0xFF000000) < (c[1] & 0xFF000000))
		r[0] = ((rgb[0] * d[0]) / d[1] + ((c[0] & 0xFF000000) >> 24)) << 24;
	else
		r[0] = (((c[0] & 0xFF000000) >> 24) - ((rgb[0] * d[0]) / d[1])) << 24;
	if ((c[0] & 0xFF0000) < (c[1] & 0xFF0000))
		r[1] = (rgb[1] * d[0] / d[1] + ((c[0] & 0xFF0000) >> 16)) << 16;
	else
		r[1] = (((c[0] & 0xFF0000) >> 16) - (rgb[1] * d[0] / d[1])) << 16;
	if ((c[0] & 0xFF00) < (c[1] & 0xFF00))
		r[2] = (rgb[2] * d[0] / d[1] + ((c[0] & 0xFF00) >> 8)) << 8;
	else
		r[2] = (((c[0] & 0xFF00) >> 8) - (rgb[2] * d[0] / d[1])) << 8;
	if ((c[0] & 0xFF) < (c[1] & 0xFF))
		r[3] = rgb[3] * d[0] / d[1] + (c[0] & 0xFF);
	else
		r[3] = (c[0] & 0xFF) - rgb[3] * d[0] / d[1];
	return (r[0] | r[1] | r[2] | r[3]);
}

static unsigned int	ft_mix_colour(int x[3], int y[3], unsigned int c[2])
{
	unsigned int	d[2];
	unsigned int	rgb[4];

	d[0] = ft_abs(x[2] - x[0]) + ft_abs(y[2] - y[0]);
	d[1] = ft_abs(x[1] - x[0]) + ft_abs(y[1] - y[0]);
	if (!d[1])
		d[1] = 1;
	rgb[0] = (ft_uabsdif(c[0] & 0xFF000000, c[1] & 0xFF000000)) >> 24;
	rgb[1] = (ft_uabsdif(c[0] & 0xFF0000, c[1] & 0xFF0000)) >> 16;
	rgb[2] = (ft_uabsdif(c[0] & 0xFF00, c[1] & 0xFF00)) >> 8;
	rgb[3] = ft_uabsdif(c[0] & 0xFF, c[1] & 0xFF);
	return (ft_mix_colour2(d, rgb, c));
}

//different max values for different imgs, maybe structure with colour;
static void	ft_plot_line_low(mlx_image_t *img, t_ray l)
{
	l.dx = l.x[1] - l.x[0];
	l.dy = l.y[1] - l.y[0];
	l.yi = 1;
	if (l.dy < 0)
	{
		l.yi = -1;
		l.dy *= -1;
	}
	l.d = (2 * l.dy) - l.dx;
	l.x[2] = l.x[0];
	l.y[2] = l.y[0];
	while (l.x[2] <= l.x[1])
	{
		if (l.x[2] > 0 && l.x[2] < l.maxwidth && l.y[2] > 0 && l.y[2] < l.maxheight)
			mlx_put_pixel(img, l.x[2], l.y[2], ft_mix_colour(l.x, l.y, l.c));
		if (l.d > 0)
		{
			l.y[2] = l.y[2] + l.yi;
			l.d += 2 * (l.dy - l.dx);
		}
		else
			l.d = l.d + 2 * l.dy;
		l.x[2]++;
	}
}

static void	ft_plot_line_high(mlx_image_t *img, t_ray l)
{
	l.dx = l.x[1] - l.x[0];
	l.dy = l.y[1] - l.y[0];
	l.xi = 1;
	if (l.dx < 0)
	{
		l.xi = -1;
		l.dx *= -1;
	}
	l.d = (2 * l.dx) - l.dy;
	l.x[2] = l.x[0];
	l.y[2] = l.y[0];
	while (l.y[2] <= l.y[1])
	{
		if (l.x[2] > 0 && l.x[2] < l.maxwidth && l.y[2] > 0 && l.y[2] < l.maxheight)
			mlx_put_pixel(img, l.x[2], l.y[2],ft_mix_colour(l.x, l.y, l.c));
		if (l.d > 0)
		{
			l.x[2] = l.x[2] + l.xi;
			l.d = l.d + (2 * (l.dx - l.dy));
		}
		else
			l.d = l.d + 2 * l.dx;
		l.y[2]++;
	}
}

void	ft_place_line(mlx_image_t *img, t_ray l)
{
	if (ft_abs(l.y[1] - l.y[0]) < ft_abs(l.x[1] - l.x[0]))
	{
		if (l.x[0] > l.x[1])
			ft_big_swap(l.x, l.y, l.c);
		ft_plot_line_low(img, l);
	}
	else
	{
		if (l.y[0] > l.y[1])
			ft_big_swap(l.x, l.y, l.c);
		ft_plot_line_high(img, l);
	}
}



// int	ft_is_inside2(t_max *max, unsigned int rad2, int y, int x)
// {
// 	unsigned int	cx;
// 	unsigned int	cy;

// 	cx = x - (int)max->map->p.x + max->math->sin[max->map->p.orientation] / 1024;
// 	cy = y - (int)max->map->p.y + max->math->cos[max->map->p.orientation] / 1024;
// 	if (cx * cx + cy * cy <= rad2)
// 		return (1);
// 	return (0);
// }
void	ft_erase_map(t_max *max)
{
	int	y;
	int	x;

	y = 0;
	while (y < MAPHEIGHT)
	{
		x = 0;
		while (x < MAPWIDTH)
		{
			mlx_put_pixel(max->maximap, x, y, 0x0);
			++x;
		}
		++y;
	}
}



// void	ft_draw_minimap(t_max *max)
// {
// 	int	y;
// 	int	x;
// 	int	ny;
// 	int	nx;
// 	int	s; //scaling factor
// 	int	r;

// 	s = 8;
// 	y = 0;
// 	// while (y < MINIHEIGHT)
// 	// {
// 	// 	x = 0;
// 	// 	while (x < MINIWIDTH)
// 	// 	{
// 	// 		ny = y + ((int)max->map->p.y * s / 256) - MINIHEIGHT / 2;
// 	// 		nx = x + ((int)max->map->p.x * s / 256) - MINIWIDTH / 2;
// 	// 		if (ny > 0 && nx > 0 && ny < max->map->h * s && nx < max->map->w * s)
// 	// 		{
// 	// 			if (ft_is_inside(max->map, 4096, (ny << 8) / s, (nx << 8) / s))
// 	// 			{
// 	// 				//ft_printf("y= %i, x= %i\n", y, x);
// 	// 				mlx_put_pixel(max->maximap, x, y, max->map->c.rgba & TMASK);	//player has ceiling colour
// 	// 			}
// 	// 			// else if (ft_is_inside2(max, 1024, (y << 8) / s, (x << 8) / s))
// 	// 			// {
// 	// 			// 	mlx_put_pixel(max->map, x, y, 0x00ff00ff & TMASK);	//green circle for the direction visualisation
// 	// 			// }
// 	// 			else if (max->map->m[(ny / s) * max->map->w + (nx / s)] & WALL)
// 	// 			{
// 	// 				if (max->map->m[(ny / s) * max->map->w + (nx / s)] & VISITED)
// 	// 					mlx_put_pixel(max->maximap, x, y, 0x000000ff & TMASK); //Visited wall shine white
// 	// 				else
// 	// 					mlx_put_pixel(max->maximap, x, y, UNDISCOVERDWALL & TMASK); //black for unvisited area
// 	// 			}
// 	// 			else if (max->map->m[(ny / s) * max->map->w + (nx / s)] & FLOOR)
// 	// 			{
// 	// 				if (max->map->m[(ny / s) * max->map->w + (nx / s)] & VISITED)
// 	// 					mlx_put_pixel(max->maximap, x, y, max->map->f.rgba & TMASK); //floor is the proper colour
// 	// 				else
// 	// 					mlx_put_pixel(max->maximap, x, y, UNDISCOVERDFLOOR & TMASK); //black for unvisited area
// 	// 			}
// 	// 			else
// 	// 				mlx_put_pixel(max->maximap, x, y, 0x404040FF & TMASK);
// 	// 		}
// 	// 		else
// 	// 			mlx_put_pixel(max->maximap, x, y, 0x808080FF & TMASK);
// 	// 		++x;
// 	// 	}
// 	// 	++y;
// 	// }
// 	while (y < MINIHEIGHT)
// 	{
// 		x = 0;
// 		while (x < MINIWIDTH)
// 		{
// 			ny = y + ((int)max->map->p.y * s / 256) - MINIHEIGHT / 2;
// 			nx = x + ((int)max->map->p.x * s / 256) - MINIWIDTH / 2;
// 			if (ny > 0 && nx > 0 && ny < max->map->h * s && nx < max->map->w * s)
// 			{
// 				if (ft_is_inside(max->map, 4096, (ny << 8) / s, (nx << 8) / s))
// 				{
// 					//ft_printf("y= %i, x= %i\n", y, x);
// 					mlx_put_pixel(max->minimap, x, y, max->map->c.rgba & TMASK);	//player has ceiling colour
// 				}
// 				// else if (ft_is_inside2(max, 1024, (y << 8) / s, (x << 8) / s))
// 				// {
// 				// 	mlx_put_pixel(max->map, x, y, 0x00ff00ff & TMASK);	//green circle for the direction visualisation
// 				// }
// 				else if (max->map->m[(ny / s) * max->map->w + (nx / s)] & WALL)
// 				{
// 					//mlx_put_pixel(max->minimap, x, y, 0x000000FF & TMASK); //walls are black for now
// 					if (max->map->m[(ny / s) * max->map->w + (nx / s)] & VISITED)
// 						mlx_put_pixel(max->minimap, x, y, 0x000000ff & TMASK); //Visited wall shine white
// 					else
// 						mlx_put_pixel(max->minimap, x, y, UNDISCOVERDWALL & TMASK); //black for unvisited area
// 				}
// 				else if (max->map->m[(ny / s) * max->map->w + (nx / s)] & FLOOR)
// 				{
// 					// mlx_put_pixel(max->minimap, x, y, max->map->f.rgba & TMASK); //floor is the proper colour
// 					if (max->map->m[(ny / s) * max->map->w + (nx / s)] & VISITED)
// 						mlx_put_pixel(max->minimap, x, y, max->map->f.rgba & TMASK); //floor is the proper colour
// 					else
// 						mlx_put_pixel(max->minimap, x, y, UNDISCOVERDFLOOR & TMASK); //black for unvisited area
// 				}
// 				else
// 					mlx_put_pixel(max->minimap, x, y, 0x404040FF & TMASK);
// 			}
// 			else
// 				mlx_put_pixel(max->minimap, x, y, 0x808080FF & TMASK);
// 			++x;
// 		}
// 		++y;
// 	}

// 	r = 0;
	
// 	while (r < RAYS)
// 	{
// 		max->map->p.miniray[r].x[0] = MINIWIDTH / 2;
// 		max->map->p.miniray[r].y[0] = MINIHEIGHT / 2;
// 		max->map->p.miniray[r].x[1] = MINIWIDTH / 2 + ((((max->map->p.ray[r].rx - max->map->p.ray[r].xs)) * s) >> 16);
// 		max->map->p.miniray[r].y[1] = MINIHEIGHT / 2 + ((((max->map->p.ray[r].ry - max->map->p.ray[r].ys)) * s) >> 16);
// 		max->map->p.miniray[r].maxheight = MINIHEIGHT;
// 		max->map->p.miniray[r].maxwidth = MINIWIDTH;
// 		max->map->p.miniray[r].c[0] = max->map->p.ray[r].c[0];
// 		max->map->p.miniray[r].c[1] = max->map->p.ray[r].c[1];
// 		ft_place_line(max->minimap, max->map->p.miniray[r]);
// 		++r;
// 	}
// 	r = 0;
	
// 	// while (r < RAYS)
// 	// {	
// 	// 	max->map->p.miniray[r].x[0] = MINIWIDTH / 2;
// 	// 	max->map->p.miniray[r].y[0] = MINIHEIGHT / 2;
// 	// 	max->map->p.miniray[r].ra = max->map->p.orientation - max->map->p.fov2 + r * max->map->p.fov * 65536LL / (RAYS - 1) / 360;
// 	// 	max->map->p.miniray[r].x[1] = MINIWIDTH / 2 - (((max->math->sin[max->map->p.miniray[r].ra]) * s) / 8192);
// 	// 	max->map->p.miniray[r].y[1] = MINIHEIGHT / 2 - (((max->math->cos[max->map->p.miniray[r].ra]) * s) / 8192);
// 	// 	max->map->p.miniray[r].c[0] = 0xffff00ff;
// 	// 	max->map->p.miniray[r].c[1] = max->map->f.rgba;
// 	// 	max->map->p.miniray[r].maxheight = MINIHEIGHT;
// 	// 	max->map->p.miniray[r].maxwidth = MINIWIDTH;
// 	// 	ft_place_line(max->minimap, max->map->p.miniray[r]);
// 	// 	++r;
// 	// }
// 	// max->map->p.xl[0] = MINIWIDTH / 2;
// 	// max->map->p.yl[0] = MINIHEIGHT / 2;
// 	// max->map->p.xl[1] = MINIWIDTH / 2 - max->math->sin[(unsigned short)(max->map->p.orientation + max->map->p.fov2)] * s / 16384;
// 	// max->map->p.yl[1] = MINIHEIGHT / 2 - max->math->cos[(unsigned short)(max->map->p.orientation + max->map->p.fov2)] * s / 16384;
// 	// max->map->p.xr[0] = MINIWIDTH / 2;
// 	// max->map->p.yr[0] = MINIHEIGHT / 2;
// 	// max->map->p.xr[1] = MINIWIDTH / 2  - max->math->sin[(unsigned short)(max->map->p.orientation - max->map->p.fov2)] * s / 16384;
// 	// max->map->p.yr[1] = MINIHEIGHT / 2 - max->math->cos[(unsigned short)(max->map->p.orientation - max->map->p.fov2)] * s / 16384;
// 	// ft_place_line(max->minimap, max->map->p.xx, max->map->p.yy, 0xff0000ff);
// 	// ft_place_line(max->minimap, max->map->p.xl, max->map->p.yl, 0xffff00ff);
// 	// ft_place_line(max->minimap, max->map->p.xr, max->map->p.yr, 0xffff00ff);
// 	// max->map->p.xd[0] = MINIWIDTH / 2;;
// 	// max->map->p.yd[0] = MINIHEIGHT / 2;
// 	// max->map->p.xd[1] = max->map->p.xd[0] + max->map->p.dx * s / 16384;
// 	// max->map->p.yd[1] = max->map->p.yd[0] + max->map->p.dy * s / 16384;
// 	// ft_place_line(max->minimap, max->map->p.xd, max->map->p.yd, 0x0000ffff);
// 	// max->map->p.xc[0] = max->map->p.xd[1];
// 	// max->map->p.yc[0] = max->map->p.yd[1];
// 	// max->map->p.xc[1] = max->map->p.xc[0] + max->map->p.cx * s / 16384;
// 	// max->map->p.yc[1] = max->map->p.yc[0] + max->map->p.cy * s / 16384;
// 	// ft_place_line(max->minimap, max->map->p.xc, max->map->p.yc, 0xff00ffff);
// 	// max->map->p.xn[0] = max->map->p.xd[1];
// 	// max->map->p.yn[0] = max->map->p.yd[1];
// 	// max->map->p.xn[1] = max->map->p.xn[0] - max->map->p.cx * s / 16384;
// 	// max->map->p.yn[1] = max->map->p.yn[0] - max->map->p.cy * s / 16384;
// 	// ft_place_line(max->minimap, max->map->p.xn, max->map->p.yn, 0xffa0ffff);
// }

// // Weird psychadelich stuff
// // unsigned int	ft_get_colour(int x, int xw, int y, int wh, mlx_texture_t *img)
// // {
// // 	unsigned int	r;
// // 	int				h;
// // 	int				w;
// // 	int				p;

// // 	w = img->width;
// // 	h = img->height;
// // 	p = w * y / wh + 0 * h;
// // 	r = (img->pixels[p] << 24) | (img->pixels[p + 1] << 16) | (img->pixels[p + 2] << 8) | 0x0000FF;
// // 	(void)x;
// // 	(void)xw;
// // 	return (r);
// // }

// unsigned int	ft_get_colour(t_max *max, int x, long long length, int y, int wh, mlx_texture_t *img)
// {
// 	t_clr			r;
// 	int				h;
// 	int				w;
// 	int				p;
// 	int				xw;

// 	xw = 65536;
// 	w = img->width;
// 	h = img->height;
// 	p = w * 4 * (h * y / wh) + (4 * (w * x / xw));
// 	//ft_printf("%i %i\n",(h * y / wh), (w * x / xw));
// 	r.rgba = (img->pixels[p] << 24) | (img->pixels[p + 1] << 16) | (img->pixels[p + 2] << 8) | 0x0000FF;
// 	if (length > MAXDIST)
// 		length = MAXDIST;
// 	r.r = max->math->brumered[r.r][length * 255LL / MAXDIST];
// 	r.g = max->math->brumegreen[r.g][length * 255LL / MAXDIST];
// 	r.b = max->math->brumeblue[r.b][length * 255LL / MAXDIST];
// 	return (r.rgba);
// }

// unsigned int	ft_get_colour2(t_max *max, unsigned int c, int y, int fake_offset)
// {
// 	t_clr			r;
// 	int				length;
// 	int				start;
// 	int				offset;

// 	r.rgba = c;
// 	offset = HEIGHT / 2 - fake_offset;
// 	start = 2 * offset;
// 	if (y < HEIGHT / 2)
// 		length = PERCENTIL(0, 255, start + y, HEIGHT / 2 + offset);
// 	else
// 		length = PERCENTIL(0, 255, start + (HEIGHT - y), HEIGHT / 2 + offset);
// 	// if (y < HEIGHT / 2)
// 	//  	ft_printf("%i %i %i %i || %i %i\n", start, length, y, offset, start + y, HEIGHT / 2 + offset);
// 	//ft_printf("1 %3i %3i %3i %3i || ", r.r, r.g, r.b, length); 
// 	r.r = max->math->brumered[r.r][length];
// 	r.g = max->math->brumegreen[r.g][length];
// 	r.b = max->math->brumeblue[r.b][length];
// 	//ft_printf("2 %3i %3i %3i %3i\n", r.r, r.g, r.b, length); 
// 	return (r.rgba);
// }

// void	ft_get_colour3(t_max *max, unsigned int c, int y, int fake_offset)
// {
// 	t_clr			r;
// 	int				length;
// 	int				start;
// 	int				offset;

// 	r.rgba = c;
// 	offset = HEIGHT / 2 - fake_offset;
// 	start = 2 * offset;
// 	if (y < HEIGHT / 2)
// 		length = PERCENTIL(0, 255, start + y, HEIGHT / 2 + offset);
// 	else
// 		length = PERCENTIL(0, 255, start + (HEIGHT - y), HEIGHT / 2 + offset);
// 	// if (y < HEIGHT / 2)
// 	//  	ft_printf("%i %i %i %i || %i %i\n", start, length, y, offset, start + y, HEIGHT / 2 + offset);
// 	ft_printf("1 %3i %3i %3i %3i || ", r.r, r.g, r.b, length); 
// 	r.r = max->math->brumered[r.r][length];
// 	r.g = max->math->brumegreen[r.g][length];
// 	r.b = max->math->brumeblue[r.b][length];
// 	ft_printf("2 %3i %3i %3i %3i\n", r.r, r.g, r.b, length); 
// }

// void	ft_draw_screen(t_max *max)
// {
// 	int	y;
// 	int	x;
// 	int	r;
// 	int	wall_height;
// 	int	offset;
// 	int	fake_wall_height;
// 	int	fake_offset;
// 	long long	length;
// 	long long	fake_length;

// 	x = 0;
// 	while (x < SCREENWIDTH)
// 	{
// 		y = 0;
// 		r = x * RAYS / SCREENWIDTH;
// 		//ft_printf("new ray\n");
// 		//ft_printf("%i %i\n", r, x);
// 		length = max->map->p.ray[r].length;
// 		fake_length = MAXDIST;
// 		if (NOFISHEYE)
// 		{
// 			//ft_printf("L1 %Lx\n", max->map->p.ray[r].length);
// 			//ft_printf("ANGLE %i\n", (unsigned short)(max->map->p.orientation - max->map->p.ray[r].ra));
// 			length *= max->math->cos[(unsigned short)(max->map->p.orientation - max->map->p.ray[r].ra)];
// 			fake_length *= max->math->cos[(unsigned short)(max->map->p.orientation - max->map->p.ray[r].ra)];
// 			//ft_printf("L2 %Lx\n", max->map->p.ray[r].length);
// 			length /= 65536;
// 			fake_length /= 65536;
// 			//ft_printf("L3 %Lx\n", max->map->p.ray[r].length);
// 		}
// 		//ft_printf("b\n");
// 		//ft_printf("%i\n", wall_height);
// 		fake_wall_height = 65536 * SCREENHEIGHT / fake_length;
// 		wall_height = 65536 * SCREENHEIGHT / length;
// 		//ft_printf("wall: %i %i\n", wall_height, fake_wall_height);
// 		//ft_printf("c\n");
// 		// if (wall_height > SCREENHEIGHT)
// 		// 	wall_height = SCREENHEIGHT;
// 		if (length > MAXDIST || !max->map->p.ray[r].wall)
// 			wall_height = 0;
// 		offset = SCREENHEIGHT / 2 - wall_height / 2;
// 		fake_offset = SCREENHEIGHT / 2 - fake_wall_height / 2;
// 		//ft_printf("offset: %i %i\n", offset, fake_offset);
// 		while (y < SCREENHEIGHT)
// 		{
// 			if (y < offset && y < fake_offset)
// 			{
// 				//mlx_put_pixel(max->screen, x, y, 0x000000FF);
// 				//mlx_put_pixel(max->screen, x, y, max->map->c.rgba);
// 				// if (x == 512)
// 				// 	ft_get_colour3(max, max->map->c.rgba, y, fake_offset);
// 				mlx_put_pixel(max->screen, x, y, ft_get_colour2(max, max->map->c.rgba, y, fake_offset));
// 			}
// 			else if (y > offset && y < wall_height + offset)
// 			{
// 				//ft_printf("AAAAAA\n");
// 				//mlx_put_pixel(max->screen, x, y, max->map->p.ray[r].c[1]);
// 				if (max->map->p.ray[r].wall & NWALL)
// 				{
// 					//mlx_put_pixel(max->screen, x, y, ft_get_colour(x / 4, 1920 / 4, y - offset, wall_height, max->t->nwall));

// 					mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map->p.ray[r].rx % 65536, max->map->p.ray[r].length, y - offset, wall_height, max->t->nwall));
// 				}
// 				else if (max->map->p.ray[r].wall & EWALL)
// 					mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map->p.ray[r].ry % 65536, max->map->p.ray[r].length, y - offset, wall_height, max->t->ewall));
// 				else if (max->map->p.ray[r].wall & SWALL)
// 					mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map->p.ray[r].rx % 65536, max->map->p.ray[r].length, y - offset, wall_height, max->t->swall));
// 				else if (max->map->p.ray[r].wall & WWALL)
// 					mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map->p.ray[r].ry % 65536, max->map->p.ray[r].length, y - offset, wall_height, max->t->wwall));
// 				else
// 					mlx_put_pixel(max->screen, x, y, 0xFF00FFFF);
// 			}
// 			else if (y < fake_wall_height + fake_offset)
// 			{
// 				mlx_put_pixel(max->screen, x, y, max->map->b.rgba);
// 			}
// 			else
// 			{
// 				//mlx_put_pixel(max->screen, x, y, 0x000000FF);
// 				//mlx_put_pixel(max->screen, x, y, max->map->f.rgba);
// 				mlx_put_pixel(max->screen, x, y, ft_get_colour2(max, max->map->f.rgba, y, fake_offset));

// 			}
// 			++y;
// 		}
// 		++x;
// 	}
// }

void	ft_move_player(t_map *map, int y, int x)
{
	//ft_printf ("%x %x %x %x %x\n",y >> 8, x >> 8, map->m[((y >> 8) * map->w + (x >> 8))], WALL);
	//ft_printf("moving player\n");
	if (map->m[((y >> 16) * map->w + (x >> 16))] & WALL)
	{
		//ft_printf("You are in a wall\n");
		return ;
	}
	else
	{
		map->p.y = y;
		map->p.x = x;
		// if (map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
		// {
		// 	if (y < ((map->p.my << 8) | WALLDISTANCE))
		// 		map->p.sy = WALLDISTANCE;
		// }
		// if (map->m[map->p.my * map->w + map->p.mx] & FLOORWNW
		// 	&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
		// 	&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWW))
		// {
		// 	if (y < ((map->p.my << 8) | WALLDISTANCE)
		// 		&& x < ((map->p.mx << 8) | WALLDISTANCE))
		// 	{
		// 		if ((x & 0xFF) <= (y & 0xFF))
		// 			map->p.sy = WALLDISTANCE;
		// 		if ((y & 0xFF) <= (x & 0xFF))
		// 			map->p.sx = WALLDISTANCE;
		// 	}
		// }
		// if (map->m[map->p.my * map->w + map->p.mx] & FLOORWNE
		// 	&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
		// 	&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWE))
		// {
		// 	if (y < ((map->p.my << 8) | WALLDISTANCE)
		// 		&& x > ((map->p.mx << 8) | (256 - WALLDISTANCE)))
		// 	{
		// 		if (((256 - x) & 0xFF) <= (y & 0xFF))
		// 			map->p.sy = WALLDISTANCE;
		// 		if ((y & 0xFF) <= ((256 - x) & 0xFF))
		// 			map->p.sx = 256 - WALLDISTANCE;
		// 	}
		// }
		// if (map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
		// {
		// 	if (y > ((map->p.my << 8) | (256 - WALLDISTANCE)))
		// 		map->p.sy = 256 - WALLDISTANCE;
		// }
		// if (map->m[map->p.my * map->w + map->p.mx] & FLOORWSW
		// 	&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
		// 	&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWW))
		// {
		// 	if (y > ((map->p.my << 8) | (256 - WALLDISTANCE))
		// 		&& x < ((map->p.mx << 8) | WALLDISTANCE))
		// 	{
		// 		if ((x & 0xFF) <= ((256 - y) & 0xFF))
		// 			map->p.sy = 256 - WALLDISTANCE;
		// 		if (((256 - y) & 0xFF) <= (x & 0xFF))
		// 			map->p.sx = WALLDISTANCE;
		// 	}
		// }
		// if (map->m[map->p.my * map->w + map->p.mx] & FLOORWSE
		// 	&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
		// 	&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWE))
		// {
		// 	if (y > ((map->p.my << 8) | (256 - WALLDISTANCE))
		// 		&& x > ((map->p.mx << 8) | (256 - WALLDISTANCE)))
		// 	{
		// 		if (((256 - x) & 0xFF) <= ((256 - y) & 0xFF))
		// 			map->p.sy = 256 - WALLDISTANCE;
		// 		if (((256 - y) & 0xFF) <= ((256 - x) & 0xFF))
		// 			map->p.sx = 256 - WALLDISTANCE;
		// 	}
		// }
		// if (map->m[map->p.my * map->w + map->p.mx] & FLOORWW)
		// {
		// 	if (x < ((map->p.mx << 8) | WALLDISTANCE))
		// 		map->p.sx = WALLDISTANCE;
		// }
		// if (map->m[map->p.my * map->w + map->p.mx] & FLOORWE)
		// {
		// 	if (x > ((map->p.mx << 8) | (256 - WALLDISTANCE)))
		// 		map->p.sx = 256 - WALLDISTANCE;
		// }
		// ft_printf("moved player\n");
	}
}

void	ft_revisit_map(t_map *map)
{
	int	y;

	map->m[map->p.my * map->w + map->p.mx] |= VISITED;
	y = 0;
	while (y < map->hh * map->w)
	{
		if (map->m[y] & VISITED)
		{
			//ft_printf("old%Lx\n", map->m[y]);
			map->m[y] -= (VISIT);
			//ft_printf("new%Lx\n", map->m[y]);
		}
		++y;
	}
}

//hook for moving player on the map
//create hook for moving map instead of player
int	magic_test = 1;
void	ft_hook(void *param)
{
	t_max	*max;

	max = param;
	max->map->p.orientation += magic_test;
	max->newms = ft_get_time_in_ms();
	max->framems = (unsigned int)(max->newms - max->oldms);
	//ft_printf("framems: %u\n", max->framems);
	// Add some max speed to prevent running through walls.
	max->map->p.turnspeed = max->framems * 32;
	max->map->p.speed = MIN(4 * 8 * 128, 128 * 8 * max->framems);
	max->map->p.xspeed = (max->map->p.speed * max->math->cos[max->map->p.orientation]) / 65536;
	max->map->p.yspeed = -(max->map->p.speed * max->math->sin[max->map->p.orientation]) / 65536;
	++max->frame;
	max->oldms = max->newms;
	max->map->p.dx = -max->math->sin[max->map->p.orientation];
	max->map->p.dy = -max->math->cos[max->map->p.orientation];
	// size based on fov... maybe tangens? fov cannot be more than 180
	max->map->p.cx = max->math->cos[max->map->p.orientation];
	max->map->p.cy = max->math->sin[max->map->p.orientation];
	ft_snprintf(max->s, 255, "FPS: %3i   Pos [%4x] [%4x]   Orientation [%3i]",
		1000 / max->framems, max->map->p.x, max->map->p.y,
		max->map->p.orientation * 360 / 65536);
	mlx_delete_image(max->mlx, max->str);
	max->str = mlx_put_string(max->mlx, max->s, 10, 5);
	//ft_printf("test\n");
	if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
	{
		ft_printf("You have quit the game by pressing ESC.\n");
		mlx_close_window(max->mlx);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_SPACE))	//sprinting, faster but slower turns LIMIT STAMINA
	{
		//ft_printf("You have pressed space.\n");
		max->map->p.xspeed *= 2;
		max->map->p.yspeed *= 2;
		max->map->p.turnspeed /= 2;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_LEFT_SHIFT))	//sprinting, faster but slower turns LIMIT STAMINA
	{
		//ft_printf("You have pressed space.\n");
		max->map->p.xspeed *= 2;
		max->map->p.yspeed *= 2;
		max->map->p.turnspeed /= 2;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_UP) || mlx_is_key_down(max->mlx, MLX_KEY_W))
	{
		//ft_printf("You have pressed up arrow.\n");
		//ft_printf("xspeed %i | yspeed %i | orientation %i.\n", max->map->p.xspeed, max->map->p.yspeed, max->map->p.orientation);
		ft_move_player(max->map, max->map->p.y - max->map->p.xspeed, max->map->p.x - max->map->p.yspeed);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_DOWN) || mlx_is_key_down(max->mlx, MLX_KEY_S))
	{
		//ft_printf("You have pressed down arrow.\n");
		ft_move_player(max->map, max->map->p.y + max->map->p.xspeed, max->map->p.x + max->map->p.yspeed);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_A))
	{
		//ft_printf("You have pressed A.\n");
		ft_move_player(max->map, max->map->p.y + max->map->p.yspeed, max->map->p.x - max->map->p.xspeed);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_D))
	{
		//ft_printf("You have pressed D.\n");
		ft_move_player(max->map, max->map->p.y - max->map->p.yspeed, max->map->p.x + max->map->p.xspeed);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_LEFT) || mlx_is_key_down(max->mlx, MLX_KEY_Q))
	{
		//ft_printf("You have pressed left arrow.\n");
		//ft_printf("xspeed %i | yspeed %i | orientation %i.\n", max->map->p.xspeed, max->map->p.yspeed, max->map->p.orientation);
		max->map->p.orientation -= max->map->p.turnspeed;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(max->mlx, MLX_KEY_E))
	{
		//ft_printf("You have pressed right arrow.\n");
		max->map->p.orientation += max->map->p.turnspeed;
	}
	// if (mlx_is_key_down(max->mlx, MLX_KEY_M))
	// {
	// 	if (max->mmode < -32)
	// 		max->mmode = 1;
	// 	if (max->mmode > 32)
	// 		max->mmode = 0;
	// }
	//ft_printf("test0\n");
	if (!(max->frame % TICK))
		ft_revisit_map(max->map);
	
	//ft_printf("test1\n");
	ft_init_rays(max);
	ft_init_orays(max);
	//ft_draw_screen(max);
	// if (max->mmode > 0)
	// {
	// 	++max->mmode;
	// 	ft_draw_map(max);
	// }
	// else
	// {
	// 	--max->mmode;
	// 	ft_erase_map(max);
	// }
	//ft_printf("test2\n");
	ft_draw_map(max);
	//ft_draw_minimap(max);
}