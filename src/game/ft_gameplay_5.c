/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameplay_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:39 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/10 13:22:22 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_init_wc(t_wallcheck *wc, int y, int x)
{
	wc->x = x;
	wc->y = y;
	wc->ny = y - WALLDISTANCE;
	wc->sy = y + WALLDISTANCE;
	wc->ex = x - WALLDISTANCE;
	wc->wx = x + WALLDISTANCE;
}

int	ft_is_wall(t_map *map, int x, int y)
{
	int	mx;
	int	my;
	int	mp;

	mx = x >> 16;
	my = y >> 16;
	mp = my * map->w + mx;
	if (map->m[mp] & WALL)
		return (1);
	return (0);
}

void	ft_move_player_2(t_map *map, int oldx, int oldy)
{
	map->p.smx += ((int)map->p.x - oldx) / 1024;
	map->p.smy += ((int)map->p.y - oldy) / 1024;
	if (map->p.smx < SUPERMAPBORDER)
		map->p.smx = SUPERMAPBORDER;
	if (map->p.smx > SUPERMAPWIDTH - SUPERMAPBORDER)
		map->p.smx = SUPERMAPWIDTH - SUPERMAPBORDER;
	if (map->p.smy < SUPERMAPBORDER)
		map->p.smy = SUPERMAPBORDER;
	if (map->p.smy > SUPERMAPHEIGHT - SUPERMAPBORDER)
		map->p.smy = SUPERMAPHEIGHT - SUPERMAPBORDER;
}

void	ft_revisit_map(t_map *map)
{
	int	y;

	map->m[map->p.my * map->w + map->p.mx] |= VISITED;
	y = 0;
	while (y < map->hh * map->w)
	{
		if (map->m[y] & VISITED)
			map->m[y] -= (VISIT);
		++y;
	}
}

void	ft_discover_full_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->ww * map->hh)
	{
		map->m[(i / map->ww) * 256 + i % map->ww] |= 0X8F00000000;
		++i;
	}
}
