/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:25:48 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 20:26:03 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

char	*ft_strdup2(char *str, char c)
{
	while (*str && *str == c)
		str++;
	return (ft_strdup(str));
}

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
		i = -1;
		while (split[j][++i])
		{
			if (!ft_isdigit(split[j][i]) && !ft_isspace(split[j][i]))
			{
				ft_free_split(&split);
				return (ft_puterror("Invalid character in colour", 0));
			}
		}
		if (j > 2 || ft_atoi(split[j]) > 255)
		{
			ft_free_split(&split);
			return (ft_puterror("Colour format is not right", 0));
		}
		++j;
	}
	return (ft_fill_colour2(split, c, map));
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
