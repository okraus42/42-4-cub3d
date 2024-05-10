/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameplay_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:07 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/10 13:18:36 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_move_player_3(t_map *map, t_wallcheck wc)
{
	if (ft_is_wall(map, wc.x, wc.ny))
		map->p.sy = WALLDISTANCE;
	if (ft_is_wall(map, wc.x, wc.sy))
		map->p.sy = SQUARESIZE - WALLDISTANCE;
	if (ft_is_wall(map, wc.wx, wc.y))
		map->p.sx = SQUARESIZE - WALLDISTANCE;
	if (ft_is_wall(map, wc.ex, wc.y))
		map->p.sx = WALLDISTANCE;
}

int	ft_move_player_4_1(t_map *map, int y, int x)
{
	int	r;

	r = 1;
	if (map->p.sy < SQUAREHALF)
	{
		if ((map->doors[((y >> 16) * map->w + (x >> 16))]
				& 0x7F) > 0)
		{
			map->p.sy = SQUARESIZE - 1;
			map->p.my -= 1;
		}
	}
	else
		r = 0;
	return (r);
}

int	ft_move_player_4(t_map *map, int y, int x)
{
	int	r;

	r = 1;
	if (map->m[((y >> 16) * map->w + (x >> 16))] & DOOR)
	{
		if (map->m[((y >> 16) * map->w + (x >> 16))] & DOOREW)
		{
			if (ft_move_player_4_1(map, y, x))
			{
			}
			else
			{
				if ((map->doors[((y >> 16) * map->w + (x >> 16))]
						& 0x7F) > 0)
				{
					map->p.sy = 0;
					map->p.my += 1;
				}
			}
		}
	}
	else
		r = 0;
	return (r);
}

void	ft_move_player_5(t_map *map, int y, int x)
{
	if (map->p.sx < SQUAREHALF)
	{
		if ((map->doors[((y >> 16) * map->w + (x >> 16))]
				& 0x7F) > 0)
		{
			map->p.sx = SQUARESIZE - 1;
			map->p.mx -= 1;
		}
	}
	else
	{
		if ((map->doors[((y >> 16) * map->w + (x >> 16))]
				& 0x7F) > 0)
		{
			map->p.sx = 0;
			map->p.mx += 1;
		}
	}
}

void	ft_move_player(t_map *map, int y, int x)
{
	int			oldy;
	int			oldx;
	t_wallcheck	wc;

	if (map->m[((y >> 16) * map->w + (x >> 16))] & WALL)
		return ;
	else
	{
		oldy = map->p.y;
		oldx = map->p.x;
		map->p.y = y;
		map->p.x = x;
		ft_init_wc(&wc, y, x);
		ft_move_player_3(map, wc);
		if (ft_move_player_4(map, y, x))
		{
		}
		else if (map->m[((y >> 16) * map->w + (x >> 16))] & DOORNS)
			ft_move_player_5(map, y, x);
	}
	ft_move_player_2(map, oldx, oldy);
}
