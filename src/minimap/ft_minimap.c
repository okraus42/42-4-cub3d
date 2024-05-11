/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:53:41 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 15:25:20 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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

void	ft_draw_minimap_2_1(t_max *max, t_dminmap *dmmp)
{
	dmmp->ny = dmmp->y + ((int)max->map.p.y
			* dmmp->s / 65536) - MINIHEIGHT / 2;
	dmmp->nx = dmmp->x + ((int)max->map.p.x
			* dmmp->s / 65536) - MINIWIDTH / 2;
}

void	ft_draw_minimap_2(t_max *max, t_dminmap dmmp)
{
	while (dmmp.y < MINIHEIGHT)
	{
		dmmp.x = 0;
		while (dmmp.x < MINIWIDTH)
		{
			ft_draw_minimap_2_1(max, &dmmp);
			if (dmmp.ny > 0 && dmmp.nx > 0 && dmmp.ny < max->map.h
				* dmmp.s && dmmp.nx < max->map.w * dmmp.s)
			{
				if (ft_is_inside(&max->map, 268435456 * 2,
						(dmmp.ny << 16) / dmmp.s, (dmmp.nx << 16) / dmmp.s))
					mlx_put_pixel(max->i.minimap, dmmp.x, dmmp.y,
						max->map.c.rgba & TMASK);
				else
					mlx_put_pixel(max->i.minimap, dmmp.x, dmmp.y,
						((max->map.m[(dmmp.ny / dmmp.s) * max->map.w
								+ (dmmp.nx / dmmp.s)]) >> 32) & TMASK);
			}
			else
				mlx_put_pixel(max->i.minimap, dmmp.x, dmmp.y, 0x0 & TMASK);
			++dmmp.x;
		}
		++dmmp.y;
	}
}

void	ft_draw_minimap_3(t_max *max)
{
	if (max->settings.debugging)
	{
		max->map.p.miniray[max->ray].c[0] = 0XFF00FFFF & TMASK;
		ft_place_line(max->i.minimap, max->map.p.miniray[max->ray]);
	}
}

void	ft_draw_minimap(t_max *max)
{
	t_dminmap	dmmp;

	dmmp.s = 8;
	dmmp.y = 0;
	ft_draw_minimap_2(max, dmmp);
	dmmp.r = 0;
	while (dmmp.r < RAYS)
	{
		max->map.p.miniray[dmmp.r].x[0] = MINIWIDTH / 2;
		max->map.p.miniray[dmmp.r].y[0] = MINIHEIGHT / 2;
		max->map.p.miniray[dmmp.r].x[1] = MINIWIDTH / 2
			+ ((((max->map.p.oray[dmmp.r].rx - max->map.p
							.oray[dmmp.r].xs)) * dmmp.s) >> 16);
		max->map.p.miniray[dmmp.r].y[1] = MINIHEIGHT / 2
			+ ((((max->map.p.oray[dmmp.r].ry - max->map.p
							.oray[dmmp.r].ys)) * dmmp.s) >> 16);
		max->map.p.miniray[dmmp.r].maxheight = MINIHEIGHT;
		max->map.p.miniray[dmmp.r].maxwidth = MINIWIDTH;
		max->map.p.miniray[dmmp.r].c[0] = max->map.p.oray[dmmp.r].c[0];
		max->map.p.miniray[dmmp.r].c[1] = max->map.p.oray[dmmp.r].c[1];
		ft_place_line(max->i.minimap, max->map.p.miniray[dmmp.r]);
		++dmmp.r;
	}
	ft_draw_minimap_3(max);
}
