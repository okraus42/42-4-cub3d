/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:52:53 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/07 13:55:56 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_fill_colours_to_map2(t_map *map, int i)
{
	if (map->m[i] & EXIT)
	{
		map->sprites[SPRITE_EXIT].x = ((i % 256) << 16) | 0x7FFF;
		map->sprites[SPRITE_EXIT].y = ((i / 256) << 16) | 0x7FFF;
		map->m[i] &= 0x00000000FFFFFFFF;
		map->m[i] |= 0xFF00FFFF00000000;
	}
	else if (map->m[i] & FLOOR1)
	{
		map->m[i] &= 0x00000000FFFFFFFF;
		map->m[i] |= ((unsigned long long)(map->f.rgba) << 32);
	}
	else if (map->m[i] & FLOORFLAMINGO)
	{
		map->sprites[map->spritecount].x = ((i % 256) << 16) | 0x7FFF;
		map->sprites[map->spritecount].y = ((i / 256) << 16) | 0x7FFF;
		ft_init_sprites_flamingo(map, map->spritecount);
	}
}

void	ft_fill_colours_to_map3_d(t_map *map, int i)
{
	if (map->m[i] & DOOREAST)
	{
		map->m[i] &= 0x00000000FFFFFFFF;
		map->m[i] |= 0x53565AFF00000000;
		map->doors[i] = 0x1FF;
	}
	else if (map->m[i] & DOORWEST)
	{
		map->m[i] &= 0x00000000FFFFFFFF;
		map->m[i] |= 0x53565AFF00000000;
		map->doors[i] = 0x1FF;
	}
	else if (map->m[i] & DOORNORTH)
	{
		map->m[i] &= 0x00000000FFFFFFFF;
		map->m[i] |= 0x53565AFF00000000;
		map->doors[i] = 0x1FF;
	}
	else if (map->m[i] & DOORSOUTH)
	{
		map->m[i] &= 0x00000000FFFFFFFF;
		map->m[i] |= 0x53565AFF00000000;
		map->doors[i] = 0x1FF;
	}
}

void	ft_fill_colours_to_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->h * map->w)
	{
		ft_fill_colours_to_map2(map, i);
		ft_fill_colours_to_map3_d(map, i);
		if (map->m[i] & WALL)
		{
			map->m[i] &= 0x00000000FFFFFFFF;
			map->m[i] |= 0x000000FFFFFFFFFF;
		}
		else
			map->m[i] &= 0x00000000FFFFFFFF;
		++i;
	}
}

int	ft_fill_colours(t_map *map)
{
	char	**split;
	int		j;

	split = ft_split(map->mapstr, '\n');
	if (!split)
		return (ft_puterror("Malloc error", 0));
	j = 0;
	while (split[j])
	{
		if (!ft_strncmp(split[j], "F ", 2) || !ft_strncmp(split[j], "C ", 2)
			|| !ft_strncmp(split[j], "B ", 2))
		{
			if (!ft_fill_colour(split[j][0], &split[j][2], map, 0))
			{
				ft_free_split(&split);
				return (0);
			}
		}
		++j;
	}
	ft_free_split(&split);
	if (!map->c.rgba || !map->f.rgba)
		return (ft_puterror("Missing floor or ceiling colour, aborting...", 0));
	return (1);
}

int	ft_fill_map(t_map *map)
{
	if (!ft_fill_textures(map))
		return (0);
	if (!ft_fill_colours(map))
		return (0);
	if (!ft_fill_array(map))
		return (0);
	ft_fill_colours_to_map(map);
	return (1);
}
