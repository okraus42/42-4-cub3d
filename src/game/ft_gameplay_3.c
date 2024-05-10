/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameplay_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:22 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/10 13:24:53 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

static int	ft_is_inside(t_map *map, long long rad2, long long y, long long x)
{
	long long	cx;
	long long	cy;

	cx = x - map->p.x;
	cy = y - map->p.y;
	if (cx * cx + cy * cy <= rad2)
	{
		return (1);
	}
	return (0);
}

void	ft_discover_map(t_map *map)
{
	int			i;
	long long	mx;
	long long	my;
	long long	rad2;
	long long	vis;

	vis = (long long)(0xFF / ((map->p.reveal / 4) + 1)) << 32;
	i = 0;
	rad2 = map->p.reveal * 65536;
	rad2 *= rad2;
	while (i < map->hh * map->ww)
	{
		my = (i / map->ww) * 65536 + 32768;
		mx = i % map->ww * 65536 + 32768;
		if (ft_is_inside(map, rad2, my, mx))
			map->m[(i / map->ww) * 256 + i % map->ww] |= vis;
		++i;
	}
}

void	ft_draw_strings_2(t_max *max)
{
	if (max->keys[MLX_KEY_2])
	{
		++max->ray;
		max->keys[MLX_KEY_2] = 0;
	}
	if (max->keys[MLX_KEY_3])
	{
		--max->ray;
		max->keys[MLX_KEY_3] = 0;
	}
	if (max->ray == RAYS)
		max->ray = 0;
	if (max->ray < 0)
		max->ray = RAYS - 1;
	ft_snprintf(max->overlay.rayinfo.str, 255,
		"Ray [%4i] ra [%5i] c0[%8x] c1[%8x] length[%Li]", max->ray,
		max->map.p.oray[max->ray].ra, max->map.p.oray[max->ray].c[0],
		max->map.p.oray[max->ray].c[1], max->map.p.oray[max->ray].length);
	ft_snprintf(max->overlay.basicinfo.str, 255,
		"FPS: %3i  Pos [%6x] [%6x]   Orientation [%5i]",
		1000 / max->framems, max->map.p.x, max->map.p.y,
		max->map.p.orientation);
}

void	ft_draw_strings_3(t_max *max)
{
	ft_snprintf(max->overlay.basicinfo.str, 255,
		"FPS: %3i   Pos [%6x] [%6x]   Orientation [%3i]",
		1000 / max->framems, max->map.p.x, max->map.p.y,
		max->map.p.orientation * 360 / MAXDEGREE);
	ft_snprintf(max->overlay.playerinfo.str, 255,
		"Name [%-10.10s] Coalition [%-10.10s] Campus[%-10.10s]",
		max->name, max->coalition, max->campus);
	ft_snprintf(max->overlay.gameplayinfo.str, 255,
		"Level[%2i] Score [%10i] Flamingos[%3i/%3i]",
		max->level, max->score,
		max->map.total_sprite[SPRITE_FLAMINGO]
		- max->map.current_sprite[SPRITE_FLAMINGO],
		max->map.total_sprite[SPRITE_FLAMINGO]);
	ft_snprintf(max->overlay.timeinfo.str, 255,
		"timelvl[%3i/%3i] time game[%3i/%3i]",
		max->levelms / 1000, max->limitms / 1000,
		(max->gamems + max->levelms) / 1000, max->timetriallimitms / 1000);
}

void	ft_draw_strings(t_max *max)
{
	if (max->settings.debugging)
		ft_draw_strings_2(max);
	else
		ft_draw_strings_3(max);
	ft_draw_text(&max->overlay.basicinfo, 0);
	ft_draw_text(&max->overlay.rayinfo, 0);
	ft_draw_text(&max->overlay.playerinfo, 0);
	ft_draw_text(&max->overlay.gameplayinfo, 0);
	ft_draw_text(&max->overlay.timeinfo, 0);
}
