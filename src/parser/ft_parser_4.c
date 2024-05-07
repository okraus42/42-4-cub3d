/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:16:59 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/07 13:49:22 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_init_time(t_max *max)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (i < 65536)
	{
		if (max->map.m[i] & FLOOR)
		{
			++c;
		}
		++i;
	}
	max->limitms = (c * 100) + 15000;
}

void	ft_fill_array4(t_map *map, char c, int y, int x)
{
	map->m[y * map->w + x] = FLOOR1;
	map->p.mx = x;
	map->p.my = y;
	map->p.sx = 0x7f7f;
	map->p.sy = 0x7f7f;
	map->p.unused_x = 0;
	map->p.unused_y = 0;
	map->p.smx = x * 64;
	map->p.smy = y * 64;
	if (map->p.smx > SUPERMAPWIDTH - SUPERMAPBORDER)
		map->p.smx = SUPERMAPWIDTH - SUPERMAPBORDER;
	if (map->p.smy > SUPERMAPHEIGHT - SUPERMAPBORDER)
		map->p.smy = SUPERMAPHEIGHT - SUPERMAPBORDER;
	if (c == 'N')
		map->p.orientation = NORTH;
	else if (c == 'W')
		map->p.orientation = WEST;
	else if (c == 'S')
		map->p.orientation = SOUTH;
	else if (c == 'E')
		map->p.orientation = EAST;
}

void	ft_fill_array3(t_map *map, char c, int y, int x)
{
	if (c == '0')
		map->m[y * map->w + x] = FLOOR1;
	else if (c == '1')
		map->m[y * map->w + x] = WALL1;
	else if (c == 'X')
		map->m[y * map->w + x] = EXIT;
	else if (c == 'F')
		map->m[y * map->w + x] = FLOORFLAMINGO;
	else if (c == '>')
		map->m[y * map->w + x] = DOOREAST;
	else if (c == '<')
		map->m[y * map->w + x] = DOORWEST;
	else if (c == '^')
		map->m[y * map->w + x] = DOORNORTH;
	else if (c == 'v')
		map->m[y * map->w + x] = DOORSOUTH;
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		ft_fill_array4(map, c, y, x);
}

int	ft_fill_array2(t_map *map, char **split, int j, int a)
{
	int	i;

	while (split[j])
	{
		i = 0;
		while (split[j][i])
		{
			ft_fill_array3(map, split[j][i], j - a, i);
			++i;
		}
		++j;
	}
	ft_flood_check(map, map->p.mx + map->p.my * map->w);
	if (!map->valid)
	{
		ft_free_split(&split);
		return (ft_puterror("Invalid map border or player position", 0));
	}
	return (1);
}

int	ft_fill_array(t_map *map)
{
	char	**split;
	int		j;
	int		a;

	split = ft_split(map->mapstr, '\n');
	if (!split)
		return (ft_puterror("Malloc error", 0));
	j = 0;
	while (split[j])
	{
		if (ft_strchr(" 01", split[j][0]))
			break ;
		++j;
	}
	if (!split[j])
	{
		ft_free_split(&split);
		return (ft_puterror("Map not found", 0));
	}
	a = j;
	if (!ft_check_map(map, split, j, a))
		return (0);
	if (!ft_fill_array2(map, split, j, a))
		return (0);
	ft_free_split(&split);
	return (1);
}
