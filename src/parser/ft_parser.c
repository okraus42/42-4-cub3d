/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:25:48 by okraus            #+#    #+#             */
/*   Updated: 2024/05/07 13:58:34 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	ft_fill_colour2(char **split, int c, t_map *map)
{
	if (c == 'F')
	{
		map->f.r = ft_atoi(split[0]);
		map->f.g = ft_atoi(split[1]);
		map->f.b = ft_atoi(split[2]);
		map->f.a = 0xFF;
	}
	if (c == 'C')
	{
		map->c.r = ft_atoi(split[0]);
		map->c.g = ft_atoi(split[1]);
		map->c.b = ft_atoi(split[2]);
		map->c.a = 0xFF;
	}
	if (c == 'B')
	{
		map->b.r = ft_atoi(split[0]);
		map->b.g = ft_atoi(split[1]);
		map->b.b = ft_atoi(split[2]);
		map->b.a = 0xFF;
	}
	ft_free_split(&split);
	return (1);
}

int	ft_fill_colour(int c, char *s, t_map *map, int j)
{
	char	**split;
	int		i;

	split = ft_split(s, ',');
	if (!split)
		return (ft_puterror("Malloc error", 0));
	while (j < 3)
	{
		i = 0;
		while (split[j][i])
		{
			if (!ft_isdigit(split[j][i]))
			{
				ft_free_split(&split);
				return (ft_puterror("Invalid character in colour", 0));
			}
			++i;
		}
		if (i > 3 || j > 2 || ft_atoi(split[j]) > 255)
		{
			ft_free_split(&split);
			return (ft_puterror("Colour format is not right", 0));
		}
		++j;
	}
	return (ft_fill_colour2(split, c, map));
}

int	ft_check_map(t_map *map, char **split, int j, int a)
{
	int	p;
	int	i;

	p = 0;
	while (split[j])
	{
		i = 0;
		while (split[j][i])
		{
			if (!ft_strchr(" 01NSEWXF><^v", split[j][i]))
			{
				ft_free_split(&split);
				return (ft_puterror("Invalid character in map", 0));
			}
			if (ft_strchr("NSEW", split[j][i]))
				++p;
			++i;
			map->w = MAX(map->w, i);
		}
		++j;
	}
	map->h = j - a;
	if (p != 1)
	{
		ft_free_split(&split);
		if (!p)
			return (ft_puterror("No player location in the map", 0));
		else
			return (ft_puterror("Too many player locations in map", 0));
	}
	if (map->w < 3 || map->h < 3 || map->w > 256 || map->h > 256)
	{
		ft_free_split(&split);
		return (ft_puterror("Wrong map dimensions, minimum size is 3x3", 0));
	}
	map->ww = map->w;
	map->w = 256;
	map->hh = map->h;
	map->h = 256;
	return (1);
}

void	ft_flood_check2(t_map *map, int pos)
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

void	ft_flood_check(t_map *map, int pos)
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
	ft_flood_check2(map, pos);
	if (pos < map->w || pos > (map->h - 1) * map->w || !(pos % map->w)
		|| pos % map->w == map->w - 1)
	{
		map->valid = 0;
		return ;
	}
	ft_flood_check(map, pos + 1);
	ft_flood_check(map, pos - 1);
	ft_flood_check(map, pos + map->w);
	ft_flood_check(map, pos - map->w);
}
