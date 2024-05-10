/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:17:08 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/10 16:31:41 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	ft_check_map2(t_map *map, char **split, int p)
{
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
			map->w = ft_max(map->w, i);
		}
		++j;
	}
	map->h = j - a;
	return (ft_check_map2(map, split, p));
}
