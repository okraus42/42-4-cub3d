/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:17:52 by okraus            #+#    #+#             */
/*   Updated: 2024/02/11 16:40:29 by okraus           ###   ########.fr       */
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

void	ft_draw_map(t_max *max)
{
	int	y;
	int	x;
	
	int	s; //scaling factor
	int	r;


	s = MIN(MAPWIDTH / max->map->ww, MAPHEIGHT / max->map->hh);
	y = 0;
	while (y < MAPHEIGHT)
	{
		x = 0;
		while (x < MAPWIDTH)
		{
			if (y < max->map->h * s && x < max->map->w * s)
			{
				if (ft_is_inside(max->map, 2147483648LL, (y << 16) / s, (x << 16) / s))
				{
					//ft_printf("y= %i, x= %i\n", y, x);
					mlx_put_pixel(max->maximap, x, y, max->map->c.rgba & TMASK);	//player has ceiling colour
				}
				else
				{
					mlx_put_pixel(max->maximap, x, y, ((max->map->m[(y / s) * max->map->w + (x / s)]) >> 32) & TMASK);
				}
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
		max->map->p.mapray[r].x[0] = (max->map->p.oray[r].xs * s) >> 16;
		max->map->p.mapray[r].y[0] = (max->map->p.oray[r].ys * s) >> 16;
		max->map->p.mapray[r].x[1] = (max->map->p.oray[r].rx * s) >> 16;
		max->map->p.mapray[r].y[1] = (max->map->p.oray[r].ry * s) >> 16;
		max->map->p.mapray[r].maxheight = MAPHEIGHT;
		max->map->p.mapray[r].maxwidth = MAPWIDTH;
		max->map->p.mapray[r].c[0] = max->map->p.oray[r].c[0] & TMASK;
		max->map->p.mapray[r].c[1] = max->map->p.oray[r].c[1] & TMASK;
		//ft_printf("%x\n", max->map->p.mapray[r].c[0]);
		ft_place_line(max->maximap, max->map->p.mapray[r]);
		++r;
	}
}