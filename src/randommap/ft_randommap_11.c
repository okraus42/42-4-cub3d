/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_11.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:13:25 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 16:14:23 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
