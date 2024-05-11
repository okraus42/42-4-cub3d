/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_9.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:02:37 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 16:03:10 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
		m->map[i] = RDOOR_NS;
	else
		m->map[i] = RDOOR_WE;
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
