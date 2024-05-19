/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:33:20 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 16:30:07 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_random_init_exit(t_max *max, int i)
{
	ft_printf("EXIT: x %x y  %x\n", i % 256, i / 256);
	max->map.sprites[SPRITE_EXIT].x = (i % 256) << 16 | 0x7FFF;
	max->map.sprites[SPRITE_EXIT].y = (i / 256) << 16 | 0x7FFF;
	max->map.m[i] = ((max->map.m[i] & 0xFFFFF0) | EXIT) | 0xFF00FFFF00000000;
}

void	ft_random_init(t_max *max)
{
	t_rmap			m;
	int				i;
	int				j;

	i = -1;
	j = 0;
	ft_random_init_inits(max, &m);
	while (++i < 65536)
	{
		if (j < m.s && (i % 256 < m.w))
		{
			ft_random_init_loop(max, &m, j, i);
			++j;
		}
	}
	while (--i)
	{
		if (max->map.m[i] & FLOOR1)
		{
			ft_random_init_exit(max, i);
			break ;
		}
	}
}

void	ft_place_sprites_inner(t_max *max, int i, int *c)
{
	while (i < max->map.w * max->map.h)
	{
		if (max->map.m[i] & WALL)
		{
			++i;
			continue ;
		}
		if ((max->map.m[i] & FLOOR1)
			&& (i != (max->map.p.mx + max->map.p.my * max->map.w)))
		{
			if (*c && !(rand() % 64))
			{
				max->map.sprites[max->map.spritecount].x = (i % 256)
					<< 16 | 0x7FFF;
				max->map.sprites[max->map.spritecount].y = (i / 256)
					<< 16 | 0x7FFF;
				ft_init_sprites_flamingo(&max->map, max->map.spritecount);
				--(*c);
			}
		}
		++i;
	}
}

void	ft_place_sprites(t_max *max)
{
	int	i;
	int	c;
	int	canary;

	canary = 4096;
	c = max->menu.rm.flamingos.value;
	while (c || canary)
	{
		i = 0;
		ft_place_sprites_inner(max, i, &c);
		--canary;
	}
}

int	ft_process_random(t_max *max)
{
	t_map	*map;

	map = &max->map;
	ft_init_sprites(max);
	ft_random_init(max);
	ft_fill_randommap(map);
	ft_init_brume(max);
	ft_place_sprites(max);
	ft_init_time(max);
	return (1);
}
