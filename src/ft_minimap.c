/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:53:41 by okraus            #+#    #+#             */
/*   Updated: 2024/04/12 12:01:45 by okraus           ###   ########.fr       */
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
			ny = y + ((int)max->map.p.y * s / 65536) - MINIHEIGHT / 2;
			nx = x + ((int)max->map.p.x * s / 65536) - MINIWIDTH / 2;
			if (ny > 0 && nx > 0 && ny < max->map.h * s && nx < max->map.w * s)
			{
				if (ft_is_inside(&max->map, 268435456 * 2, (ny << 16) / s, (nx << 16) / s))
				{
					mlx_put_pixel(max->i.minimap, x, y, max->map.c.rgba & TMASK);	//player has ceiling colour
				}
				else
				{
					mlx_put_pixel(max->i.minimap, x, y, ((max->map.m[(ny / s) * max->map.w + (nx / s)]) >> 32) & TMASK);
				}
			}
			else
				mlx_put_pixel(max->i.minimap, x, y, 0x808080FF & TMASK);
			++x;
		}
		++y;
	}

	r = 0;
	
	while (r < RAYS)
	{
		max->map.p.miniray[r].x[0] = MINIWIDTH / 2;
		max->map.p.miniray[r].y[0] = MINIHEIGHT / 2;
		max->map.p.miniray[r].x[1] = MINIWIDTH / 2 + ((((max->map.p.oray[r].rx - max->map.p.oray[r].xs)) * s) >> 16);
		max->map.p.miniray[r].y[1] = MINIHEIGHT / 2 + ((((max->map.p.oray[r].ry - max->map.p.oray[r].ys)) * s) >> 16);
		max->map.p.miniray[r].maxheight = MINIHEIGHT;
		max->map.p.miniray[r].maxwidth = MINIWIDTH;
		max->map.p.miniray[r].c[0] = max->map.p.oray[r].c[0];
		max->map.p.miniray[r].c[1] = max->map.p.oray[r].c[1];
		ft_place_line(max->i.minimap, max->map.p.miniray[r]);
		++r;
	}
	if (DEBUGGING)
	{
		max->map.p.miniray[max->ray].c[0] = 0XFF00FFFF & TMASK;
		ft_place_line(max->i.minimap, max->map.p.miniray[max->ray]);
	}
}

