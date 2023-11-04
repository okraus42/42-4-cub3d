/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraplusmazegen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:32:35 by okraus            #+#    #+#             */
/*   Updated: 2023/11/04 09:45:33 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/header/libft.h"
#include <math.h>
#include <time.h>

// compile with libft.a
// pass number for
// width, height, ratio of dead ends, loops, T-intersections, X-intersections
// notoverlapping room placement attempts, overlapping rooms placement attempts
// like 52 26 4 5 3 2 20 10
typedef	struct s_map
{
	int				width;		//input weight
	int				height;		//input heightH
	int				w;			//actual map width
	int				h;			//actual map height
	int				s;			//size, stop w*h
	int				i;			//iterating
	int				d;			//temp value
	int				p;			//actual position?
	int				walls;		//how many walls around actual position
	int				ends;		//how many dead ends in the maze originally
	int				e;			//how many dead ends left
	int				l;			//how many basic loops
	int				ll;
	int				t;			//how many t intersections from dead end
	int				tt;	
	int				x;			//how many x intersections from dead end
	int				xx;
	int				rn;			//how many attempts to build not an overlapping room
	int				ro;			//how many attempts to build an overlapping room
	int				rw;			//room width
	int				rh;			//room height
	int				ed;			//extra door probability
	int				dr;			//dead end removal (0 - keep dead ends, 1 - remove dead ends, n - remove n corridors from dead ends)
	int				loops;		//how many dead ends were changed int loops
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	colour;
	t_list			*lst;		//stack of visited positions (with neighbours?)
	t_list			*ltemp;		//temporaty list
	int				*temp;		//temporary value of position in the map
	unsigned int	map[16641];	//map up to 64*64
} t_map;

typedef enum e_map_block
{
	EDGE = 0x0,
	WALL_A = 0x1,		//WALL COLUMN, permanent wall except for 
	WALL_B = 0x2,		//WALL between columns
	WALL_C = 0x3,		//WALL between columns between two different areas
	DEADEND = 0x4,
	CORRIDOR_A = 0x5,	// corridor at junction place
	T_JUNCTION = 0x6,
	X_JUNCTION = 0x7,
	CORRIDOR_B = 0x8,	// corridor between two permawalls
	ROOM = 0x10,
	ROOM_A = 0x14,		//room 4
	DOOR_NS = 0x20,		// corridor at 
	DOOR_WE = 0x40,
	FLOOD = 0x1000,
	FLOOD_B = 0x2000
		
}	t_map_block;


// BETTER SOLUTION
// Do EDGES 2 walls thick
// typedef enum e_map_block
// {
// 	EDGE = 0x0,
// 	WALL_A = 0x10,		//WALL COLUMN, permanent wall except for 
// 	WALL_B = 0x20,		//WALL between columns
// 	WALL_C = 0x40,		//WALL between columns between two different areas

// 	DOOR_NS = 0x100,		// corridor at 
// 	DOOR_WE = 0x200,

// 	DEADEND = 0x1000,
// 	CORRIDOR_A = 0x2000,	// corridor at junction place
// 	T_JUNCTION = 0x4000,
// 	X_JUNCTION = 0x8000,
// 	CORRIDOR_B = 0x10000,	// corridor between two permawalls
// 	ROOM = 0x100000,
// 	ROOM_A = 0x200000,		//room 4
//	ROOM_B = 0x400000,

// 	FLOOD = 0x1000000,		//flood to index different areas
// 	FLOOD_B = 0x2000000		//flood to connect different areas
		
// }	t_map_block;

void	map_print(t_map *m)
{
	m->i = 0;

	while (m->i < m->s)
	{
		m->red = ((m->map[m->i] / 4) + 12 * m->map[m->i]) % 64 + 192;
		m->green = (32 + (m->map[m->i] / 4) + 34 * m->map[m->i]) % 64 + 192;
		m->blue = ((m->map[m->i] / 4) + m->map[m->i] * 16) % 64 + 192;
		m->colour = m->red << 16 | m->green << 8 | m->blue;
		/*if (m->i == m->p)
			ft_printf("XX", 0xffffff);*/
		if (m->map[m->i] == EDGE)
			ft_printf("%^*C  %0C", 0x000000);
		else if (m->map[m->i] == WALL_A)
			ft_printf("%^*C  %0C", 0x002222);
		else if (m->map[m->i] == WALL_B)
			ft_printf("%^*C  %0C", 0x444400);
		else if (m->map[m->i] == WALL_C)
			ft_printf("%^*C  %0C", 0x660066);
		else if (m->map[m->i] == DEADEND)
			ft_printf("%^*C  %0C", 0xff8888);
		else if (m->map[m->i] == CORRIDOR_A)
			ft_printf("%^*C  %0C", 0x999999);
		else if (m->map[m->i] == T_JUNCTION)
			ft_printf("%^*C  %0C", 0xaaffaa);
		else if (m->map[m->i] == X_JUNCTION)
			ft_printf("%^*C  %0C", 0xbbbbff);
		else if (m->map[m->i] == CORRIDOR_B)
			ft_printf("%^*C  %0C", 0xdddddd);
		else if (m->map[m->i] == ROOM)
			ft_printf("%^*C  %0C", 0xffffff);
		else if (m->map[m->i] == ROOM_A)
			ft_printf("%^*C  %0C", 0xffeeff);
		else if (m->map[m->i] == DOOR_NS)
			ft_printf("%^*C  %0C", 0xcc9966);
		else if (m->map[m->i] == DOOR_WE)
			ft_printf("%^*C  %0C", 0xcccc33);
		else if (m->map[m->i] & FLOOD)
			ft_printf("%^*C  %0C", m->colour);
		else if (m->map[m->i] & FLOOD_B)
			ft_printf("%^*C  %0C", 0xff0000);
		else
			ft_printf("%^*C  %0C", 0x222277);
		++(m->i);
		if (m->i % m->w == 0)
			ft_printf("\n");
	}
}

void	map_prefill(t_map *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if ((m->i / m->w) & 1 && !(m->i & 1))
			m->map[m->i] = 2;
		else if (m->i > m->w && m->i < (m->h - 1) * m->w
			&& m->i % m->w && m->i % m->w < (m->w - 1))
			m->map[m->i] = 1;
		else
			m->map[m->i] = 0;
		++(m->i);
	}
	m->i = 0;
	while (m->i < m->s)
	{
		if (!((m->i / m->w) & 1) && !(m->i & 1))
			m->map[m->i] = 0;
		++(m->i);
	}
}

void	map_prefill2(t_map *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		//ft_printf("%i\n", m->i);
		if ((m->i < m->w * 2) || (m->i > (m->w * (m->h - 2)))
			|| (m->i % m->w) < 2 || (m->i % m->w) > (m->w - 3))
			m->map[m->i] = EDGE;
		else if ((m->i / m->w) & 1 && !(m->i & 1))
			m->map[m->i] = FLOOD;
		else if (!((m->i / m->w) & 1) && !(m->i & 1))
			m->map[m->i] = WALL_A;
		else if (m->i > m->w && m->i < (m->h - 1) * m->w
			&& m->i % m->w && m->i % m->w < (m->w - 1))
			m->map[m->i] = WALL_B;
		else
			m->map[m->i] = FLOOD;
		++(m->i);
	}
}

int	mg_north(t_map *m)
{
	if (m->map[m->i - m->w] == 0 )	//	do not care about walls
		return (0);
	if (m->map[m->i - (m->w * 2)] == 2)
	{
		m->map[m->i - (m->w * 2)] = 16;
		m->map[m->i - (m->w)] = 8;
		return (m->i - (m->w * 2));
	}
	return (0);
}

int	mg_south(t_map *m)
{
	if (m->map[m->i + m->w] == 0)
		return (0);
	if (m->map[m->i + (m->w * 2)] == 2)
	{
		m->map[m->i + (m->w * 2)] = 32;
		m->map[m->i + (m->w)] = 8;
		return (m->i + (m->w * 2));
	}
	return (0);
}

int	mg_east(t_map *m)
{
	if (m->map[m->i + 1] == 0)
		return (0);
	if (m->map[m->i + 2] == 2)
	{
		m->map[m->i + 2] = 64;
		m->map[m->i + 1] = 8;
		return (m->i + 2);
	}
	return (0);
}

int	mg_west(t_map *m)
{
	if (m->map[m->i - 1] == 0)
		return (0);
	if (m->map[m->i - 2] == 2)
	{
		m->map[m->i - 2] = 128;
		m->map[m->i - 1] = 8;
		return (m->i - 2);
	}
	return (0);
}

int	check_unvisited_neighbours(t_map *m)
{
	if (m->map[m->p - 1] != 0 && m->map[m->p - 2] == 2)
		return (0);
	if (m->map[m->p + 1] != 0 && m->map[m->p + 2] == 2)
		return (0);
	if (m->map[m->p - m->w] != 0 && m->map[m->p - (m->w * 2)] == 2)
		return (0);
	if (m->map[m->p + m->w] != 0 && m->map[m->p + (m->w * 2)] == 2)
		return (0);
	return (1);
}

int	maze_gen(t_map *m)
{
	m->i = 0;
	srand(time(0));
	//init starting position for the alghoritm, make sure it is a valid position
	while (!((m->i / m->w) & 1 && !(m->i & 1)))
		m->i = rand() % (m->s);
	m->map[m->i] = 64;
	m->temp = malloc(sizeof(int));
	if (!m->temp)
		return (1);
	*m->temp = m->i;
	m->lst = ft_lstnew(m->temp);
	if (!m->lst)
		return (1);
	while (m->lst)
	{
		//ft_printf("i = %i\n", i);
		//map_print(map, w, h);
		//ft_printf("\n");
		m->d = rand() % 4;
		if (m->d == 0)		// maze North path expansion
			m->d = mg_north(m);
		else if (m->d == 1)	// maze East path expansion
			m->d = mg_east(m);
		else if (m->d == 2)	// maze South path expansion
			m->d = mg_south(m);
		else if (m->d == 3)	// maze West path expansion  
			m->d = mg_west(m);
		if (m->d)
		{
			//add new location to the list of active locations
			m->temp = malloc(sizeof(int));
			if (!m->temp)
				return (1);
			m->ltemp = ft_lstnew(m->temp);
			if (!m->ltemp)
				return (1);
			*m->temp = m->d;
			ft_lstadd_front(&m->lst, m->ltemp);
		}
		// check if newest list has neigbours if not remove from the list
		if (m->lst)
			m->p = *(int *)m->lst->content;
		while (m->lst && check_unvisited_neighbours(m))
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
	return (0);
}

void	map_refill(t_map *m)
{
	m->i = 0;
	m->ends = 0;
	while (m->i < m->s)
	{
		m->walls = 0;
		if (m->map[m->i] & 0xF0)
		{
			if (m->map[m->i - 1] != 0 && m->map[m->i - 1] == 1)
				m->walls++;
			if (m->map[m->i + 1] != 0 && m->map[m->i + 1] == 1)
				m->walls++;
			if (m->map[m->i - m->w] != 0 && m->map[m->i - m->w] == 1)
				m->walls++;
			if (m->map[m->i + m->w] != 0 && m->map[m->i + m->w] == 1)
				m->walls++;	
		}
		if (m->walls == 3)
		{
			m->map[m->i] = 4;
			m->ends++;
		}
		++(m->i);
	}
}

int	map_calculate(t_map *m)
{
	int	e;
	int	l;
	int	t;
	int	x;

	if (!m->ends || (!m->e && !m->l && !m->x && !m->t)) //avoid working with zero's
		return (1);
	m->d = m->ends << 8;  //shifted by 8 to lower division error
	e = m->e << 8;
	l = m->l << 8;
	t = m->t << 8;
	x = m->x << 8;
	m->e = ((m->d * e) / (e + l + t + x)) >> 8; //shifted back by 8 
	m->l = ((m->d * l) / (e + l + t + x)) >> 8;
	m->t = ((m->d * t) / (e + l + t + x)) >> 8;
	m->x = ((m->d * x) / (e + l + t + x)) >> 8;
	while ((m->e + m->l + m->t + m->x) < m->ends)	//increase the biggest 
	{												// number to match the	
		if (e >= l && e >= t && e >= x)				// number of ends
			m->e++;
		else if (l >= e && l >= t && l >= x)
			m->l++;
		else if (t >= e && t >= l && t >= x)
			m->t++;
		else
			m->x++;
	}
	/*ft_printf("ends: %i e: %i, l: %i, t: %i, x: %i \n",
		m->ends, m->e, m->l, m->t, m->x);*/
	return (0);
}

void	breakonewall(t_map *m)
{
	int	counter;
	
	counter = 1;
	while (counter && m->i < m->s)
	{
		m->d = rand() % 4;
		if (m->d == 0 && m->map[m->i - 1] == 1)
		{
			m->map[m->i - 1] = 8;
			counter = 0;
			//ft_printf("West wall  removed\n");
		}
		else if (m->d == 1 && m->map[m->i + 1] == 1)
		{
			m->map[m->i + 1] = 8;
			counter = 0;
			//ft_printf("East wall removed\n");
		}
		else if (m->d == 2 && m->map[m->i - m->w] == 1)
		{
			m->map[m->i - m->w] = 8;
			counter = 0;
			//ft_printf("North wall removed\n");
		}
		else if (m->d == 3 && m->map[m->i + m->w] == 1)
		{
			m->map[m->i + m->w] = 8;
			counter = 0;
			//ft_printf("South wall removed\n");
		}
		//if there are no walls because of the adjacend dead end was resolved,
		// skip breaking stage
		else if (m->map[m->i - 1] != 1 && m->map[m->i + 1] != 1
			&& m->map[m->i - m->w] != 1 && m->map[m->i + m->w] != 1) 
			counter = 0;
	}
	//ft_printf("wall removed\n");
}

void	wallbreaker(t_map *m)
{
	if (m->map[m->i] == DEADEND)
	{
		m->d = rand() % 8;
		// ft_printf("%d\n", m->d);
		// ft_printf("%i\n", m->i);
		// ft_printf("%i || 0 %i | 1 %i | 2 %i | 3 %i \n",  m->map[m->i], m->map[m->i - 1],
		// 	m->map[m->i + 1], m->map[m->i - m->w], m->map[m->i + m->w]);
		if (m->ll < m->l && (m->d & 4) && (m->d & 2) && (m->d & 1))
		{
			//ft_printf("making ll\n");
			breakonewall(m);
			//ft_printf("made ll\n");
			m->ll++;
			m->map[m->i] = CORRIDOR_A;
		}
		else if (m->tt < m->t && (m->d & 2) && (m->d & 1))
		{
			//ft_printf("making tt\n");
			breakonewall(m);
			breakonewall(m);
			//ft_printf("made tt\n");
			m->tt++;
			m->map[m->i] = T_JUNCTION;
		}
		else if (m->xx < m->x && (m->d & 1))
		{
			//ft_printf("making xx\n");
			breakonewall(m);
			breakonewall(m);
			breakonewall(m);
			//ft_printf("made xx\n");
			m->xx++;
			m->map[m->i] = X_JUNCTION;
		}
		// ft_printf("aaaa\n");
		// ft_printf("ends: %i e: %i, l: %i, t: %i, x: %i \n",
		// 	m->ends, m->e, m->l, m->t, m->x);
		// ft_printf("ends: %i e: %i, ll: %i, tt: %i, xx: %i \n",
		// 	m->ends, m->e, m->ll, m->tt, m->xx);
		// m->p = m->i;
		// map_print(m);
	}
}

void	map_loops(t_map *m)
{
	m->ll = 0;
	m->tt = 0;
	m->xx = 0;
	while (m->ll + m->tt + m->xx != m->l + m->t + m->x)
	{
		m->i = 0;
		while (m->i < m->s - 3)
		{
			wallbreaker(m);
			++(m->i);
			//ft_printf("%i\n", m->i);
		}
		
	}
}

void	maze_mod(t_map *m)
{
	map_refill(m);
	if (map_calculate(m))
		return ;
	map_loops(m);
}

void	map_refill2_temp(t_map *m)
{
	m->walls = 0;
	if (m->map[m->i + 1] == WALL_A || m->map[m->i + 1] == WALL_B || m->map[m->i + 1] == EDGE)
		m->walls++;
	if (m->map[m->i - 1] == WALL_A ||  m->map[m->i - 1] == WALL_B ||m->map[m->i - 1] == EDGE)
		m->walls++;
	if (m->map[m->i - m->w] == WALL_A || m->map[m->i - m->w] == WALL_B || m->map[m->i - m->w] == EDGE)
		m->walls++;
	if (m->map[m->i + m->w] == WALL_A || m->map[m->i + m->w] == WALL_B || m->map[m->i + m->w] == EDGE)
		m->walls++;
	if (!m->walls)
		m->map[m->i] = X_JUNCTION;
	else if (m->walls == 1)
		m->map[m->i] = T_JUNCTION;
	else if (m->walls == 2)
		m->map[m->i] = CORRIDOR_A;
	else if (m->walls == 3)
		m->map[m->i] = DEADEND;
	else if (m->walls == 4)
		m->map[m->i] = ROOM;
	else
		m->map[m->i] = WALL_C;
	//ft_printf("%i - %i - %i\n", m->i, m->walls, m->map[m->i]);
}

void	map_refill2_temp2(t_map *m)
{
	if (m->map[m->i] == WALL_A)
		m->map[m->i] = WALL_B;
}

void	map_refill2(t_map *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		//ft_printf("%i\n", m->i);
		if ((m->i < m->w) || (m->i > (m->w * (m->h - 1)))
			|| !(m->i % m->w) || (m->i % m->w) == (m->w - 1))
			m->map[m->i] = EDGE;
		else if ((m->i / m->w) & 1 && !(m->i & 1))
			map_refill2_temp(m);
		else if (!((m->i / m->w) & 1) && !(m->i & 1))
			m->map[m->i] = WALL_A;
		else if (m->i > m->w && m->i < (m->h - 1) * m->w
			&& m->i % m->w && m->i % m->w < (m->w - 1))
			map_refill2_temp2(m);	//check status;
		else
			m->map[m->i] = m->map[m->i];
		//ft_printf("%i\n", m->i);
		++(m->i);
	}
	m->i = 0;
	/*
	while (m->i < m->s)
	{
		if ((m->i < m->w) || (m->i > (m->w * (m->h - 1)))
			|| !(m->i % m->w) || (m->i % m->w) == (m->w - 1))
			m->map[m->i] = m->map[m->i];
		else if ((m->i / m->w) & 1 && !(m->i & 1))
			map_refill2_temp2(m);
		else if (!((m->i / m->w) & 1) && !(m->i & 1))
			m->map[m->i] = m->map[m->i];
		else if (m->i > m->w && m->i < (m->h - 1) * m->w
			&& m->i % m->w && m->i % m->w < (m->w - 1))
			map_refill2_temp(m);	//check status;
		else
			m->map[m->i] = ROOM;
		++(m->i);
	}*/
}

int	check_room_overlap(t_map *m, int x, int y)
{
	while (y < m->rh)	
	{
		x = 0;
		while (x < m->rw)
		{
			if (m->map[m->i + (y * m->w) + x] == 0)
				return (0);				
			++x;
		}
		++y;
	}
	return (1);
}

int	check_room_nooverlap(t_map *m, int x, int y)
{
	while (y < m->rh)	
	{
		x = 0;
		while (x < m->rw)
		{
			if (m->map[m->i + (y * m->w) + x] == 0
				|| m->map[m->i + (y * m->w) + x] == ROOM
				|| m->map[m->i + (y * m->w) + x] == ROOM_A)
				return (0);				
			++x;
		}
		++y;
	}
	return (1);
}

void	add_room(t_map *m, int x, int y)
{
	y = 0;
	while (y < m->rh)	
	{
		x = 0;
		while (x < m->rw)
		{
			if (m->map[m->i + (y * m->w) + x] & 4)
				m->map[m->i + (y * m->w) + x] =	ROOM_A;
			else
				m->map[m->i + (y * m->w) + x] =	ROOM;
			++x;
		}
		++y;
	}
}

void	add_rooms_overlap(t_map *m)
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
			if ((m->map[m->i] & 4) || (m->map[m->i] == ROOM_A))
				break;
		}
		m->rw = (rand() % 4) * 2 + 3;
		m->rh = (rand() % 4) * 2 + 3;
		if (check_room_overlap(m, x, y))
			add_room(m, x, y);
		++i;
	}
}

void	add_rooms_nooverlap(t_map *m)
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
			if ((m->map[m->i] & 4) || (m->map[m->i] == ROOM_A))
				break;
		}
		m->rw = (rand() % 4) * 2 + 3;
		m->rh = (rand() % 4) * 2 + 3;
		if (check_room_nooverlap(m, x, y))
			add_room(m, x, y);
		++i;
	}
}

void	add_room_walls(t_map *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if (m->map[m->i] == CORRIDOR_B)
		{
			if (m->map[m->i + 1] == ROOM_A || m->map[m->i - 1] == ROOM_A
				|| m->map[m->i - m->w] == ROOM_A
				|| m->map[m->i + m->w] == ROOM_A)
				m->map[m->i] = WALL_B;
		}

		++(m->i);
	}
}

void	keep_flooding(t_map *m, int i, unsigned int flood_value)
{
	if (m->map[i] > 3 && m->map[i] < 0x20)
		m->map[i] = flood_value;
	if (m->map[i - 1] > 3 && m->map[i - 1] < 0x20)
	{
		keep_flooding(m, i - 1, flood_value);
	}
	if (m->map[i + 1] > 3 && m->map[i + 1] < 0x20)
	{
		keep_flooding(m, i + 1, flood_value);
	}
	if (m->map[i - m->w] > 3 && m->map[i - m->w] < 0x20)
	{
		keep_flooding(m, i - m->w, flood_value);
	}
	if (m->map[i + m->w] > 3 && m->map[i + m->w] < 0x20)
	{
		keep_flooding(m, i + m->w, flood_value);
	}	
}

void	start_flooding(t_map *m)
{
	m->i = rand() % (3 * m->s / 4) + m->s / 8;
	while (m->map[m->i] < 4)
		++(m->i);
}

void	keep_flooding_2(t_map *m, int i, unsigned int flood_value)
{
	if (m->map[i] & FLOOD)
		m->map[i] = flood_value;
	if (m->map[i - 1] & FLOOD)
	{
		keep_flooding_2(m, i - 1, flood_value);
	}
	if (m->map[i + 1] & FLOOD)
	{
		keep_flooding_2(m, i + 1, flood_value);
	}
	if (m->map[i - m->w] & FLOOD)
	{
		keep_flooding_2(m, i - m->w, flood_value);
	}
	if (m->map[i + m->w] & FLOOD)
	{
		keep_flooding_2(m, i + m->w, flood_value);
	}	
}

int	flood_check(t_map *m)
{
	(void)m;
	return (0);
}

void	connect_rooms(t_map *m)
{
	map_print(m);
	//start flooding
	//
	//while (flood_check)
	m->i = 0;
	m->d = -1;
	while (m->i < m->s)
	{
		if (m->map[m->i] > 3 && m->map[m->i] < 0x20)
		{
			++(m->d);
			keep_flooding(m, m->i, FLOOD + m->d);
		}
		++m->i;
	}
	start_flooding(m);
	keep_flooding_2(m , m->i, FLOOD_B);
	//create openings
	//open doors at random
	//close openings
	//keep flooding
}

void	add_rooms(t_map *m)
{
	map_refill2(m);
	//try to add non overlaping rooms and overlapping
	add_rooms_nooverlap(m);
	add_rooms_overlap(m);
	//put walls around rooms
	add_room_walls(m);
	//connect rooms
	connect_rooms(m);	
}


int	mg_north2(t_map *m)
{
	if (m->map[m->i - (m->w * 2)] == FLOOD)
	{
		m->map[m->i - (m->w * 2)] = FLOOD_B;
		m->map[m->i - (m->w)] = CORRIDOR_B;
		return (m->i - (m->w * 2));
	}
	return (0);
}

int	mg_south2(t_map *m)
{
	if (m->map[m->i + (m->w * 2)] == FLOOD)
	{
		m->map[m->i + (m->w * 2)] = FLOOD_B;
		m->map[m->i + (m->w)] = CORRIDOR_B;
		return (m->i + (m->w * 2));
	}
	return (0);
}

int	mg_east2(t_map *m)
{
	if (m->map[m->i + 2] == FLOOD)
	{
		m->map[m->i + 2] = FLOOD_B;
		m->map[m->i + 1] = CORRIDOR_B;
		return (m->i + 2);
	}
	return (0);
}

int	mg_west2(t_map *m)
{
	if (m->map[m->i - 2] == FLOOD)
	{
		m->map[m->i - 2] = FLOOD_B;
		m->map[m->i - 1] = CORRIDOR_B;
		return (m->i - 2);
	}
	return (0);
}

int	check_unvisited_neighbours2(t_map *m)
{
	if (m->map[m->p - 2] == FLOOD)
		return (0);
	if (m->map[m->p + 2] == FLOOD)
		return (0);
	if (m->map[m->p - (m->w * 2)] == FLOOD)
		return (0);
	if (m->map[m->p + (m->w * 2)] == FLOOD)
		return (0);
	return (1);
}

int	maze_gen2(t_map *m)
{
	m->i = 0;
	srand(time(0));
	//init starting position for the alghoritm, make sure it is a valid position
	while (!(m->map[m->i] & FLOOD))
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
		//ft_printf("i = %i\n", i);
		//map_print(map, w, h);
		//ft_printf("\n");
		m->d = rand() % 4;
		if (m->d == 0)		// maze North path expansion
			m->d = mg_north2(m);
		else if (m->d == 1)	// maze East path expansion
			m->d = mg_east2(m);
		else if (m->d == 2)	// maze South path expansion
			m->d = mg_south2(m);
		else if (m->d == 3)	// maze West path expansion  
			m->d = mg_west2(m);
		if (m->d)
		{
			//add new location to the list of active locations
			m->temp = malloc(sizeof(int));
			if (!m->temp)
				return (1);
			m->ltemp = ft_lstnew(m->temp);
			if (!m->ltemp)
				return (1);
			*m->temp = m->d;
			ft_lstadd_front(&m->lst, m->ltemp);
		}
		// check if newest list has neigbours if not remove from the list
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
	return (0);
}


void	map_refill4(t_map *m)
{
	m->i = 0;
	m->ends = 0;
	while (m->i < m->s)
	{
		m->walls = 0;
		if (m->map[m->i] & FLOOD_B)
		{
			if (m->map[m->i - 1] == WALL_B)
				m->walls++;
			if (m->map[m->i + 1] == WALL_B)
				m->walls++;
			if (m->map[m->i - m->w] == WALL_B)
				m->walls++;
			if (m->map[m->i + m->w] == WALL_B)
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

int	map_calculate4(t_map *m)
{
	int	e;
	int	l;
	int	t;
	int	x;

	if (!m->ends || (!m->e && !m->l && !m->x && !m->t)) //avoid working with zero's
		return (1);
	m->d = m->ends << 8;  //shifted by 8 to lower division error
	e = m->e << 8;
	l = m->l << 8;
	t = m->t << 8;
	x = m->x << 8;
	m->e = ((m->d * e) / (e + l + t + x)) >> 8; //shifted back by 8 
	m->l = ((m->d * l) / (e + l + t + x)) >> 8;
	m->t = ((m->d * t) / (e + l + t + x)) >> 8;
	m->x = ((m->d * x) / (e + l + t + x)) >> 8;
	while ((m->e + m->l + m->t + m->x) < m->ends)	//increase the biggest 
	{												// number to match the	
		if (e >= l && e >= t && e >= x)				// number of ends
			m->e++;
		else if (l >= e && l >= t && l >= x)
			m->l++;
		else if (t >= e && t >= l && t >= x)
			m->t++;
		else
			m->x++;
	}
	return (0);
}

void	breakonewall4(t_map *m)
{
	int	counter;
	
	counter = 1;
	while (counter && m->i < m->s) //second condition makes no sense, added because of bug in code while debugging
	{
		m->d = rand() % 4;
		if (m->d == 0 && m->map[m->i - 1] == WALL_B)
		{
			m->map[m->i - 1] = CORRIDOR_B;
			counter = 0;
			//ft_printf("West wall  removed\n");
		}
		else if (m->d == 1 && m->map[m->i + 1] == WALL_B)
		{
			m->map[m->i + 1] = CORRIDOR_B;
			counter = 0;
			//ft_printf("East wall removed\n");
		}
		else if (m->d == 2 && m->map[m->i - m->w] == WALL_B)
		{
			m->map[m->i - m->w] = CORRIDOR_B;
			counter = 0;
			//ft_printf("North wall removed\n");
		}
		else if (m->d == 3 && m->map[m->i + m->w] == WALL_B)
		{
			m->map[m->i + m->w] = CORRIDOR_B;
			counter = 0;
			//ft_printf("South wall removed\n");
		}
		//if there are no walls because of the adjacend dead end was resolved,
		// skip breaking stage
		else if (m->map[m->i - 1] != WALL_B && m->map[m->i + 1] != WALL_B
			&& m->map[m->i - m->w] != WALL_B && m->map[m->i + m->w] != WALL_B) 
			counter = 0;
	}
	//ft_printf("wall removed\n");
}

void	wallbreaker4(t_map *m)
{
	if (m->map[m->i] == DEADEND)
	{
		m->d = rand() % 8;
		// ft_printf("%d\n", m->d);
		// ft_printf("%i\n", m->i);
		// ft_printf("%i || 0 %i | 1 %i | 2 %i | 3 %i \n",  m->map[m->i], m->map[m->i - 1],
		// 	m->map[m->i + 1], m->map[m->i - m->w], m->map[m->i + m->w]);
		if (m->ll < m->l && (m->d & 4) && (m->d & 2) && (m->d & 1))
		{
			//ft_printf("making ll\n");
			breakonewall4(m);
			//ft_printf("made ll\n");
			m->ll++;
			m->map[m->i] = CORRIDOR_A;
		}
		else if (m->tt < m->t && (m->d & 2) && (m->d & 1))
		{
			//ft_printf("making tt\n");
			breakonewall4(m);
			breakonewall4(m);
			//ft_printf("made tt\n");
			m->tt++;
			m->map[m->i] = T_JUNCTION;
		}
		else if (m->xx < m->x && (m->d & 1))
		{
			//ft_printf("making xx\n");
			breakonewall4(m);
			breakonewall4(m);
			breakonewall4(m);
			//ft_printf("made xx\n");
			m->xx++;
			m->map[m->i] = X_JUNCTION;
		}
		// ft_printf("aaaa\n");
		// ft_printf("ends: %i e: %i, l: %i, t: %i, x: %i \n",
		// 	m->ends, m->e, m->l, m->t, m->x);
		// ft_printf("ends: %i e: %i, ll: %i, tt: %i, xx: %i \n",
		// 	m->ends, m->e, m->ll, m->tt, m->xx);
		// m->p = m->i;
		// map_print(m);
	}
}

void	map_loops4(t_map *m)
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
			//ft_printf("%i\n", m->i);
		}
		
	}
}

void	map_refill5(t_map *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if (m->map[m->i] & CORRIDOR_B)
		{
			if (!(m->map[m->i - 1]) || !(m->map[m->i + 1])
				|| !(m->map[m->i + m->w])
				|| !(m->map[m->i - m->w]))
				m->map[m->i] = WALL_B;
		}
		++(m->i);
	}
	m->i = 0;
	m->ends = 0;
	while (m->i < m->s)
	{
		m->walls = 0;
		//edit this condition later
		if (m->map[m->i] == FLOOD_B || m->map[m->i] == CORRIDOR_A
			|| m->map[m->i] == DEADEND || m->map[m->i] == T_JUNCTION
			|| m->map[m->i] == X_JUNCTION)
		{
			if (m->map[m->i - 1] == WALL_B)
				m->walls++;
			if (m->map[m->i + 1] == WALL_B)
				m->walls++;
			if (m->map[m->i - m->w] == WALL_B)
				m->walls++;
			if (m->map[m->i + m->w] == WALL_B)
				m->walls++;	
			if (m->walls == 3)
			{
				m->map[m->i] = DEADEND;
				m->ends++;
			}
			if (m->walls == 2)
			{
				m->map[m->i] = CORRIDOR_A;
				m->ends++;
			}
			if (m->walls == 1)
			{
				m->map[m->i] = T_JUNCTION;
				m->ends++;
			}
			if (m->walls == 0)
			{
				m->map[m->i] = X_JUNCTION;
				m->ends++;
			}
		}
		++(m->i);
	}
}

void	maze_mod4(t_map *m)
{
	map_refill4(m);
	map_print(m);
	if (map_calculate4(m))
		return ;
	map_print(m);
	map_loops4(m);
	map_print(m);
	map_refill5(m);
}

int	main(int ac, char *av[])
{
	/*int				width;
	int				height;
	unsigned char	map[16641];*/
	t_map			m;

	if (ac != 9)
		return (2);
	m.width = ft_atoi(av[1]);
	m.height = ft_atoi(av[2]);
	m.e = ft_atoi(av[3]);
	m.l = ft_atoi(av[4]);
	m.t = ft_atoi(av[5]);
	m.x = ft_atoi(av[6]);
	m.rn = ft_atoi(av[7]);
	m.ro = ft_atoi(av[8]);
	m.w = m.width * 2 + 5;
	m.h = m.height * 2 + 5;
	m.s = m.w * m.h;
	if (m.width < 3 || m.height < 3 || m.width > 64 || m.height > 64)
		return (1);
	if (m.x < 0 || m.l < 0 || m.t < 0 || m.e < 0)
		return (4);
	map_prefill(&m);
	map_print(&m);
	//prefill map
	//create maze
	maze_gen(&m);
	map_print(&m);
	//add loops and intersections
	maze_mod(&m);
	map_print(&m);
	//add rooms (attempts & overlaps)
	add_rooms(&m);
	map_print(&m);
	//trim deadends (0 no, 1 yes, n specific number of corritdors is removed )
	

	map_prefill2(&m);
	map_print(&m);
	maze_gen2(&m);
	maze_mod4(&m);
	map_print(&m);
	//print maze
	map_print(&m);
	return (0);
}
