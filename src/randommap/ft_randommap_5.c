/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:51:07 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 15:51:45 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
