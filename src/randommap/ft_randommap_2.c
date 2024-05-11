/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:37:56 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 15:44:16 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_inittimetrialmap_seedinit(t_randommap *rm)
{
	if (!rm->seed)
	{
		rm->seed = time(0);
		srand(rm->seed);
	}
}

void	ft_inittimetrialmap(t_randommap *rm, int level)
{
	rm->width.value = 10 + 2 * level;
	rm->height.value = 5 + level;
	rm->ratiode.value = (rand() % 64) * (rand() % 8 + 1) * (rand() % 8 + 1);
	rm->ratiolo.value = (rand() % 16) * (rand() % 8 + 1) * (rand() % 4 + 1);
	rm->ratioti.value = (rand() % 8) * (rand() % 8 + 1);
	rm->ratioxi.value = (rand() % 2) * (rand() % 8 + 1);
	rm->rnorooms.value = (rm->width.value * rm->height.value / 64 + 1)
		* (rand() % ((rm->width.value + rm->height.value) / 16))
		* (rand() % 8 + 1);
	rm->rorooms.value = (rm->width.value * rm->height.value / 64 + 1)
		* (rand() % ((rm->width.value + rm->height.value) / 16))
		* (rand() % 8 + 1);
	rm->rdoors.value = (rand() % 8) * (rand() % 8) * (rand() % 8);
	rm->rdeadends.value = (rand() % 12288);
	if (rm->rdeadends.value > 8192)
		rm->rdeadends.value = 0;
	if (rm->rdeadends.value > 4096)
		rm->rdeadends.value = 1;
	if (rm->rdeadends.value != 1)
		rm->ratiolo.value = rm->ratiode.value + 1;
	rm->flamingos.value = level;
}

void	ft_flood_randomcheck_floorinit(t_map *map, int pos)
{
	if (map->m[pos + 1] & WALL)
		map->m[pos] |= FLOORWE;
	if (map->m[pos - 1] & WALL)
		map->m[pos] |= FLOORWW;
	if (map->m[pos + map->w] & WALL)
		map->m[pos] |= FLOORWS;
	if (map->m[pos - map->w] & WALL)
		map->m[pos] |= FLOORWN;
	if (map->m[pos + map->w + 1] & WALL)
		map->m[pos] |= FLOORWSE;
	if (map->m[pos + map->w - 1] & WALL)
		map->m[pos] |= FLOORWSW;
	if (map->m[pos - map->w + 1] & WALL)
		map->m[pos] |= FLOORWNE;
	if (map->m[pos - map->w - 1] & WALL)
		map->m[pos] |= FLOORWNW;
}

void	ft_flood_randomcheck(t_map *map, int pos)
{
	if (map->m[pos] & FLOOD1)
		return ;
	if ((map->m[pos] & WALL))
		return ;
	if (!(map->m[pos]))
	{
		map->valid = 0;
		return ;
	}
	map->m[pos] |= FLOOD1;
	ft_flood_randomcheck_floorinit(map, pos);
	if (pos < map->w || pos > (map->h - 1) * map->w || !(pos % map->w)
		|| pos % map->w == map->w - 1)
	{
		map->valid = 0;
		return ;
	}
	ft_flood_randomcheck(map, pos + 1);
	ft_flood_randomcheck(map, pos - 1);
	ft_flood_randomcheck(map, pos + map->w);
	ft_flood_randomcheck(map, pos - map->w);
}

void	ft_fill_randommap(t_map *map)
{
	ft_flood_randomcheck(map, map->p.mx + map->p.my * map->w);
	ft_fill_colours_to_map(map);
}
