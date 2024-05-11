/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:53:46 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 15:54:42 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
