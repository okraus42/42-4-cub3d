/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:17:52 by okraus            #+#    #+#             */
/*   Updated: 2024/04/19 13:35:08 by okraus           ###   ########.fr       */
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
// void	ft_put_flamingo_in_map(t_max *max, t_sprite *flamingo)
// {
// 	int	x;
// 	int	y;
// 	int	i;
// 	int	j;
// 	int	s;

// 	s = MIN(MAPWIDTH / max->map.ww, MAPHEIGHT / max->map.hh);
// 	x = (flamingo->x >> 16) * s - s / 2;
// 	y = (flamingo->y >> 16) * s - s / 2;
// 	i = 0;
// 	while (i < s)
// 	{
// 		j = 0;
// 		while (j < s)
// 		{
// 			mlx_put_pixel(max->i.maximap, x + i, y + j, 0xFF80FFFF & TMASK);
// 			++j;
// 		}
// 		++i;
// 	}
// }

void	ft_draw_map(t_max *max)
{
	int	y;
	int	x;
	int	s; //scaling factor
	int	r;


	s = MIN(MAPWIDTH / max->map.ww, MAPHEIGHT / max->map.hh);
	y = 0;
	while (y < MAPHEIGHT)
	{
		x = 0;
		while (x < MAPWIDTH)
		{
			if (y < max->map.h * s && x < max->map.w * s)
			{
				if (ft_is_inside(&max->map, 268435456 * 2, (y << 16) / s, (x << 16) / s))
				{
					//ft_printf("y= %i, x= %i\n", y, x);
					mlx_put_pixel(max->i.maximap, x, y, max->map.c.rgba & TMASK);	//player has ceiling colour
				}
				else
				{
					mlx_put_pixel(max->i.maximap, x, y, ((max->map.m[(y / s) * max->map.w + (x / s)]) >> 32) & TMASK);
				}
			}
			else
				mlx_put_pixel(max->i.maximap, x, y, 0x808080FF & TMASK);
			++x;
		}
		++y;
	}
	// int	i;
	// i = 0;
	// while (i < max->map.spritecount)
	// {
	// 	if (max->map.sprites[i].state)
	// 	{
	// 		if (max->map.sprites[i].type == SPRITE_FLAMINGO)
	// 			ft_put_flamingo_in_map(max, &max->map.sprites[i]);
	// 	}
	// 	++i;
	// }
	r = 0;
	while (r < RAYS)
	{
		max->map.p.mapray[r].x[0] = (max->map.p.oray[r].xs * s) >> 16;
		max->map.p.mapray[r].y[0] = (max->map.p.oray[r].ys * s) >> 16;
		max->map.p.mapray[r].x[1] = (max->map.p.oray[r].rx * s) >> 16;
		max->map.p.mapray[r].y[1] = (max->map.p.oray[r].ry * s) >> 16;
		max->map.p.mapray[r].maxheight = MAPHEIGHT;
		max->map.p.mapray[r].maxwidth = MAPWIDTH;
		max->map.p.mapray[r].c[0] = max->map.p.oray[r].c[0] & TMASK;
		max->map.p.mapray[r].c[1] = max->map.p.oray[r].c[1] & TMASK;
		//ft_printf("%x\n", max->map.p.mapray[r].c[0]);
		ft_place_line(max->i.maximap, max->map.p.mapray[r]);
		++r;
	}
	if (max->settings.debugging)
	{
		max->map.p.mapray[max->ray].c[0] = 0XFF00FFFF & TMASK;
		max->map.p.mapray[max->ray].c[1] = 0XFF00FFFF & TMASK;
		if(max->ray > 10)
		{
			max->map.p.mapray[max->ray - 1].c[0] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 2].c[0] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 3].c[0] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 4].c[0] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 5].c[0] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 6].c[0] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 7].c[0] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 8].c[0] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 9].c[0] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 1].c[1] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 2].c[1] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 3].c[1] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 4].c[1] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 5].c[1] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 6].c[1] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 7].c[1] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 8].c[1] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray - 9].c[1] = 0X00FFFFFF & TMASK;
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray - 1]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray - 2]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray - 3]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray - 4]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray - 5]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray - 6]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray - 7]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray - 8]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray - 9]);
		}
		if(max->ray < RAYS - 10)
		{
					max->map.p.mapray[max->ray - 1].c[0] = 0X00FFFFFF & TMASK;
			max->map.p.mapray[max->ray + 2].c[0] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 3].c[0] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 4].c[0] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 5].c[0] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 6].c[0] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 7].c[0] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 8].c[0] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 9].c[0] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 1].c[1] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 2].c[1] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 3].c[1] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 4].c[1] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 5].c[1] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 6].c[1] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 7].c[1] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 8].c[1] = 0X0000FFFF & TMASK;
			max->map.p.mapray[max->ray + 9].c[1] = 0X0000FFFF & TMASK;
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray + 1]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray + 2]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray + 3]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray + 4]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray + 5]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray + 6]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray + 7]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray + 8]);
			ft_place_line(max->i.maximap, max->map.p.mapray[max->ray + 9]);
		}
		ft_place_line(max->i.maximap, max->map.p.mapray[max->ray]);
	}
}