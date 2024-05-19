/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:22:44 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 18:23:54 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_init_sprites_flamingo(t_map *map, int i)
{
	map->sprites[i].state = 1;
	map->sprites[i].texture = FLAMINGO_TEXTURE;
	map->sprites[i].glowtexture = FLAMINGO_GLOW;
	map->sprites[i].type = SPRITE_FLAMINGO;
	map->sprites[i].frame = 0;
	map->sprites[i].maxframe = 1;
	map->sprites[i].z = 20;
	map->m[(map->sprites[i].y >> 16) * map->w + (map->sprites[i].x >> 16)]
		&= 0x00000000FFFFFFFF;
	map->m[(map->sprites[i].y >> 16) * map->w + (map->sprites[i].x >> 16)]
		|= 0xFF80FFFF00000000;
	++map->current_sprite[SPRITE_FLAMINGO];
	++map->total_sprite[SPRITE_FLAMINGO];
	++map->spritecount;
}

void	ft_init_sprites(t_max *max)
{
	int	i;

	i = 0;
	max->map.sprites[SPRITE_EXIT].state = 0;
	max->map.sprites[SPRITE_EXIT].texture = EXIT_TEXTURE;
	max->map.sprites[SPRITE_EXIT].glowtexture = EXIT_GLOW;
	max->map.sprites[SPRITE_EXIT].type = SPRITE_EXIT;
	max->map.sprites[SPRITE_EXIT].frame = 0;
	max->map.sprites[SPRITE_EXIT].maxframe = 32;
	max->map.sprites[SPRITE_EXIT].z = 20;
	max->map.spritecount = 1;
	while (i < SPRITETYPES)
	{
		max->map.current_sprite[i] = 0;
		max->map.total_sprite[i] = 0;
		++i;
	}
}

int	ft_sprite_visible_check(t_max *max, int minangle, int maxangle)
{
	if (minangle < maxangle)
	{
		if (max->map.p.oray[0].ra < max->map.p.oray[RAYS - 1].ra)
		{
			if (max->map.p.oray[RAYS - 1].ra < minangle
				|| max->map.p.oray[0].ra > maxangle)
				return (0);
		}
		else
		{
			if (max->map.p.oray[RAYS - 1].ra < minangle
				&& max->map.p.oray[0].ra > maxangle)
				return (0);
		}
	}
	else
	{
		if (max->map.p.oray[0].ra < max->map.p.oray[RAYS - 1].ra)
		{
			if (max->map.p.oray[RAYS - 1].ra < minangle
				&& max->map.p.oray[0].ra > maxangle)
				return (0);
		}
	}
	return (1);
}

int	ft_sprite_visible(t_max *max, int direction, int radius)
{
	int	minangle;
	int	maxangle;

	minangle = direction - radius;
	maxangle = direction + radius;
	if (minangle < 0)
		minangle += MAXDEGREE;
	if (maxangle >= MAXDEGREE)
		maxangle -= MAXDEGREE;
	return (ft_sprite_visible_check(max, minangle, maxangle));
}

int	ft_sprite_visible2(t_max *max, int r, long long distance)
{
	if (max->map.p.oray[r].wall && distance > max->map.p.oray[r].length)
		return (0);
	return (1);
}
