/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:33:20 by okraus            #+#    #+#             */
/*   Updated: 2024/03/28 15:18:50 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

// generate map
// player coordiantes and orientation
// colours
// textures

static void	ft_map_init(t_map *map)
{
	int	i;

	map->mapstr = NULL;
	map->northtexture = NULL;
	map->southtexture = NULL;
	map->westtexture = NULL;
	map->easttexture = NULL;
	//map->d = NULL;
	map->valid = 1;
	map->e = -1;
	map->p.orientation = -1;
	map->p.x = 0;
	map->p.y = 0;
	map->p.speed = 16;
	map->p.turnspeed = 512;
	map->p.xspeed = 0;
	map->p.yspeed = 0;
	map->p.fov = FOV;
	map->p.fov2 = map->p.fov * 65536 / 720;
	map->h = 0;
	map->w = 0;
	map->f.rgba = ((unsigned int)(rand() % 0xFFFFFF) << 8) | 0xFF;
	map->c.rgba = ((unsigned int)(rand() % 0xFFFFFF) << 8) | 0xFF;
	map->b.rgba = 0xFF;
	i = 0;
	while (i < 65536)
	{
		map->m[i] = 0;
		++i;
	}
}

// FLOORWN = 0x10,
// FLOORWE = 0x20,
// FLOORWS = 0x40,
// FLOORWW = 0x80,

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


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// compile with libft.a
// pass number for
// width, height, ratio of dead ends, loops, T-intersections, X-intersections
// notoverlapping room placement attempts, overlapping rooms placement attempts
// chance to create extra doors (higher is better, 4096 is max)
// chance to remove deadends 0 keeps deadends, 1 removes dead ends,
// 2 - 1024 chance to remove percentage of deadends
// like 52 26 4 5 3 2 20 10 25 512

typedef struct s_rmap
{
	int				width;
	int				height;
	int				w;
	int				h;
	int				s;
	int				i;
	int				d;
	int				p;
	int				walls;
	int				ends;
	int				e;
	int				l;
	int				ll;
	int				t;
	int				tt;	
	int				x;
	int				xx;
	int				rn;
	int				ro;
	int				rw;
	int				rh;
	int				ed;
	int				dr;
	int				loops;
	int				wall_c;
	int				cw;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	colour;
	t_list			*lst;
	t_list			*ltemp;
	int				*temp;
	unsigned int	map[65536];
}	t_rmap;

// typedef struct s_map
// {
// 	int				width;		//input weight
// 	int				height;		//input heightH
// 	int				w;			//actual map width
// 	int				h;			//actual map height
// 	int				s;			//size, stop w*h
// 	int				i;			//iterating
// 	int				d;			//temp value
// 	int				p;			//actual position?
// 	int				walls;		//how many walls around actual position
// 	int				ends;		//how many dead ends in the maze originally
// 	int				e;			//how many dead ends left
// 	int				l;			//how many basic loops
// 	int				ll;
// 	int				t;			//how many t intersections from dead end
// 	int				tt;	
// 	int				x;			//how many x intersections from dead end
// 	int				xx;
// 	int				rn;		//how many attempts to build not an overlapping room
// 	int				ro;			//how many attempts to build an overlapping room
// 	int				rw;			//room width
// 	int				rh;			//room height
// 	int				ed;			//extra door probability
// 	int				dr;	//dead end removal (0 - keep de, 1 - remove de,
//						//n - remove n corridors from de)
// 	int				loops;		//how many dead ends were changed int loops
// 	int				wall_c;		//number of wall c
// 	int				cw;			// % to close wall c
// 	unsigned int	red;
// 	unsigned int	green;
// 	unsigned int	blue;
// 	unsigned int	colour;
// 	t_list			*lst;		//stack of visited positions (with neighbours?)
// 	t_list			*ltemp;		//temporaty list
// 	int				*temp;		//temporary value of position in the map
// 	unsigned int	map[65536];	//map up to 256*256
// } t_rmap;

// BETTER SOLUTION
// Do EDGES 2 walls thick
typedef enum e_map_block
{
	EDGE = 0x0,
	RWALL = 0xF0,
	RWALL_A = 0x10,
	RWALL_B = 0x20,
	RWALL_C = 0x40,
	RWALL_D = 0x80,
	DOOR_NS = 0x100,
	DOOR_WE = 0x200,
	DOOR = 0xF00,
	DEADSPOT = 0x10000,
	CORNER_CORRIDOR = 0x1F000,
	CORRIDOR = 0x3F000,
	DEADEND = 0x1000,
	CORRIDOR_A = 0x2000,
	T_JUNCTION = 0x4000,
	X_JUNCTION = 0x8000,
	CORRIDOR_B = 0x20000,
	ROOM_A = 0x100000,
	ROOM_B = 0x200000,
	ROOM_C = 0x400000,
	ROOM = 0xF00000,
	CORRIDORROOM = 0xFFF000,
	FLOOD_A = 0x1000000,
	FLOOD_B = 0x2000000	
}	t_rmap_block;

// BETTER SOLUTION
// Do EDGES 2 walls thick
// typedef enum e_map_block
// {
// 	EDGE = 0x0,
// 	RWALL = 0xF0,
// 	RWALL_A = 0x10,		//RWALL COLUMN, permanent wall except for 
// 	RWALL_B = 0x20,		//RWALL between columns
// 	RWALL_C = 0x40,		//RWALL between columns between two different areas
// 	RWALL_D = 0x80,		//RWALL after deadend
// 	DOOR_NS = 0x100,		// corridor at 
// 	DOOR_WE = 0x200,
// 	DOOR = 0xF00,
// 	DEADSPOT = 0x10000,	//surrounded by 4 walls
// 	CORNER_CORRIDOR = 0x1F000, // corner corridor
// 	CORRIDOR = 0x3F000,	//any corridor corner stuff
// 	DEADEND = 0x1000,
// 	CORRIDOR_A = 0x2000,	// corridor at junction place
// 	T_JUNCTION = 0x4000,
// 	X_JUNCTION = 0x8000,
// 	CORRIDOR_B = 0x20000,	// corridor between two permawalls
// 	ROOM_A = 0x100000,
// 	ROOM_B = 0x200000,		//room 4
// 	ROOM_C = 0x400000,
// 	ROOM = 0xF00000,
// 	CORRIDORROOM = 0xFFF000,
// 	FLOOD_A = 0x1000000,		//flood to index different areas
// 	FLOOD_B = 0x2000000		//flood to connect different areas
// }	t_rmap_block;

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
		if (m->map[i] == EDGE)
			ft_printf("%^*C  %0C", 0x000000);
		else if (m->map[i] == RWALL_A)
			ft_printf("%^*C  %0C", 0x002222);
		else if (m->map[i] == RWALL_B)
			ft_printf("%^*C  %0C", 0x444400);
		else if (m->map[i] == RWALL_C)
			ft_printf("%^*C  %0C", 0x660066);
		else if (m->map[i] == RWALL_D)
			ft_printf("%^*C  %0C", 0x330033);
		else if (m->map[i] == DEADEND)
			ft_printf("%^*C  %0C", 0xff8888);
		else if (m->map[i] == CORRIDOR_A)
			ft_printf("%^*C  %0C", 0x999999);
		else if (m->map[i] == T_JUNCTION)
			ft_printf("%^*C  %0C", 0xaaffaa);
		else if (m->map[i] == X_JUNCTION)
			ft_printf("%^*C  %0C", 0xbbbbff);
		else if (m->map[i] == CORRIDOR_B)
			ft_printf("%^*C  %0C", 0xdddddd);
		else if (m->map[i] == ROOM_A)
			ft_printf("%^*C  %0C", 0xffffff);
		else if (m->map[i] == ROOM_B)
			ft_printf("%^*C  %0C", 0xffeeff);
		else if (m->map[i] == DOOR_NS)
			ft_printf("%.*^*C--%0C", 0, 0xcc9966);
		else if (m->map[i] == DOOR_WE)
			ft_printf("%.*^*C||%0C", 0, 0xcc9966);
		else if (m->map[i] & FLOOD_A)
			ft_printf("%^*C  %0C", m->colour);
		else if (m->map[i] & FLOOD_B)
			ft_printf("%^*C  %0C", 0xff0000);
		else
			ft_printf("%^*C  %0C", 0x222277);
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
		else if (m->map[i] == RWALL_A)
			ft_printf("1");
		else if (m->map[i] == RWALL_B)
			ft_printf("1");
		else if (m->map[i] == RWALL_C)
			ft_printf("1");
		else if (m->map[i] == RWALL_D)
			ft_printf("1");
		else if (m->map[i] == DEADEND)
			ft_printf("0");
		else if (m->map[i] == CORRIDOR_A)
			ft_printf("0");
		else if (m->map[i] == T_JUNCTION)
			ft_printf("0");
		else if (m->map[i] == X_JUNCTION)
			ft_printf("0");
		else if (m->map[i] == CORRIDOR_B)
			ft_printf("0");
		else if (m->map[i] == ROOM_A)
			ft_printf("0");
		else if (m->map[i] == ROOM_B)
			ft_printf("0");
		else if (m->map[i] == DOOR_NS)
			ft_printf("0");
		else if (m->map[i] == DOOR_WE)
			ft_printf("0");
		else if (m->map[i] & FLOOD_A)
			ft_printf("0");
		else if (m->map[i] & FLOOD_B)
			ft_printf("0");
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

void	map_loops4(t_rmap *m)
{
	m->ll = 0;
	m->tt = 0;
	m->xx = 0;
	while (m->ll + m->tt + m->xx != m->l + m->t + m->x)
	{
		m->i = 0;
		while (m->i < m->s - 3)
		{
			wallbreaker4(m);
			++(m->i);
		}
	}
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
		m->map[i] = DOOR_NS;
	else
		m->map[i] = DOOR_WE;
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
				|| m->map[m->i - 1] == DOOR_WE || m->map[m->i + 1] == DOOR_WE
				|| (m->map[m->i + m->w]) == DOOR_NS
				|| (m->map[m->i - m->w]) == DOOR_NS)
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
		if (m->map[m->i] & DOOR_NS
			&& m->map[m->i + m->w] == CORRIDOR_A
			&& m->map[m->i - m->w] == CORRIDOR_A)
			m->map[m->i] = CORRIDOR_B;
		else if (m->map[m->i] & DOOR_WE
			&& m->map[m->i - 1] & CORRIDOR_A
			&& m->map[m->i + 1] & CORRIDOR_A)
			m->map[m->i] = CORRIDOR_B;
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
	if (m->map[m->d + 1] & (CORRIDOR_B | DOOR))
		rd_east(m);
	else if (m->map[m->d - 1] & (CORRIDOR_B | DOOR))
		rd_west(m);
	else if (m->map[m->d + (m->w)] & (CORRIDOR_B | DOOR))
		rd_south(m);
	else if (m->map[m->d - (m->w)] & (CORRIDOR_B | DOOR))
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

void	ft_random_init(t_max *max)
{
	t_rmap	m;
	int		i;
	int		j;
	int		p;

	srand(time(0));
	ft_map_init(max->map);
	map_init(&max->menu.rm, &m);
	// if (m.width < 3 || m.height < 3 || m.width > 125 || m.height > 125)
	// 	return (1);
	// if (m.x < 0 || m.l < 0 || m.t < 0 || m.e < 0 || m.rn < 0 || m.ro < 0
	// 	|| m.cw < 0 || m.dr < 0)
	// 	return (4);
	map_prefill2(&m);
	map_print("prefilled map", &m);
	maze_gen2(&m);
	maze_mod4(&m);
	map_print("indexed map", &m);
	add_rooms6(&m);
	map_print("added and opened rooms", &m);
	trim_deadends(&m);
	map_print("???trimmed deadeneds???", &m);
	map_refill42(&m);
	map_print("FINAL MAP", &m);
	map_print2("copy map", &m);
	i = 0;
	p = 1;
	j = 0;
	max->map->ww = m.w;
	max->map->w = 256;
	max->map->hh = m.h;
	max->map->h = 256;
	while (i < 65536)
	{
		if (j < m.s && (i % 256 < m.w))
		{
			if (m.map[j] & RWALL)
				max->map->m[i] = WALL1;
			if ((m.map[j] & CORRIDOR) || (m.map[j] & DOOR) || (m.map[j] & ROOM))
			{
				max->map->m[i] = FLOOR1;
				if (p)
				{
					max->map->p.mx = i % 256;
					max->map->p.my = i / 256;
					max->map->p.sx = 0x7f7f;
					max->map->p.sy = 0x7f7f;
					max->map->p.orientation = EAST;
					max->map->p.unused_x = 0;
					max->map->p.unused_y = 0;
					p = 0;
				}
			}
			++j;
		}
		++i;
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

int	ft_process_random(t_max *max)
{
	t_map	*map;

	map = max->map;
	ft_random_init(max);
	// if (!ft_read_map(map))
	// {
	// 	ft_freemap(map);
	// 	return (0);
	// }
	ft_fill_randommap(map);
	//no textures now
	// if (!ft_init_textures(max))
	// {
	// 	ft_freemap(map);
	// 	return (0);
	// }
	ft_init_brume(max);
	// int i;

	// i = 0;
	// while (i < 256)
	// {
	// 	ft_printf("%i %i", max->math->brumered[255][i], max->map->b.r);
	// 	ft_printf(" %i %i ", max->math->brumegreen[0][i], max->map->b.g);
	// 	ft_printf("%i %i\n", max->math->brumeblue[128][i], max->map->b.b);
	// 	++i;
	// }
	//for debugging
	ft_print_map(map);
	//ft_freemap(map);
	return (1);
}
