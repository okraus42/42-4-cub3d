/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_13.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:23:31 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 16:27:41 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

static void	ft_map_init(t_max *max, t_map *map)
{
	int	i;

	map->mapstr = NULL;
	map->northtexture = NULL;
	map->southtexture = NULL;
	map->westtexture = NULL;
	map->easttexture = NULL;
	map->valid = 1;
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
	map->f.rgba = ((unsigned int)(rand() % 0xFFFFFF) << 8) | 0xFF;
	map->c.rgba = ((unsigned int)(rand() % 0xFFFFFF) << 8) | 0xFF;
	map->b.rgba = ((unsigned int)(rand() % 0xFFFFFF) << 8) | 0xFF;
	i = -1;
	while (++i < 65536)
		map->m[i] = 0;
}

void	map_init(t_randommap *rm, t_rmap *m)
{
	m->width = rm->width.value;
	m->height = rm->height.value;
	m->e = rm->ratiode.value;
	m->l = rm->ratiolo.value;
	m->t = rm->ratioti.value;
	m->x = rm->ratioxi.value;
	m->rn = rm->rnorooms.value;
	m->ro = rm->rorooms.value;
	m->cw = rm->rdoors.value;
	m->dr = rm->rdeadends.value;
	m->w = m->width * 2 + 5;
	m->h = m->height * 2 + 5;
	m->s = m->w * m->h;
}

void	ft_random_init_loop_putplayer(t_max *max, t_rmap *m, int i)
{
	max->map.p.mx = i % 256;
	max->map.p.my = i / 256;
	max->map.p.sx = 0x7f7f;
	max->map.p.sy = 0x7f7f;
	max->map.p.smx = i % 256 * 64;
	max->map.p.smy = i / 256 * 64;
	if (max->map.p.smx > SUPERMAPWIDTH - SUPERMAPBORDER)
		max->map.p.smx = SUPERMAPWIDTH - SUPERMAPBORDER;
	if (max->map.p.smy > SUPERMAPHEIGHT - SUPERMAPBORDER)
		max->map.p.smy = SUPERMAPHEIGHT - SUPERMAPBORDER;
	max->map.p.orientation = EAST;
	max->map.p.unused_x = 0;
	max->map.p.unused_y = 0;
	m->pp = 0;
}

void	ft_random_init_loop(t_max *max, t_rmap *m, int j, int i)
{
	if (m->map[j] & RWALL)
		max->map.m[i] = WALL1;
	else if ((m->map[j] & RDOOR_NS))
	{
		if (rand() % 2)
			max->map.m[i] = DOORWEST;
		else
			max->map.m[i] = DOOREAST;
	}
	else if ((m->map[j] & RDOOR_WE))
	{
		if (rand() % 2)
			max->map.m[i] = DOORNORTH;
		else
			max->map.m[i] = DOORSOUTH;
	}
	else if ((m->map[j] & CORRIDOR)
		|| (m->map[j] & RDOOR) || (m->map[j] & ROOM))
	{
		max->map.m[i] = FLOOR1;
		if (m->pp)
			ft_random_init_loop_putplayer(max, m, i);
	}
}

void	ft_random_init_inits(t_max *max, t_rmap *m)
{
	unsigned int	seed;

	seed = time(0);
	srand(seed);
	ft_map_init(max, &max->map);
	map_init(&max->menu.rm, m);
	map_prefill2(m);
	map_print("prefilled map", m);
	maze_gen2(m);
	maze_mod4(m);
	map_print("indexed map", m);
	add_rooms6(m);
	map_print("added and opened rooms", m);
	trim_deadends(m);
	map_print("???trimmed deadeneds???", m);
	map_refill42(m);
	map_print("FINAL MAP", m);
	map_print2("copy map", m);
	m->pp = 1;
	max->map.ww = m->w;
	max->map.w = 256;
	max->map.hh = m->h;
	max->map.h = 256;
}
