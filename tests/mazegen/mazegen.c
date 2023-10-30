/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mazegen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:32:35 by okraus            #+#    #+#             */
/*   Updated: 2023/10/30 17:54:55 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/header/libft.h"
#include <math.h>
#include <time.h>

// compile with libft.a
// pass number for width and height like 52 26
typedef	struct s_map
{
	int				width;		//input weight
	int				height;		//input height
	int				w;			//actual map width
	int				h;			//actual map height
	int				i;			//iterating
	int				d;			//temp value
	int				p;			//actual position?
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
		if (m->map[m->i] == 0)
			ft_printf("%^*C  %0C", 0x000000);
		else if (m->map[m->i] == 1)
			ft_printf("%^*C  %0C", 0x333333);
		else if (m->map[m->i] == 2)
			ft_printf("%^*C  %0C", 0x777777);
		else if (m->map[m->i] == 4)
			ft_printf("%^*C  %0C", 0xffffff);
		else if (m->map[m->i] == 8)
			ft_printf("%^*C  %0C", 0x555555);
		else if (m->map[m->i] == 16)
			ft_printf("%^*C  %0C", 0x775555);
		else if (m->map[m->i] == 32)
			ft_printf("%^*C  %0C", 0x557755);
		else if (m->map[m->i] == 64)
			ft_printf("%^*C  %0C", 0x557777);
		else if (m->map[m->i] == 128)
			ft_printf("%^*C  %0C", 0x775577);
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
	m->map[m->i] = 4;
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

int	main(int ac, char *av[])
{
	/*int				width;
	int				height;
	unsigned char	map[16641];*/
	t_map			m;

	if (ac != 3)
		return (2);
	m.width = ft_atoi(av[1]);
	m.height = ft_atoi(av[2]);
	m.w = m.width * 2 + 1;
	m.h = m.height * 2 + 1;
	if (m.width < 3 || m.height < 3 || m.width > 64 || m.height > 64)
		return (1);
	map_prefill(&m);
	//prefill map
	//create maze
	maze_gen(&m);
	//print maze
	map_print(&m);
	return (0);
}