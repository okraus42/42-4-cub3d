/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:58:40 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 15:59:29 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
