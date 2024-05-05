/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen2dquad.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:38:28 by okraus            #+#    #+#             */
/*   Updated: 2024/04/15 11:34:00 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static int	ft_is_inside(t_map *map, long long rad2, int y, int x)
{
	long long	cx;
	long long	cy;

	cx = x - (int)map->p.x;
	cy = y - (int)map->p.y;
	if (cx * cx + cy * cy <= rad2)
	{
		return (1);
	}
	return (0);
}

static unsigned int	ft_get_wall_colour(t_max *max, int y, int x)
{
	unsigned int	c;

	y >>= 1;
	x >>= 1;
	c = max->t.supermapwall->pixels[y % 32 * 32 * 4 + x % 32 * 4 + 0] << 24 | 
		max->t.supermapwall->pixels[y % 32 * 32 * 4 + x % 32 * 4 + 1] << 16 |
		max->t.supermapwall->pixels[y % 32 * 32 * 4 + x % 32 * 4 + 2] << 8 |
		(max->t.supermapwall->pixels[y % 32 * 32 * 4 + x % 32 * 4 + 3] & 0);
	return (c);
}

static unsigned int	ft_get_floor_colour(t_max *max, int y, int x)
{
	unsigned int	c;

	y >>= 1;
	x >>= 1;
	c = max->t.supermapfloor->pixels[y % 32 * 32 * 4 + x % 32 * 4 + 0] << 24 | 
		max->t.supermapfloor->pixels[y % 32 * 32 * 4 + x % 32 * 4 + 1] << 16 |
		max->t.supermapfloor->pixels[y % 32 * 32 * 4 + x % 32 * 4 + 2] << 8 |
		(max->t.supermapfloor->pixels[y % 32 * 32 * 4 + x % 32 * 4 + 3] & 0);
	return (c);
}

static void	ft_put_quad_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	mlx_put_pixel(image, x, y, color);
	mlx_put_pixel(image, x + 1, y, color);
	mlx_put_pixel(image, x, y + 1, color);
	mlx_put_pixel(image, x + 1, y + 1, color);
}

void	ft_draw_screen2dquad(t_max *max)
{
	int	y;
	int	x;
	int	ny;
	int	nx;
	int	s; //scaling factor
	int	r;

	s = 6;
	y = 0;
	while (y < SUPERMAPHEIGHT)
	{
		x = 0;
		while (x < SUPERMAPWIDTH)
		{
			ny = y + (((int)max->map.p.y << s) >> 16) - max->map.p.smy;
			nx = x + (((int)max->map.p.x << s) >> 16) - max->map.p.smx;
			if (ny > 0 && nx > 0 && ny < max->map.h << s && nx < max->map.w << s)
			{
				if (ft_is_inside(&max->map, 268435456 * 2, (ny << 16) >> s, (nx << 16) >> s))
				{
					ft_put_quad_pixel(max->i.supermap, x, y, max->map.c.rgba & TMASK);	//player has ceiling colour
				}
				else if (max->map.m[(ny >> s) * max->map.w + (nx >> s)] & WALL)
				{
					ft_put_quad_pixel(max->i.supermap, x, y, (ft_get_wall_colour(max, ny, nx) | (0xFF & (max->map.m[(ny >> s) * max->map.w + (nx >> s)]) >> 32)) & TMASK);
				}
				else if (max->map.m[(ny >> s) * max->map.w + (nx >> s)] & FLOOR)
				{
					//ft_put_quad_pixel(max->supermap, x, y, ((max->map.m[(ny >> s) * max->map.w + (nx >> s)]) >> 32) & TMASK);
					ft_put_quad_pixel(max->i.supermap, x, y, (ft_get_floor_colour(max, ny, nx) | (0xFF & (max->map.m[(ny >> s) * max->map.w + (nx >> s)]) >> 32)) & TMASK);
				}
				else
				{
					ft_put_quad_pixel(max->i.supermap, x, y, 0x0 & TMASK);
				}
			}
			else //outside of map is transparent
				ft_put_quad_pixel(max->i.supermap, x, y, 0x0 & TMASK);
			x += 2;
		}
		y += 2;
	}

	r = 0;
	
	while (r < RAYS)
	{
		max->map.p.miniray[r].x[0] = max->map.p.smx;
		max->map.p.miniray[r].y[0] = max->map.p.smy;
		max->map.p.miniray[r].x[1] = max->map.p.smx + ((((max->map.p.oray[r].rx - max->map.p.oray[r].xs)) << s) >> 16);
		max->map.p.miniray[r].y[1] = max->map.p.smy + ((((max->map.p.oray[r].ry - max->map.p.oray[r].ys)) << s) >> 16);
		max->map.p.miniray[r].maxheight = SUPERMAPHEIGHT;
		max->map.p.miniray[r].maxwidth = SUPERMAPWIDTH;
		max->map.p.miniray[r].c[0] = max->map.p.oray[r].c[0];
		max->map.p.miniray[r].c[1] = max->map.p.oray[r].c[1];
		ft_place_line(max->i.supermap, max->map.p.miniray[r]);
		++r;
	}
	if (max->settings.debugging)
	{
		max->map.p.miniray[max->ray].c[0] = 0XFF00FFFF & TMASK;
		ft_place_line(max->i.supermap, max->map.p.miniray[max->ray]);
	}
}

