/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plusmazegen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:32:35 by okraus            #+#    #+#             */
/*   Updated: 2023/11/01 19:10:32 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/header/libft.h"
#include <math.h>
#include <time.h>

// compile with libft.a
// pass number for
// width, height, ratio of dead ends, loops, T-intersections, X-intersections
// like 52 26 4 5 3 2
typedef	struct s_map
{
	int				width;		//input weight
	int				height;		//input height
	int				w;			//actual map width
	int				h;			//actual map height
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
	int				loops;		//how many dead ends were changed int loops
	t_list			*lst;		//stack of visited positions (with neighbours?)
	t_list			*ltemp;		//temporaty list
	int				*temp;		//temporary value of position in the map
	unsigned char	map[16641];	//map up to 64*64
} t_map;


void	map_print(t_map *m)
{
	m->i = 0;
	while (m->i < m->w * m->h)
	{
		/*if (m->i == m->p)
			ft_printf("XX", 0xffffff);*/
		if (m->map[m->i] == 0)
			ft_printf("%^*C  %0C", 0x000000);
		else if (m->map[m->i] == 1)
			ft_printf("%^*C  %0C", 0x555555);
		else if (m->map[m->i] == 2)
			ft_printf("%^*C  %0C", 0xcccccc);
		else if (m->map[m->i] == 4)
			ft_printf("%^*C  %0C", 0xffffff);
		else if (m->map[m->i] == 5)
			ft_printf("%^*C  %0C", 0x00ffff);
		else if (m->map[m->i] == 6)
			ft_printf("%^*C  %0C", 0xff00ff);
		else if (m->map[m->i] == 7)
			ft_printf("%^*C  %0C", 0xffff00);
		else if (m->map[m->i] == 8)
			ft_printf("%^*C  %0C", 0xaaaaaa);
		else if (m->map[m->i] == 16)
			ft_printf("%^*C  %0C", 0xccaaaa);
		else if (m->map[m->i] == 32)
			ft_printf("%^*C  %0C", 0xaaccaa);
		else if (m->map[m->i] == 64)
			ft_printf("%^*C  %0C", 0xaacccc);
		else if (m->map[m->i] == 128)
			ft_printf("%^*C  %0C", 0xccaacc);
		++(m->i);
		if (m->i % m->w == 0)
			ft_printf("\n");
	}
}

void	map_prefill(t_map *m)
{
	m->i = 0;
	while (m->i < m->w * m->h)
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
	while (m->i < m->w * m->h)
	{
		if (!((m->i / m->w) & 1) && !(m->i & 1))
			m->map[m->i] = 0;
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
		m->i = rand() % (m->w * m->h);
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
	while (m->i < m->w * m->h)
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
	while (counter && m->i < m->w * m->h)
	{
		m->d = rand() % 4;
		if (m->d == 0 && m->map[m->i - 1] == 1)
		{
			m->map[m->i - 1] = 8;
			counter = 0;
			ft_printf("West wall  removed\n");
		}
		else if (m->d == 1 && m->map[m->i + 1] == 1)
		{
			m->map[m->i + 1] = 8;
			counter = 0;
			ft_printf("East wall removed\n");
		}
		else if (m->d == 2 && m->map[m->i - m->w] == 1)
		{
			m->map[m->i - m->w] = 8;
			counter = 0;
			ft_printf("North wall removed\n");
		}
		else if (m->d == 3 && m->map[m->i + m->w] == 1)
		{
			m->map[m->i + m->w] = 8;
			counter = 0;
			ft_printf("South wall removed\n");
		}
		//if there are no walls because of the adjacend dead end was resolved,
		// skip breaking stage
		else if (m->map[m->i - 1] != 1 && m->map[m->i + 1] != 1
			&& m->map[m->i - m->w] != 1 && m->map[m->i + m->w] != 1) 
			counter = 0;
	}
	ft_printf("wall removed\n");
}

void	wallbreaker(t_map *m)
{
	if (m->map[m->i] == 4)
	{
		m->d = rand() % 8;
		// ft_printf("%d\n", m->d);
		// ft_printf("%i\n", m->i);
		// ft_printf("%i || 0 %i | 1 %i | 2 %i | 3 %i \n",  m->map[m->i], m->map[m->i - 1],
		// 	m->map[m->i + 1], m->map[m->i - m->w], m->map[m->i + m->w]);
		if (m->ll < m->l && (m->d & 4) && (m->d & 2) && (m->d & 1))
		{
			ft_printf("making ll\n");
			breakonewall(m);
			ft_printf("made ll\n");
			m->ll++;
			m->map[m->i] = 5;
		}
		else if (m->tt < m->t && (m->d & 2) && (m->d & 1))
		{
			ft_printf("making tt\n");
			breakonewall(m);
			breakonewall(m);
			ft_printf("made tt\n");
			m->tt++;
			m->map[m->i] = 6;
		}
		else if (m->xx < m->x && (m->d & 1))
		{
			ft_printf("making xx\n");
			breakonewall(m);
			breakonewall(m);
			breakonewall(m);
			ft_printf("made xx\n");
			m->xx++;
			m->map[m->i] = 7;
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
		while (m->i < m->w * m->h - 3)
		{
			wallbreaker(m);
			++(m->i);
			ft_printf("%i\n", m->i);
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

int	main(int ac, char *av[])
{
	/*int				width;
	int				height;
	unsigned char	map[16641];*/
	t_map			m;

	if (ac != 7)
		return (2);
	m.width = ft_atoi(av[1]);
	m.height = ft_atoi(av[2]);
	m.e = ft_atoi(av[3]);
	m.l = ft_atoi(av[4]);
	m.t = ft_atoi(av[5]);
	m.x = ft_atoi(av[6]);
	m.w = m.width * 2 + 1;
	m.h = m.height * 2 + 1;
	if (m.width < 3 || m.height < 3 || m.width > 64 || m.height > 64)
		return (1);
	if (m.x < 0 || m.l < 0 || m.t < 0 || m.e < 0)
		return (4);
	map_prefill(&m);
	//prefill map
	//create maze
	maze_gen(&m);
	maze_mod(&m);
	//print maze
	map_print(&m);
	return (0);
}
