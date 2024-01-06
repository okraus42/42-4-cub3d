/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:08:20 by okraus            #+#    #+#             */
/*   Updated: 2024/01/06 12:44:22 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_big_swap(int a[3], int b[3], unsigned int c[2])
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

unsigned int	ft_mix_colour(int x[3], int y[3], unsigned int c[2])
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
void	ft_plot_line_low(mlx_image_t *img, t_ray l)
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

void	ft_plot_line_high(mlx_image_t *img, t_ray l)
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

int	ft_is_inside(t_map *map, unsigned long rad2, int y, int x)
{
	unsigned long	cx;
	unsigned long	cy;

	cx = x - (int)map->p.x;
	cy = y - (int)map->p.y;
	if (cx * cx + cy * cy <= rad2)
	{
		// if (y > 100 && x > 200)
		// 	ft_printf("y %i x %i cx %i cy %i\n", y, x, cx, cy);
		return (1);
	}
	return (0);
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

int	ft_test(t_ray *ray)
{
	ray->hl = (ray->hx - ray->xs) * (ray->hx - ray->xs) + (ray->hy - ray->ys) * (ray->hy - ray->ys);
	ray->vl = (ray->vx - ray->xs) * (ray->vx - ray->xs) + (ray->vy - ray->ys) * (ray->vy - ray->ys);
	ray->length = MIN(ray->hl, ray->vl);
	if (ray->hl > ray->vl)
		return (1);
	else
		return (0);
}

void	ft_init_rays(t_max *max)
{
	// long long	xs; //ray starting position 65536 is 1.000
	// long long	ys;
	// long long	hx;
	// long long	hy;
	// long long	vx;
	// long long	vy;
	// long long	rx;	//ray final position
	// long long	ry;
	// long long	xo;	//x and y offset
	// long long	yo;
	int	dof;
	int	mx;
	int	my;
	int	mp;
	int	r;
	long long	maxdist;
	t_ray	*ray;
		
	r = 0;
	while (r < RAYS)
	{	
		ray = &max->map->p.ray[r];
		ray->xs = ((int)max->map->p.x) * 256;
		ray->ys = ((int)max->map->p.y) * 256;
		ray->xo = 65536;
		ray->yo = 65536;
		ray->ra = max->map->p.orientation - max->map->p.fov2 + r * max->map->p.fov * 65536LL / (RAYS - 1) / 360;
		//ft_printf("%i, %i, %u\n", r, ray->ra, r * max->map->p.fov * 65536U);
		// rx = (((int)max->map->p.x - max->math->sin[ray->ra] / 16)) * 256;
		// ry = (((int)max->map->p.y - max->math->cos[ray->ra] / 16)) * 256;
		dof = 0;
		if (ray->ra > WEST + 4 || ray->ra < EAST - 4)
		{
			ray->hy = ((ray->ys >> 16) << 16) - 1;
			ray->hx = (((ray->ys - ray->hy) * max->math->ntan[ray->ra]) >> 16) + ray->xs;
			// ft_printf("if1 %Lx %Lx %Lx %Lx\n", xs, ys, hx, hy);
			// ft_printf("if1 %Lx\n", max->math->ntan[ray->ra]);
			ray->xo = (65536 * max->math->ntan[ray->ra]) >> 16;
			ray->yo = -65536;
		}
		else if (ray->ra < WEST -4 && ray->ra > EAST + 4)
		{
			ray->hy = ((ray->ys >> 16) << 16) + 65536;
			ray->hx = (((ray->ys - ray->hy) * max->math->ntan[ray->ra]) >> 16) + ray->xs;
			// ft_printf("if2 %Lx %Lx %Lx %Lx\n", xs, ys, hx, hy);
			// ft_printf("if2 %x %Lx %Lx %Lx\n", max->math->ntan[ray->ra]);
			ray->xo = -((65536 * max->math->ntan[ray->ra]) >> 16); //check where to put minus and bitshifting
			ray->yo = 65536;
		}
		else
		{
			ray->hy = INT_MAX;
			ray->hx = INT_MAX;
			dof = DOF;
		}
		while (dof < DOF)
		{
			mx = ray->hx >> 16;
			my = ray->hy >> 16;
			// ft_printf("%x %x\n", mx, my);
			mp = (my << 8) + mx;
			if (mp > 0 && mp < 65536 && ((max->map->m[mp]) & WALL))
				dof = DOF;
			ray->hx += ray->xo;
			ray->hy += ray->yo;
			++dof;
		}
		ray->hx -= ray->xo;
		ray->hy -= ray->yo;
		dof = 0;
		if (ray->ra < SOUTH - 4 && ray->ra > NORTH + 4)
		{
			ray->vx = ((ray->xs >> 16) << 16) - 1;
			ray->vy = (((ray->xs - ray->vx) * max->math->atan[ray->ra]) >> 16) + ray->ys;
			// ft_printf("if1 %Lx %Lx %Lx %Lx\n", xs, ys, vx, vy);
			// ft_printf("if1 %Lx\n", max->math->atan[ray->ra]);
			ray->xo = -65536;
			ray->yo = (65536 * max->math->atan[ray->ra]) >> 16;
		}
		else if (ray->ra > SOUTH + 4 && ray->ra < (unsigned short)(NORTH - 4))
		{
			ray->vx = ((ray->xs >> 16) << 16) + 65536;
			ray->vy = (((ray->xs - ray->vx) * max->math->atan[ray->ra]) >> 16) + ray->ys;
			// ft_printf("if2 %Lx %Lx %Lx %Lx\n", xs, ys, vx, vy);
			// ft_printf("if2 %x %Lx %Lx %Lx\n", max->math->atan[ray->ra]);
			ray->xo = 65536;//check where to put minus and bitshifting
			ray->yo = -((65536 * max->math->atan[ray->ra]) >> 16);
		}
		//looking up or down
		else
		{
			ray->vy = INT_MAX;
			ray->vx = INT_MAX;
			dof = DOF;
		}
		while (dof < DOF)
		{
			mx = ray->vx >> 16;
			my = ray->vy >> 16;
			// ft_printf("%x %x\n", mx, my);
			mp = (my << 8) + mx;
			if (mp > 0 && mp < 65536 && ((max->map->m[mp]) & WALL))
				dof = DOF;
			ray->vx += ray->xo;
			ray->vy += ray->yo;
			++dof;
		}
		ray->vx -= ray->xo;
		ray->vy -= ray->yo;
		// ft_printf("%x %x\n", max->map->p.x, max->map->p.y);
		// ft_printf("%Lx %Lx %Lx %Lx\n", xs, ys, rx, ry);
		if (ft_test(ray))
		{
			ray->rx = ray->vx;
			ray->ry = ray->vy;
		}
		else
		{
			ray->rx = ray->hx;
			ray->ry = ray->hy;
		}
		// ft_printf("length: %Lx\n", ray->length);
		// ft_printf("ra: %hi\n", ray->ra);
		// ft_printf("rx: %Lx ry: %Lx\n", ray->rx, ray->ry);
		// ft_printf("hx: %Lx hy: %Lx\n", ray->hx, ray->hy);
		// ft_printf("vx: %Lx vy: %Lx\n", ray->vx, ray->vy);
		
		ray->c[0] = 0xFFFF00FF;
		maxdist = 2147483648 * DOF * DOF;
		if (ray->length > maxdist)
			ray->c[1] = 0x000000ff;
		else
		{
			ray->c1a = 0xff;
			ray->c1b = ray->c0b * (255 - (255 * ray->length / maxdist)) / 256;
			ray->c1g = ray->c0g * (255 - (255 * ray->length / maxdist)) / 256;
			ray->c1r = ray->c0r * (255 - (255 * ray->length / maxdist)) / 256;
		}
		// max->map->p.mapray[r].x[0] = ray->xs;
		// max->map->p.mapray[r].y[0] = ray->ys;
		// max->map->p.mapray[r].x[1] = ray->rx;
		// max->map->p.mapray[r].y[1] = ray->ry;
		// rx = vx;
		// ry = vy;
		// max->map->p.mapray[r].x[0] = (xs * s) >> 16;
		// max->map->p.mapray[r].y[0] = (ys * s) >> 16;
		// max->map->p.mapray[r].x[1] = (rx * s) >> 16;
		// max->map->p.mapray[r].y[1] = (ry * s) >> 16;
		// max->map->p.mapray[r].c[0] = 0xff0000ff;
		// max->map->p.mapray[r].c[1] = 0xff0000ff;
		// max->map->p.mapray[r].maxheight = MAPHEIGHT;
		// max->map->p.mapray[r].maxwidth = MAPWIDTH;
		// ft_place_line(max->maximap, max->map->p.mapray[r]);
		// ++r;
		// rx = hx;
		// ry = hy;
		// max->map->p.mapray[r].x[0] = (xs * s) >> 16;
		// max->map->p.mapray[r].y[0] = (ys * s) >> 16;
		// max->map->p.mapray[r].x[1] = (rx * s) >> 16;
		// max->map->p.mapray[r].y[1] = (ry * s) >> 16;
		// max->map->p.mapray[r].c[0] = 0xff0000ff;
		// max->map->p.mapray[r].c[1] = 0xff0000ff;
		// max->map->p.mapray[r].maxheight = MAPHEIGHT;
		// max->map->p.mapray[r].maxwidth = MAPWIDTH;
		// ft_place_line(max->maximap, max->map->p.mapray[r]);
		++r;
	}
}

void	ft_draw_map(t_max *max)
{
	int	y;
	int	x;
	
	int	s; //scaling factor
	int	r;


	s = MIN(1024 / max->map->ww, 1024 / max->map->hh);
	y = 0;
	while (y < MAPHEIGHT)
	{
		x = 0;
		while (x < MAPWIDTH)
		{
			if (y < max->map->h * s && x < max->map->w * s)
			{
				if (ft_is_inside(max->map, 4096, (y << 8) / s, (x << 8) / s))
				{
					//ft_printf("y= %i, x= %i\n", y, x);
					mlx_put_pixel(max->maximap, x, y, max->map->c.rgba & TMASK);	//player has ceiling colour
				}
				// else if (ft_is_inside2(max, 1024, (y << 8) / s, (x << 8) / s))
				// {
				// 	mlx_put_pixel(max->map, x, y, 0x00ff00ff & TMASK);	//green circle for the direction visualisation
				// }
				else if (max->map->m[(y / s) * max->map->w + (x / s)] & WALL)
					mlx_put_pixel(max->maximap, x, y, 0x000000FF & TMASK); //walls are black for now
				else if (max->map->m[(y / s) * max->map->w + (x / s)] & FLOOR)
					mlx_put_pixel(max->maximap, x, y, max->map->f.rgba & TMASK); //floor is the proper colour
				else
					mlx_put_pixel(max->maximap, x, y, 0x404040FF & TMASK);
			}
			else
				mlx_put_pixel(max->maximap, x, y, 0x808080FF & TMASK);
			++x;
		}
		++y;
	}
	r = 0;
	
	while (r < RAYS)
	{
		// ft_printf("x0 %x %Lx\n", max->map->p.mapray[r].x[0], max->map->p.ray[r].xs);
		// ft_printf("y0 %x %Lx\n", max->map->p.mapray[r].y[0], max->map->p.ray[r].ys);
		// ft_printf("x1 %x %Lx\n", max->map->p.mapray[r].x[1], max->map->p.ray[r].rx);
		// ft_printf("y1 %x %Lx\n", max->map->p.mapray[r].y[1], max->map->p.ray[r].ry);
		// max->map->p.mapray[r].x[0] = (max->map->p.mapray[r].x[0] * s) >> 16;
		// max->map->p.mapray[r].y[0] = (max->map->p.mapray[r].y[0] * s) >> 16;
		// max->map->p.mapray[r].x[1] = (max->map->p.mapray[r].x[1] * s) >> 16;
		// max->map->p.mapray[r].y[1] = (max->map->p.mapray[r].y[1] * s) >> 16;
		max->map->p.mapray[r].x[0] = (max->map->p.ray[r].xs * s) >> 16;
		max->map->p.mapray[r].y[0] = (max->map->p.ray[r].ys * s) >> 16;
		max->map->p.mapray[r].x[1] = (max->map->p.ray[r].rx * s) >> 16;
		max->map->p.mapray[r].y[1] = (max->map->p.ray[r].ry * s) >> 16;
		// ft_printf("x0 %x %Lx\n", max->map->p.mapray[r].x[0], (max->map->p.ray[r].xs * s) >> 16);
		// ft_printf("y0 %x %Lx\n", max->map->p.mapray[r].y[0], (max->map->p.ray[r].ys * s) >> 16);
		// ft_printf("x1 %x %Lx\n", max->map->p.mapray[r].x[1], (max->map->p.ray[r].rx * s) >> 16);
		// ft_printf("y1 %x %Lx\n", max->map->p.mapray[r].y[1], (max->map->p.ray[r].ry * s) >> 16);
		max->map->p.mapray[r].maxheight = MAPHEIGHT;
		max->map->p.mapray[r].maxwidth = MAPWIDTH;
		max->map->p.mapray[r].c[0] = max->map->p.ray[r].c[0];
		max->map->p.mapray[r].c[1] = max->map->p.ray[r].c[1];
		ft_place_line(max->maximap, max->map->p.mapray[r]);
		++r;
	}
	// max->map->p.xx[0] = ((int)max->map->p.x * s) >> 8;
	// max->map->p.yy[0] = ((int)max->map->p.y * s) >> 8;
	// max->map->p.xx[1] = (((int)max->map->p.x - max->math->sin[max->map->p.orientation] / 128) * s) >> 8;
	// max->map->p.yy[1] = (((int)max->map->p.y - max->math->cos[max->map->p.orientation] / 128) * s) >> 8;
	// max->map->p.xl[0] = ((int)max->map->p.x * s) >> 8;
	// max->map->p.yl[0] = ((int)max->map->p.y * s) >> 8;
	// max->map->p.xl[1] = (((int)max->map->p.x - max->math->sin[(unsigned short)(max->map->p.orientation + max->map->p.fov2)] / 64) * s) >> 8;
	// max->map->p.yl[1] = (((int)max->map->p.y - max->math->cos[(unsigned short)(max->map->p.orientation + max->map->p.fov2)] / 64) * s) >> 8;
	// max->map->p.xr[0] = ((int)max->map->p.x * s) >> 8;
	// max->map->p.yr[0] = ((int)max->map->p.y * s) >> 8;
	// max->map->p.xr[1] = (((int)max->map->p.x - max->math->sin[(unsigned short)(max->map->p.orientation - max->map->p.fov2)] / 64) * s) >> 8;
	// max->map->p.yr[1] = (((int)max->map->p.y - max->math->cos[(unsigned short)(max->map->p.orientation - max->map->p.fov2)] / 64) * s) >> 8;
	// ft_place_line(max->maximap, max->map->p.xx, max->map->p.yy, 0xff0000ff);
	// ft_place_line(max->maximap, max->map->p.xl, max->map->p.yl, 0xffff00ff);
	// ft_place_line(max->maximap, max->map->p.xr, max->map->p.yr, 0xffff00ff);
	// max->map->p.xd[0] = ((int)max->map->p.x * s) >> 8;
	// max->map->p.yd[0] = ((int)max->map->p.y * s) >> 8;
	// max->map->p.xd[1] = max->map->p.xd[0] + max->map->p.dx * s / 16384;
	// max->map->p.yd[1] = max->map->p.yd[0] + max->map->p.dy * s / 16384;
	// ft_place_line(max->maximap, max->map->p.xd, max->map->p.yd, 0x0000ffff);
	// max->map->p.xc[0] = max->map->p.xd[1];
	// max->map->p.yc[0] = max->map->p.yd[1];
	// max->map->p.xc[1] = max->map->p.xc[0] + max->map->p.cx * s / 16384;
	// max->map->p.yc[1] = max->map->p.yc[0] + max->map->p.cy * s / 16384;
	// ft_place_line(max->maximap, max->map->p.xc, max->map->p.yc, 0xff00ffff);
	// max->map->p.xn[0] = max->map->p.xd[1];
	// max->map->p.yn[0] = max->map->p.yd[1];
	// max->map->p.xn[1] = max->map->p.xn[0] - max->map->p.cx * s / 16384;
	// max->map->p.yn[1] = max->map->p.yn[0] - max->map->p.cy * s / 16384;
	// ft_place_line(max->maximap, max->map->p.xn, max->map->p.yn, 0xffa0ffff);
}

void	ft_draw_minimap(t_max *max)
{
	int	y;
	int	x;
	int	ny;
	int	nx;
	int	s; //scaling factor
	int	r;

	s = 8;
	y = 0;
	while (y < MINIHEIGHT)
	{
		x = 0;
		while (x < MINIWIDTH)
		{
			ny = y + ((int)max->map->p.y * s / 256) - MINIHEIGHT / 2;
			nx = x + ((int)max->map->p.x * s / 256) - MINIWIDTH / 2;
			if (ny > 0 && nx > 0 && ny < max->map->h * s && nx < max->map->w * s)
			{
				if (ft_is_inside(max->map, 4096, (ny << 8) / s, (nx << 8) / s))
				{
					//ft_printf("y= %i, x= %i\n", y, x);
					mlx_put_pixel(max->minimap, x, y, max->map->c.rgba & TMASK);	//player has ceiling colour
				}
				// else if (ft_is_inside2(max, 1024, (y << 8) / s, (x << 8) / s))
				// {
				// 	mlx_put_pixel(max->map, x, y, 0x00ff00ff & TMASK);	//green circle for the direction visualisation
				// }
				else if (max->map->m[(ny / s) * max->map->w + (nx / s)] & WALL)
					mlx_put_pixel(max->minimap, x, y, 0x000000FF & TMASK); //walls are black for now
				else if (max->map->m[(ny / s) * max->map->w + (nx / s)] & FLOOR)
					mlx_put_pixel(max->minimap, x, y, max->map->f.rgba & TMASK); //floor is the proper colour
				else
					mlx_put_pixel(max->minimap, x, y, 0x404040FF & TMASK);
			}
			else
				mlx_put_pixel(max->minimap, x, y, 0x808080FF & TMASK);
			++x;
		}
		++y;
	}

	r = 0;
	
	while (r < RAYS)
	{
		max->map->p.miniray[r].x[0] = MINIWIDTH / 2;
		max->map->p.miniray[r].y[0] = MINIHEIGHT / 2;
		max->map->p.miniray[r].x[1] = MINIWIDTH / 2 + ((((max->map->p.ray[r].rx - max->map->p.ray[r].xs)) * s) >> 16);
		max->map->p.miniray[r].y[1] = MINIHEIGHT / 2 + ((((max->map->p.ray[r].ry - max->map->p.ray[r].ys)) * s) >> 16);
		max->map->p.miniray[r].maxheight = MINIHEIGHT;
		max->map->p.miniray[r].maxwidth = MINIWIDTH;
		max->map->p.miniray[r].c[0] = max->map->p.ray[r].c[0];
		max->map->p.miniray[r].c[1] = max->map->p.ray[r].c[1];
		ft_place_line(max->minimap, max->map->p.miniray[r]);
		++r;
	}
	r = 0;
	
	// while (r < RAYS)
	// {	
	// 	max->map->p.miniray[r].x[0] = MINIWIDTH / 2;
	// 	max->map->p.miniray[r].y[0] = MINIHEIGHT / 2;
	// 	max->map->p.miniray[r].ra = max->map->p.orientation - max->map->p.fov2 + r * max->map->p.fov * 65536LL / (RAYS - 1) / 360;
	// 	max->map->p.miniray[r].x[1] = MINIWIDTH / 2 - (((max->math->sin[max->map->p.miniray[r].ra]) * s) / 8192);
	// 	max->map->p.miniray[r].y[1] = MINIHEIGHT / 2 - (((max->math->cos[max->map->p.miniray[r].ra]) * s) / 8192);
	// 	max->map->p.miniray[r].c[0] = 0xffff00ff;
	// 	max->map->p.miniray[r].c[1] = max->map->f.rgba;
	// 	max->map->p.miniray[r].maxheight = MINIHEIGHT;
	// 	max->map->p.miniray[r].maxwidth = MINIWIDTH;
	// 	ft_place_line(max->minimap, max->map->p.miniray[r]);
	// 	++r;
	// }
	// max->map->p.xl[0] = MINIWIDTH / 2;
	// max->map->p.yl[0] = MINIHEIGHT / 2;
	// max->map->p.xl[1] = MINIWIDTH / 2 - max->math->sin[(unsigned short)(max->map->p.orientation + max->map->p.fov2)] * s / 16384;
	// max->map->p.yl[1] = MINIHEIGHT / 2 - max->math->cos[(unsigned short)(max->map->p.orientation + max->map->p.fov2)] * s / 16384;
	// max->map->p.xr[0] = MINIWIDTH / 2;
	// max->map->p.yr[0] = MINIHEIGHT / 2;
	// max->map->p.xr[1] = MINIWIDTH / 2  - max->math->sin[(unsigned short)(max->map->p.orientation - max->map->p.fov2)] * s / 16384;
	// max->map->p.yr[1] = MINIHEIGHT / 2 - max->math->cos[(unsigned short)(max->map->p.orientation - max->map->p.fov2)] * s / 16384;
	// ft_place_line(max->minimap, max->map->p.xx, max->map->p.yy, 0xff0000ff);
	// ft_place_line(max->minimap, max->map->p.xl, max->map->p.yl, 0xffff00ff);
	// ft_place_line(max->minimap, max->map->p.xr, max->map->p.yr, 0xffff00ff);
	// max->map->p.xd[0] = MINIWIDTH / 2;;
	// max->map->p.yd[0] = MINIHEIGHT / 2;
	// max->map->p.xd[1] = max->map->p.xd[0] + max->map->p.dx * s / 16384;
	// max->map->p.yd[1] = max->map->p.yd[0] + max->map->p.dy * s / 16384;
	// ft_place_line(max->minimap, max->map->p.xd, max->map->p.yd, 0x0000ffff);
	// max->map->p.xc[0] = max->map->p.xd[1];
	// max->map->p.yc[0] = max->map->p.yd[1];
	// max->map->p.xc[1] = max->map->p.xc[0] + max->map->p.cx * s / 16384;
	// max->map->p.yc[1] = max->map->p.yc[0] + max->map->p.cy * s / 16384;
	// ft_place_line(max->minimap, max->map->p.xc, max->map->p.yc, 0xff00ffff);
	// max->map->p.xn[0] = max->map->p.xd[1];
	// max->map->p.yn[0] = max->map->p.yd[1];
	// max->map->p.xn[1] = max->map->p.xn[0] - max->map->p.cx * s / 16384;
	// max->map->p.yn[1] = max->map->p.yn[0] - max->map->p.cy * s / 16384;
	// ft_place_line(max->minimap, max->map->p.xn, max->map->p.yn, 0xffa0ffff);
}

void	ft_move_player(t_map *map, int y, int x)
{
	//ft_printf ("%x %x %x %x %x\n",y >> 8, x >> 8, map->m[((y >> 8) * map->w + (x >> 8))], WALL);
	if (map->m[((y >> 8) * map->w + (x >> 8))] & WALL)
	{
		//ft_printf("You are in a wall\n");
		return ;
	}
	else
	{
		map->p.y = y;
		map->p.x = x;
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
		{
			if (y < ((map->p.my << 8) | WALLDISTANCE))
				map->p.sy = WALLDISTANCE;
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWNW
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWW))
		{
			if (y < ((map->p.my << 8) | WALLDISTANCE)
				&& x < ((map->p.mx << 8) | WALLDISTANCE))
			{
				map->p.sy = WALLDISTANCE;
				map->p.sx = WALLDISTANCE;
			}
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWNE
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWE))
		{
			if (y < ((map->p.my << 8) | WALLDISTANCE)
				&& x > ((map->p.mx << 8) | (256 - WALLDISTANCE)))
			{
				map->p.sy = WALLDISTANCE;
				map->p.sx = 256 - WALLDISTANCE;
			}
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
		{
			if (y > ((map->p.my << 8) | (256 - WALLDISTANCE)))
				map->p.sy = 256 - WALLDISTANCE;
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWSW
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWW))
		{
			if (y > ((map->p.my << 8) | (256 - WALLDISTANCE))
				&& x < ((map->p.mx << 8) | WALLDISTANCE))
			{
				map->p.sy = 256 - WALLDISTANCE;
				map->p.sx = WALLDISTANCE;
			}
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWSE
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
			&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWE))
		{
			if (y > ((map->p.my << 8) | (256 - WALLDISTANCE))
				&& x > ((map->p.mx << 8) | (256 - WALLDISTANCE)))
			{
				map->p.sy = 256 - WALLDISTANCE;
				map->p.sx = 256 - WALLDISTANCE;
			}
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWW)
		{
			if (x < ((map->p.mx << 8) | WALLDISTANCE))
				map->p.sx = WALLDISTANCE;
		}
		if (map->m[map->p.my * map->w + map->p.mx] & FLOORWE)
		{
			if (x > ((map->p.mx << 8) | (256 - WALLDISTANCE)))
				map->p.sx = 256 - WALLDISTANCE;
		}
	}
}


//hook for moving player on the map
//create hook for moving map instead of player
void	ft_hook(void *param)
{
	t_max	*max;

	max = param;
	max->newms = ft_get_time_in_ms();
	max->framems = (unsigned int)(max->newms - max->oldms);
	//ft_printf("framems: %u\n", max->framems);
	// Add some max speed to prevent running through walls.
	max->map->p.turnspeed = max->framems * 64;
	max->map->p.speed = MIN(31, max->framems);
	max->map->p.xspeed = (max->map->p.speed * max->math->cos[max->map->p.orientation]) / 65536;
	max->map->p.yspeed = (max->map->p.speed * max->math->sin[max->map->p.orientation]) / 65536;
	++max->frame;
	max->oldms = max->newms;
	max->map->p.dx = -max->math->sin[max->map->p.orientation];
	max->map->p.dy = -max->math->cos[max->map->p.orientation];
	// size based on fov... maybe tangens? fov cannot be more than 180
	max->map->p.cx = max->math->cos[max->map->p.orientation];
	max->map->p.cy = -max->math->sin[max->map->p.orientation];
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
		max->map->p.orientation += max->map->p.turnspeed;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(max->mlx, MLX_KEY_E))
	{
		//ft_printf("You have pressed right arrow.\n");
		max->map->p.orientation -= max->map->p.turnspeed;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_M))
	{
		if (max->mmode < -32)
			max->mmode = 1;
		if (max->mmode > 32)
			max->mmode = 0;
	}
	ft_init_rays(max);
	if (max->mmode > 0)
	{
		++max->mmode;
		ft_draw_map(max);
	}
	else
	{
		--max->mmode;
		ft_erase_map(max);
	}
	ft_draw_minimap(max);
}