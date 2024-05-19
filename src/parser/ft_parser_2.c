/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:37:06 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 11:33:48 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

static void	ft_map_init_2(t_map *map)
{
	map->mapstr = NULL;
	map->northtexture = NULL;
	map->southtexture = NULL;
	map->westtexture = NULL;
	map->easttexture = NULL;
	map->valid = 1;
}

static void	ft_map_init(t_max *max, t_map *map)
{
	int	i;

	ft_map_init_2(map);
	map->p.orientation = -1;
	map->p.x = 0;
	map->p.y = 0;
	map->p.speed = 16;
	map->p.turnspeed = 512;
	map->p.xspeed = 0;
	map->p.yspeed = 0;
	map->p.fov = max->settings.fov;
	map->p.fov2 = map->p.fov * 65536 / 720;
	map->h = 0;
	map->w = 0;
	map->f.rgba = 0;
	map->c.rgba = 0;
	map->b.rgba = 0xFF;
	i = 0;
	while (i < 65536)
	{
		map->m[i] = 0;
		++i;
	}
}

int	ft_init_map_textures(t_max *max)
{
	if (max->t.nwall)
		mlx_delete_texture(max->t.nwall);
	if (max->t.swall)
		mlx_delete_texture(max->t.swall);
	if (max->t.ewall)
		mlx_delete_texture(max->t.ewall);
	if (max->t.wwall)
		mlx_delete_texture(max->t.wwall);
	ft_load_texture(max->map.northtexture, &max->t.nwall);
	ft_load_texture(max->map.westtexture, &max->t.wwall);
	ft_load_texture(max->map.southtexture, &max->t.swall);
	ft_load_texture(max->map.easttexture, &max->t.ewall);
	return (1);
}

void	ft_init_brume(t_max *max)
{
	int	c;
	int	d;

	c = 0;
	while (c < 256)
	{
		d = 0;
		while (d < 256)
		{
			max->math->brumered[c][d] = ft_percentil(c, max->map.b.r, d, 255);
			max->math->brumegreen[c][d] = ft_percentil(c, max->map.b.g, d, 255);
			max->math->brumeblue[c][d] = ft_percentil(c, max->map.b.b, d, 255);
			++d;
		}
		++c;
	}
}

int	ft_process_file(t_max *max)
{
	t_map	*map;

	ft_init_sprites(max);
	map = &max->map;
	ft_printf("map->file111:%s\n", map->file);
	ft_map_init(max, map);
	if (!ft_read_map(map))
	{
		ft_freemap(map);
		return (0);
	}
	if (!ft_fill_map(map))
	{
		ft_freemap(map);
		return (0);
	}
	if (!ft_init_map_textures(max))
	{
		ft_freemap(map);
		return (0);
	}
	ft_init_brume(max);
	ft_init_time(max);
	ft_freemap(map);
	return (1);
}
