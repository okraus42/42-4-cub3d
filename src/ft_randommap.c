/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:33:20 by okraus            #+#    #+#             */
/*   Updated: 2024/05/10 18:49:33 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

// generate map
// player coordiantes and orientation
// colours
// textures

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

// FLOORWN = 0x10,
// FLOORWE = 0x20,
// FLOORWS = 0x40,
// FLOORWW = 0x80,

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

void	map_print_inner(t_rmap *m, int i)
{
	if (m->map[i] == EDGE)
		ft_printf("%^*C  %0C", 0x000000);
	else if (m->map[i] == RWALL_A)
		ft_printf("%^*C  %0C", 0x002222);
	else if (m->map[i] == RWALL_B)
		ft_printf("%^*C  %0C", 0x444400);
	else if (m->map[i] == RWALL_C || m->map[i] == RWALL_D)
		ft_printf("%^*C  %0C", 0x330033);
	else if (m->map[i] == CORRIDOR_A)
		ft_printf("%^*C  %0C", 0x999999);
	else if (m->map[i] == T_JUNCTION || m->map[i] == X_JUNCTION
		|| m->map[i] == DEADEND)
		ft_printf("%^*C  %0C", 0xaaffaa);
	else if (m->map[i] == CORRIDOR_B)
		ft_printf("%^*C  %0C", 0xdddddd);
	else if (m->map[i] == ROOM_A || m->map[i] == ROOM_B)
		ft_printf("%^*C  %0C", 0xffeeff);
	else if (m->map[i] == RDOOR_NS || m->map[i] == RDOOR_WE)
		ft_printf("%.*^*C--%0C", 0, 0xcc9966);
	else if (m->map[i] & FLOOD_A)
		ft_printf("%^*C  %0C", m->colour);
	else if (m->map[i] & FLOOD_B)
		ft_printf("%^*C  %0C", 0xff0000);
	else
		ft_printf("%^*C  %0C", 0x222277);
}

void	map_print(char *str, t_rmap *m)
{
	int	i;

	i = 0;
	if (str)
		ft_printf("%s\n", str);
	while (i < m->s)
	{
		m->red = ((m->map[i] / 4) + 12 * m->map[i]) % 64 + 192;
		m->green = (32 + (m->map[i] / 4) + 34 * m->map[i]) % 64 + 192;
		m->blue = ((m->map[i] / 4) + m->map[i] * 16) % 64 + 192;
		m->colour = m->red << 16 | m->green << 8 | m->blue;
		map_print_inner(m, i);
		++(i);
		if (i % m->w == 0)
			ft_printf("\n");
	}
}

void	map_print2(char *str, t_rmap *m)
{
	int	i;

	i = 0;
	if (str)
		ft_printf("%s\n", str);
	while (i < m->s)
	{
		m->red = ((m->map[i] / 4) + 12 * m->map[i]) % 64 + 192;
		m->green = (32 + (m->map[i] / 4) + 34 * m->map[i]) % 64 + 192;
		m->blue = ((m->map[i] / 4) + m->map[i] * 16) % 64 + 192;
		m->colour = m->red << 16 | m->green << 8 | m->blue;
		if (m->map[i] == EDGE)
			ft_printf(" ");
		else if (m->map[i] == RWALL_A || m->map[i] == RWALL_B
			|| m->map[i] == RWALL_C || m->map[i] == RWALL_D)
			ft_printf("1");
		else
			ft_printf("0");
		++(i);
		if (i % m->w == 0)
			ft_printf("\n");
	}
}

void	map_prefill2(t_rmap *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if ((m->i < m->w * 2) || (m->i > (m->w * (m->h - 2)))
			|| (m->i % m->w) < 2 || (m->i % m->w) > (m->w - 3))
			m->map[m->i] = EDGE;
		else if ((m->i / m->w) & 1 && !(m->i & 1))
			m->map[m->i] = FLOOD_A;
		else if (!((m->i / m->w) & 1) && !(m->i & 1))
			m->map[m->i] = RWALL_A;
		else if (m->i > m->w && m->i < (m->h - 1) * m->w
			&& m->i % m->w && m->i % m->w < (m->w - 1))
			m->map[m->i] = RWALL_B;
		else
			m->map[m->i] = FLOOD_A;
		++(m->i);
	}
}

int	mg_north2(t_rmap *m)
{
	if (m->map[m->i - (m->w * 2)] == FLOOD_A)
	{
		m->map[m->i - (m->w * 2)] = FLOOD_B;
		m->map[m->i - (m->w)] = CORRIDOR_B;
		return (m->i - (m->w * 2));
	}
	return (0);
}

int	mg_south2(t_rmap *m)
{
	if (m->map[m->i + (m->w * 2)] == FLOOD_A)
	{
		m->map[m->i + (m->w * 2)] = FLOOD_B;
		m->map[m->i + (m->w)] = CORRIDOR_B;
		return (m->i + (m->w * 2));
	}
	return (0);
}

int	mg_east2(t_rmap *m)
{
	if (m->map[m->i + 2] == FLOOD_A)
	{
		m->map[m->i + 2] = FLOOD_B;
		m->map[m->i + 1] = CORRIDOR_B;
		return (m->i + 2);
	}
	return (0);
}

int	mg_west2(t_rmap *m)
{
	if (m->map[m->i - 2] == FLOOD_A)
	{
		m->map[m->i - 2] = FLOOD_B;
		m->map[m->i - 1] = CORRIDOR_B;
		return (m->i - 2);
	}
	return (0);
}

int	check_unvisited_neighbours2(t_rmap *m)
{
	if (m->map[m->p - 2] == FLOOD_A)
		return (0);
	if (m->map[m->p + 2] == FLOOD_A)
		return (0);
	if (m->map[m->p - (m->w * 2)] == FLOOD_A)
		return (0);
	if (m->map[m->p + (m->w * 2)] == FLOOD_A)
		return (0);
	return (1);
}

//add new location to the list of active locations and expand maze
int	maze_expand(t_rmap *m)
{
	m->d = rand() % 4;
	if (m->d == 0)
		m->d = mg_north2(m);
	else if (m->d == 1)
		m->d = mg_east2(m);
	else if (m->d == 2)
		m->d = mg_south2(m);
	else if (m->d == 3)
		m->d = mg_west2(m);
	if (m->d)
	{
		m->temp = malloc(sizeof(int));
		if (!m->temp)
			return (1);
		m->ltemp = ft_lstnew(m->temp);
		if (!m->ltemp)
			return (1);
		*m->temp = m->d;
		ft_lstadd_front(&m->lst, m->ltemp);
	}
	return (0);
}

// check if newest list has neigbours if not remove from the list
void	maze_list(t_rmap *m)
{
	if (m->lst)
		m->p = *(int *)m->lst->content;
	while (m->lst && check_unvisited_neighbours2(m))
	{
		m->ltemp = m->lst->next;
		ft_lstdelone(m->lst, free);
		m->lst = m->ltemp;
		if (m->lst)
			m->p = *(int *)m->lst->content;
	}
	if (m->lst)
		m->i = *(int *)m->lst->content;
}

int	maze_gen2(t_rmap *m)
{
	m->i = 0;
	while (!(m->map[m->i] & FLOOD_A))
		m->i = rand() % (m->s);
	m->map[m->i] = FLOOD_B;
	m->temp = malloc(sizeof(int));
	if (!m->temp)
		return (1);
	*m->temp = m->i;
	m->lst = ft_lstnew(m->temp);
	if (!m->lst)
		return (1);
	while (m->lst)
	{
		if (maze_expand(m))
			return (1);
		maze_list(m);
	}
	return (0);
}

void	map_refill4(t_rmap *m)
{
	m->i = 0;
	m->ends = 0;
	while (m->i < m->s)
	{
		m->walls = 0;
		if (m->map[m->i] & FLOOD_B)
		{
			if (m->map[m->i - 1] == RWALL_B)
				m->walls++;
			if (m->map[m->i + 1] == RWALL_B)
				m->walls++;
			if (m->map[m->i - m->w] == RWALL_B)
				m->walls++;
			if (m->map[m->i + m->w] == RWALL_B)
				m->walls++;
		}
		if (m->walls == 3)
		{
			m->map[m->i] = DEADEND;
			m->ends++;
		}
		++(m->i);
	}
}

void	map_calculate4(t_rmap *m)
{
	int	e;
	int	l;
	int	t;
	int	x;

	e = m->e << 8;
	l = m->l << 8;
	t = m->t << 8;
	x = m->x << 8;
	m->e = ((m->d * e) / (e + l + t + x)) >> 8;
	m->l = ((m->d * l) / (e + l + t + x)) >> 8;
	m->t = ((m->d * t) / (e + l + t + x)) >> 8;
	m->x = ((m->d * x) / (e + l + t + x)) >> 8;
	while ((m->e + m->l + m->t + m->x) < m->ends)
	{
		if (e >= l && e >= t && e >= x)
			m->e++;
		else if (l >= e && l >= t && l >= x)
			m->l++;
		else if (t >= e && t >= l && t >= x)
			m->t++;
		else
			m->x++;
	}
}

void	breakwall4(t_rmap *m, int counter)
{
	while (counter)
	{
		m->d = rand() % 4;
		--counter;
		if (m->d == 0 && m->map[m->i - 1] == RWALL_B)
			m->map[m->i - 1] = CORRIDOR_B;
		else if (m->d == 1 && m->map[m->i + 1] == RWALL_B)
			m->map[m->i + 1] = CORRIDOR_B;
		else if (m->d == 2 && m->map[m->i - m->w] == RWALL_B)
			m->map[m->i - m->w] = CORRIDOR_B;
		else if (m->d == 3 && m->map[m->i + m->w] == RWALL_B)
			m->map[m->i + m->w] = CORRIDOR_B;
		else if (m->map[m->i - 1] != RWALL_B && m->map[m->i + 1] != RWALL_B
			&& m->map[m->i - m->w] != RWALL_B && m->map[m->i + m->w] != RWALL_B)
			counter = 0;
		else
			++counter;
	}
}

void	wallbreaker4(t_rmap *m)
{
	if (m->map[m->i] == DEADEND)
	{
		m->d = rand() % 8;
		if (m->ll < m->l && (m->d & 4) && (m->d & 2) && (m->d & 1))
		{
			breakwall4(m, 1);
			m->ll++;
			m->map[m->i] = CORRIDOR_A;
		}
		else if (m->tt < m->t && (m->d & 2) && (m->d & 1))
		{
			breakwall4(m, 2);
			m->tt++;
			m->map[m->i] = T_JUNCTION;
		}
		else if (m->xx < m->x && (m->d & 1))
		{
			breakwall4(m, 3);
			m->xx++;
			m->map[m->i] = X_JUNCTION;
		}
	}
}

//might loop forever sometimes?
void	map_loops4(t_rmap *m)
{
	int	i;

	i = 0;
	m->ll = 0;
	m->tt = 0;
	m->xx = 0;
	while (m->ll + m->tt + m->xx != m->l + m->t + m->x && i < 4096)
	{
		m->i = 0;
		while (m->i < m->s - 3)
		{
			wallbreaker4(m);
			++(m->i);
		}
		++i;
	}
	if (i == 4096)
		ft_printf("broken loop??\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void	map_outerwall(t_rmap *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if (m->map[m->i] & CORRIDOR_B)
		{
			if (!(m->map[m->i - 1]) || !(m->map[m->i + 1])
				|| !(m->map[m->i + m->w])
				|| !(m->map[m->i - m->w]))
				m->map[m->i] = RWALL_B;
		}
		++(m->i);
	}
	m->i = 0;
}

void	map_refill5(t_rmap *m)
{
	map_outerwall(m);
	while (m->i < m->s)
	{
		m->walls = 0;
		if (m->map[m->i] == FLOOD_B || m->map[m->i] & CORNER_CORRIDOR)
		{
			if (m->map[m->i - 1] == RWALL_B)
				m->walls++;
			if (m->map[m->i + 1] == RWALL_B)
				m->walls++;
			if (m->map[m->i - m->w] == RWALL_B)
				m->walls++;
			if (m->map[m->i + m->w] == RWALL_B)
				m->walls++;
			if (m->walls == 3)
				m->map[m->i] = DEADEND;
			if (m->walls == 2)
				m->map[m->i] = CORRIDOR_A;
			if (m->walls == 1)
				m->map[m->i] = T_JUNCTION;
			if (m->walls == 0)
				m->map[m->i] = X_JUNCTION;
		}
		++(m->i);
	}
}

void	maze_mod4(t_rmap *m)
{
	map_refill4(m);
	map_print("refill4", m);
	if (!(!m->ends || (!m->e && !m->l && !m->x && !m->t)))
	{
		m->d = m->ends << 8;
		map_calculate4(m);
	}
	map_print("calculate4", m);
	map_loops4(m);
	map_print("loops4", m);
	map_refill5(m);
}

int	check_room_overlap6(t_rmap *m, int x, int y)
{
	while (y < m->rh)
	{
		x = 0;
		while (x < m->rw)
		{
			if (m->map[m->i + (y * m->w) + x] == EDGE)
				return (0);
			++x;
		}
		++y;
	}
	return (1);
}

int	check_room_nooverlap6(t_rmap *m, int x, int y)
{
	while (y < m->rh)
	{
		x = 0;
		while (x < m->rw)
		{
			if (m->map[m->i + (y * m->w) + x] == EDGE
				|| m->map[m->i + (y * m->w) + x] == ROOM_A
				|| m->map[m->i + (y * m->w) + x] == ROOM_B)
				return (0);
			++x;
		}
		++y;
	}
	return (1);
}

void	add_room6(t_rmap *m, int x, int y)
{
	y = 0;
	while (y < m->rh)
	{
		x = 0;
		while (x < m->rw)
		{
			if (m->map[m->i + (y * m->w) + x] & CORNER_CORRIDOR
				|| m->map[m->i + (y * m->w) + x] & ROOM_B)
				m->map[m->i + (y * m->w) + x] = ROOM_B;
			else
				m->map[m->i + (y * m->w) + x] = ROOM_A;
			++x;
		}
		++y;
	}
}

void	add_rooms_overlap6(t_rmap *m)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < m->ro)
	{
		x = 0;
		y = 0;
		m->i = rand() % (m->s);
		while (1)
		{
			m->i = rand() % (m->s);
			if ((m->map[m->i] & CORNER_CORRIDOR) || (m->map[m->i] == ROOM_B))
				break ;
		}
		m->rw = (rand() % 4) * 2 + 3;
		m->rh = (rand() % 4) * 2 + 3;
		if (check_room_overlap6(m, x, y))
			add_room6(m, x, y);
		++i;
	}
}

void	add_rooms_nooverlap6(t_rmap *m)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < m->rn)
	{
		x = 0;
		y = 0;
		m->i = rand() % (m->s);
		while (1)
		{
			m->i = rand() % (m->s);
			if ((m->map[m->i] & CORNER_CORRIDOR) || (m->map[m->i] == ROOM_B))
				break ;
		}
		m->rw = (rand() % 4) * 2 + 3;
		m->rh = (rand() % 4) * 2 + 3;
		if (check_room_nooverlap6(m, x, y))
			add_room6(m, x, y);
		++i;
	}
}

void	add_room_walls6(t_rmap *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if (m->map[m->i] == CORRIDOR_B)
		{
			if (m->map[m->i + 1] == ROOM_B || m->map[m->i - 1] == ROOM_B
				|| m->map[m->i - m->w] == ROOM_B
				|| m->map[m->i + m->w] == ROOM_B)
				m->map[m->i] = RWALL_B;
		}
		++(m->i);
	}
}

void	keep_flooding6(t_rmap *m, int i, unsigned int flood_value)
{
	if (m->map[i] & CORRIDORROOM)
		m->map[i] = flood_value;
	if (m->map[i - 1] & CORRIDORROOM)
		keep_flooding6(m, i - 1, flood_value);
	if (m->map[i + 1] & CORRIDORROOM)
		keep_flooding6(m, i + 1, flood_value);
	if (m->map[i - m->w] & CORRIDORROOM)
		keep_flooding6(m, i - m->w, flood_value);
	if (m->map[i + m->w] & CORRIDORROOM)
		keep_flooding6(m, i + m->w, flood_value);
}

void	start_flooding6(t_rmap *m)
{
	m->i = rand() % (3 * m->s / 4) + m->s / 8;
	while (!(m->map[m->i] & FLOOD_A))
		++(m->i);
}

void	keep_flooding_26(t_rmap *m, int i, unsigned int flood_value)
{
	if (m->map[i] & FLOOD_A)
		m->map[i] = flood_value;
	if (m->map[i - 1] & FLOOD_A)
		keep_flooding_26(m, i - 1, flood_value);
	if (m->map[i + 1] & FLOOD_A)
		keep_flooding_26(m, i + 1, flood_value);
	if (m->map[i - m->w] & FLOOD_A)
		keep_flooding_26(m, i - m->w, flood_value);
	if (m->map[i + m->w] & FLOOD_A)
		keep_flooding_26(m, i + m->w, flood_value);
}

int	flood_check(t_rmap *m)
{
	int	i;

	i = 0;
	while (i < m->s)
	{
		if (m->map[i] & FLOOD_A)
		{
			return (1);
		}
		++i;
	}
	return (0);
}

void	add_wall_c(t_rmap *m)
{
	int	i;

	i = 0;
	m->wall_c = 0;
	while (i < m->s)
	{
		if (m->map[i] == RWALL_B
			&& ((m->map[i - 1] & FLOOD_A && m->map[i + 1] & FLOOD_B)
				|| (m->map[i + 1] & FLOOD_A && m->map[i - 1] & FLOOD_B)
				|| (m->map[i - m->w] & FLOOD_A && m->map[i + m->w] & FLOOD_B)
				|| (m->map[i + m->w] & FLOOD_A && m->map[i - m->w] & FLOOD_B)))
		{
			m->map[i] = RWALL_C;
			m->wall_c++;
		}
		++i;
	}
}

void	add_door(t_rmap *m, int i)
{
	if (m->map[i + 1] == RWALL_A || m->map[i - 1] == RWALL_A)
		m->map[i] = RDOOR_NS;
	else
		m->map[i] = RDOOR_WE;
}

void	open_door(t_rmap *m)
{
	int	i;
	int	c;
	int	r;

	i = 0;
	c = 0;
	r = rand() % m->wall_c;
	while (c < r)
	{
		if (m->map[i] == RWALL_C)
			++c;
		++i;
	}
	while (m->map[i] != RWALL_C)
		++i;
	add_door(m, i);
	m->i = i;
}

void	close_wall_c(t_rmap *m)
{
	int	i;
	int	r;

	i = 0;
	while (i < m->s)
	{
		if (m->map[i] == RWALL_C)
		{
			if (!m->cw)
				m->map[i] = RWALL_B;
			else
			{
				r = rand() % 4096;
				if (r < m->cw)
					add_door(m, i);
				else
					m->map[i] = RWALL_B;
			}
		}
		++i;
	}
}

void	flooding_loop(t_rmap *m)
{
	keep_flooding_26(m, m->i, FLOOD_B);
	add_wall_c(m);
	if (m->wall_c)
		open_door(m);
	else if (flood_check(m))
	{
		m->i = 0;
		while (!(m->map[m->i] & FLOOD_A))
			++(m->i);
	}
	close_wall_c(m);
}

void	connect_rooms6(t_rmap *m)
{
	map_print("connecting rooms 6", m);
	m->i = 0;
	m->d = -1;
	while (m->i < m->s)
	{
		if (m->map[m->i] & CORRIDORROOM)
		{
			++(m->d);
			keep_flooding6(m, m->i, FLOOD_A + m->d);
		}
		++m->i;
	}
	map_print("flooding 1", m);
	start_flooding6(m);
	map_print("started flooding", m);
	while (flood_check(m))
	{
		flooding_loop(m);
	}
	map_print("kept flooding222", m);
}

void	add_rooms6(t_rmap *m)
{
	map_print("add rooms", m);
	add_rooms_nooverlap6(m);
	map_print("added nonoverlapping rooms", m);
	add_rooms_overlap6(m);
	map_print("added overlapping rooms", m);
	add_room_walls6(m);
	map_print("added walls around rooms", m);
	connect_rooms6(m);
	map_print("connected rooms", m);
}

void	floodfill_room(t_rmap *m, int i)
{
	if (m->map[i] & CORRIDOR || m->map[i] & FLOOD_B)
		m->map[i] = ROOM_A;
	if (m->map[i - 1] & CORRIDOR || m->map[i - 1] & FLOOD_B)
		floodfill_room(m, i - 1);
	if (m->map[i + 1] & CORRIDOR || m->map[i + 1] & FLOOD_B)
		floodfill_room(m, i + 1);
	if (m->map[i - m->w] & CORRIDOR || m->map[i - m->w] & FLOOD_B)
		floodfill_room(m, i - m->w);
	if (m->map[i + m->w] & CORRIDOR || m->map[i + m->w] & FLOOD_B)
		floodfill_room(m, i + m->w);
}

void	refill_corridors1(t_rmap *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if (m->map[m->i] & FLOOD_B)
		{
			if ((m->map[m->i - 1]) == RWALL_A || (m->map[m->i + 1]) == RWALL_A
				|| (m->map[m->i + m->w]) == RWALL_A
				|| (m->map[m->i - m->w]) == RWALL_A)
				m->map[m->i] = CORRIDOR_B;
			if ((m->map[m->i - 1]) == RWALL_B || (m->map[m->i + 1]) == RWALL_B
				|| (m->map[m->i + m->w]) == RWALL_B
				|| (m->map[m->i - m->w]) == RWALL_B
				|| m->map[m->i - 1] == RDOOR_WE || m->map[m->i + 1] == RDOOR_WE
				|| (m->map[m->i + m->w]) == RDOOR_NS
				|| (m->map[m->i - m->w]) == RDOOR_NS)
				m->map[m->i] = CORRIDOR_A;
		}
		++(m->i);
	}
}

void	refill_corridors2(t_rmap *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if (m->map[m->i] & FLOOD_B)
		{
			if ((m->map[m->i - 1]) == CORRIDOR_B
				&& (m->map[m->i + 1]) == CORRIDOR_B
				&& (m->map[m->i + m->w]) == CORRIDOR_B
				&& (m->map[m->i - m->w]) == CORRIDOR_B
				&& (m->map[m->i + m->w - 1]) == RWALL_A
				&& (m->map[m->i + m->w + 1]) == RWALL_A
				&& (m->map[m->i - m->w - 1]) == RWALL_A
				&& (m->map[m->i - m->w + 1]) == RWALL_A)
				m->map[m->i] = CORRIDOR_A;
		}
		++(m->i);
	}
}

void	refill_corridors3(t_rmap *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if (m->map[m->i] & RDOOR_NS
			&& m->map[m->i + m->w] == CORRIDOR_A
			&& m->map[m->i - m->w] == CORRIDOR_A)
			m->map[m->i] = RDOOR_NS;
		else if (m->map[m->i] & RDOOR_WE
			&& m->map[m->i - 1] & CORRIDOR_A
			&& m->map[m->i + 1] & CORRIDOR_A)
			m->map[m->i] = RDOOR_WE;
		++(m->i);
	}
}

void	map_refill999(t_rmap *m)
{
	refill_corridors1(m);
	map_print("refilled map 1", m);
	refill_corridors2(m);
	map_print("refilled map 2", m);
	m->i = 0;
	while (m->i < m->s)
	{
		if (m->map[m->i] & FLOOD_B)
			floodfill_room(m, m->i);
		++(m->i);
	}
	map_print("refilled map 3", m);
	refill_corridors3(m);
}

void	list_deadends(t_rmap	*m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if (m->map[m->i] & DEADEND)
		{
			m->temp = malloc(sizeof(int));
			if (!m->temp)
				exit (1);
			m->ltemp = ft_lstnew(m->temp);
			if (!m->ltemp)
				exit (1);
			*m->temp = m->i;
			ft_lstadd_front(&m->lst, m->ltemp);
		}
		++(m->i);
	}
}

void	remove_deadend(t_rmap *m);

void	rd_north(t_rmap *m)
{
	if (m->map[m->d - (m->w * 2)] == CORRIDOR_A)
	{
		m->map[m->d - (m->w * 2)] = DEADEND;
		m->map[m->d - (m->w)] = RWALL_D;
		m->map[m->d] = RWALL_D;
		m->d = m->d - (m->w * 2);
		remove_deadend(m);
	}
	else if (m->map[m->d - (m->w * 2)] == T_JUNCTION)
	{
		m->map[m->d - (m->w * 2)] = CORRIDOR_A;
		m->map[m->d - (m->w)] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d - (m->w * 2)] == X_JUNCTION)
	{
		m->map[m->d - (m->w * 2)] = T_JUNCTION;
		m->map[m->d - (m->w)] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d - (m->w * 2)] & ROOM)
	{
		m->map[m->d - (m->w)] = RWALL_B;
		m->map[m->d] = RWALL_D;
	}
}

void	rd_south(t_rmap *m)
{
	if (m->map[m->d + (m->w * 2)] == CORRIDOR_A)
	{
		m->map[m->d + (m->w * 2)] = DEADEND;
		m->map[m->d + (m->w)] = RWALL_D;
		m->map[m->d] = RWALL_D;
		m->d = m->d + (m->w * 2);
		remove_deadend(m);
	}
	else if (m->map[m->d + (m->w * 2)] == T_JUNCTION)
	{
		m->map[m->d + (m->w * 2)] = CORRIDOR_A;
		m->map[m->d + (m->w)] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d + (m->w * 2)] == X_JUNCTION)
	{
		m->map[m->d + (m->w * 2)] = T_JUNCTION;
		m->map[m->d + (m->w)] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d + (m->w * 2)] & ROOM)
	{
		m->map[m->d + (m->w)] = RWALL_B;
		m->map[m->d] = RWALL_D;
	}
}

void	rd_west(t_rmap *m)
{
	if (m->map[m->d - 2] == CORRIDOR_A)
	{
		m->map[m->d - 2] = DEADEND;
		m->map[m->d - 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
		m->d = m->d - 2;
		remove_deadend(m);
	}
	else if (m->map[m->d - 2] == T_JUNCTION)
	{
		m->map[m->d - 2] = CORRIDOR_A;
		m->map[m->d - 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d - 2] == X_JUNCTION)
	{
		m->map[m->d - 2] = T_JUNCTION;
		m->map[m->d - 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d - 2] & ROOM)
	{
		m->map[m->d - 1] = RWALL_B;
		m->map[m->d] = RWALL_D;
	}
}

void	rd_east(t_rmap *m)
{
	if (m->map[m->d + 2] == CORRIDOR_A)
	{
		m->map[m->d + 2] = DEADEND;
		m->map[m->d + 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
		m->d = m->d + 2;
		remove_deadend(m);
	}
	else if (m->map[m->d + 2] == T_JUNCTION)
	{
		m->map[m->d + 2] = CORRIDOR_A;
		m->map[m->d + 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d + 2] == X_JUNCTION)
	{
		m->map[m->d + 2] = T_JUNCTION;
		m->map[m->d + 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d + 2] & ROOM)
	{
		m->map[m->d + 1] = RWALL_B;
		m->map[m->d] = RWALL_D;
	}
}

void	remove_deadend(t_rmap *m)
{
	if (m->map[m->d + 1] & (CORRIDOR_B | RDOOR))
		rd_east(m);
	else if (m->map[m->d - 1] & (CORRIDOR_B | RDOOR))
		rd_west(m);
	else if (m->map[m->d + (m->w)] & (CORRIDOR_B | RDOOR))
		rd_south(m);
	else if (m->map[m->d - (m->w)] & (CORRIDOR_B | RDOOR))
		rd_north(m);
}

void	process_deadends(t_rmap	*m)
{
	int	r;

	while (m->lst)
	{
		r = rand() % 1024;
		m->ltemp = m->lst->next;
		m->d = *(int *)m->lst->content;
		if (m->dr == 1 || (m->dr > r))
			remove_deadend(m);
		ft_lstdelone(m->lst, free);
		m->lst = m->ltemp;
	}
}

void	trim_deadends(t_rmap *m)
{
	map_refill999(m);
	map_refill5(m);
	map_print("refilled map", m);
	list_deadends(m);
	process_deadends(m);
	map_print("trimmed ends", m);
}

void	map_refill42(t_rmap *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if (m->map[m->i] & RWALL)
			m->map[m->i] = RWALL_A;
		if (m->map[m->i] & CORRIDOR)
			m->map[m->i] = CORRIDOR_A;
		++(m->i);
	}
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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

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
