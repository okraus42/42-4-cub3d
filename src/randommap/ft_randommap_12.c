/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_12.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:20:24 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 16:21:10 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	rd_west(t_rmap *m)
{
	if (m->map[m->d - 2] == CORRIDOR_A)
	{
		m->map[m->d - 2] = DEADEND;
		m->map[m->d - 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
		m->d = m->d - 2;
		remove_deadend(m);
	}
	else if (m->map[m->d - 2] == T_JUNCTION)
	{
		m->map[m->d - 2] = CORRIDOR_A;
		m->map[m->d - 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d - 2] == X_JUNCTION)
	{
		m->map[m->d - 2] = T_JUNCTION;
		m->map[m->d - 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d - 2] & ROOM)
	{
		m->map[m->d - 1] = RWALL_B;
		m->map[m->d] = RWALL_D;
	}
}

void	rd_east(t_rmap *m)
{
	if (m->map[m->d + 2] == CORRIDOR_A)
	{
		m->map[m->d + 2] = DEADEND;
		m->map[m->d + 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
		m->d = m->d + 2;
		remove_deadend(m);
	}
	else if (m->map[m->d + 2] == T_JUNCTION)
	{
		m->map[m->d + 2] = CORRIDOR_A;
		m->map[m->d + 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d + 2] == X_JUNCTION)
	{
		m->map[m->d + 2] = T_JUNCTION;
		m->map[m->d + 1] = RWALL_D;
		m->map[m->d] = RWALL_D;
	}
	else if (m->map[m->d + 2] & ROOM)
	{
		m->map[m->d + 1] = RWALL_B;
		m->map[m->d] = RWALL_D;
	}
}

void	remove_deadend(t_rmap *m)
{
	if (m->map[m->d + 1] & (CORRIDOR_B | RDOOR))
		rd_east(m);
	else if (m->map[m->d - 1] & (CORRIDOR_B | RDOOR))
		rd_west(m);
	else if (m->map[m->d + (m->w)] & (CORRIDOR_B | RDOOR))
		rd_south(m);
	else if (m->map[m->d - (m->w)] & (CORRIDOR_B | RDOOR))
		rd_north(m);
}

void	process_deadends(t_rmap	*m)
{
	int	r;

	while (m->lst)
	{
		r = rand() % 1024;
		m->ltemp = m->lst->next;
		m->d = *(int *)m->lst->content;
		if (m->dr == 1 || (m->dr > r))
			remove_deadend(m);
		ft_lstdelone(m->lst, free);
		m->lst = m->ltemp;
	}
}

void	trim_deadends(t_rmap *m)
{
	map_refill999(m);
	map_refill5(m);
	map_print("refilled map", m);
	list_deadends(m);
	process_deadends(m);
	map_print("trimmed ends", m);
}
