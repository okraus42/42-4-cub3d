/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_10.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:05:10 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 16:06:16 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
