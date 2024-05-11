/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:47:28 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 15:47:59 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	mg_south2(t_rmap *m)
{
	if (m->map[m->i + (m->w * 2)] == FLOOD_A)
	{
		m->map[m->i + (m->w * 2)] = FLOOD_B;
		m->map[m->i + (m->w)] = CORRIDOR_B;
		return (m->i + (m->w * 2));
	}
	return (0);
}

int	mg_east2(t_rmap *m)
{
	if (m->map[m->i + 2] == FLOOD_A)
	{
		m->map[m->i + 2] = FLOOD_B;
		m->map[m->i + 1] = CORRIDOR_B;
		return (m->i + 2);
	}
	return (0);
}

int	mg_west2(t_rmap *m)
{
	if (m->map[m->i - 2] == FLOOD_A)
	{
		m->map[m->i - 2] = FLOOD_B;
		m->map[m->i - 1] = CORRIDOR_B;
		return (m->i - 2);
	}
	return (0);
}

int	check_unvisited_neighbours2(t_rmap *m)
{
	if (m->map[m->p - 2] == FLOOD_A)
		return (0);
	if (m->map[m->p + 2] == FLOOD_A)
		return (0);
	if (m->map[m->p - (m->w * 2)] == FLOOD_A)
		return (0);
	if (m->map[m->p + (m->w * 2)] == FLOOD_A)
		return (0);
	return (1);
}

int	maze_expand(t_rmap *m)
{
	m->d = rand() % 4;
	if (m->d == 0)
		m->d = mg_north2(m);
	else if (m->d == 1)
		m->d = mg_east2(m);
	else if (m->d == 2)
		m->d = mg_south2(m);
	else if (m->d == 3)
		m->d = mg_west2(m);
	if (m->d)
	{
		m->temp = malloc(sizeof(int));
		if (!m->temp)
			return (1);
		m->ltemp = ft_lstnew(m->temp);
		if (!m->ltemp)
			return (1);
		*m->temp = m->d;
		ft_lstadd_front(&m->lst, m->ltemp);
	}
	return (0);
}
