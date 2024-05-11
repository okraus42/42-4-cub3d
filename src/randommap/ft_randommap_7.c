/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:56:26 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 15:56:53 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
