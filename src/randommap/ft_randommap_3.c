/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:44:31 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 15:45:17 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	map_print_inner(t_rmap *m, int i)
{
	if (m->map[i] == EDGE)
		ft_printf("%^*C  %0C", 0x000000);
	else if (m->map[i] == RWALL_A)
		ft_printf("%^*C  %0C", 0x002222);
	else if (m->map[i] == RWALL_B)
		ft_printf("%^*C  %0C", 0x444400);
	else if (m->map[i] == RWALL_C || m->map[i] == RWALL_D)
		ft_printf("%^*C  %0C", 0x330033);
	else if (m->map[i] == CORRIDOR_A)
		ft_printf("%^*C  %0C", 0x999999);
	else if (m->map[i] == T_JUNCTION || m->map[i] == X_JUNCTION
		|| m->map[i] == DEADEND)
		ft_printf("%^*C  %0C", 0xaaffaa);
	else if (m->map[i] == CORRIDOR_B)
		ft_printf("%^*C  %0C", 0xdddddd);
	else if (m->map[i] == ROOM_A || m->map[i] == ROOM_B)
		ft_printf("%^*C  %0C", 0xffeeff);
	else if (m->map[i] == RDOOR_NS || m->map[i] == RDOOR_WE)
		ft_printf("%.*^*C--%0C", 0, 0xcc9966);
	else if (m->map[i] & FLOOD_A)
		ft_printf("%^*C  %0C", m->colour);
	else if (m->map[i] & FLOOD_B)
		ft_printf("%^*C  %0C", 0xff0000);
	else
		ft_printf("%^*C  %0C", 0x222277);
}

void	map_print(char *str, t_rmap *m)
{
	int	i;

	i = 0;
	if (str)
		ft_printf("%s\n", str);
	while (i < m->s)
	{
		m->red = ((m->map[i] / 4) + 12 * m->map[i]) % 64 + 192;
		m->green = (32 + (m->map[i] / 4) + 34 * m->map[i]) % 64 + 192;
		m->blue = ((m->map[i] / 4) + m->map[i] * 16) % 64 + 192;
		m->colour = m->red << 16 | m->green << 8 | m->blue;
		map_print_inner(m, i);
		++(i);
		if (i % m->w == 0)
			ft_printf("\n");
	}
}

void	map_print2(char *str, t_rmap *m)
{
	int	i;

	i = 0;
	if (str)
		ft_printf("%s\n", str);
	while (i < m->s)
	{
		m->red = ((m->map[i] / 4) + 12 * m->map[i]) % 64 + 192;
		m->green = (32 + (m->map[i] / 4) + 34 * m->map[i]) % 64 + 192;
		m->blue = ((m->map[i] / 4) + m->map[i] * 16) % 64 + 192;
		m->colour = m->red << 16 | m->green << 8 | m->blue;
		if (m->map[i] == EDGE)
			ft_printf(" ");
		else if (m->map[i] == RWALL_A || m->map[i] == RWALL_B
			|| m->map[i] == RWALL_C || m->map[i] == RWALL_D)
			ft_printf("1");
		else
			ft_printf("0");
		++(i);
		if (i % m->w == 0)
			ft_printf("\n");
	}
}

void	map_prefill2(t_rmap *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if ((m->i < m->w * 2) || (m->i > (m->w * (m->h - 2)))
			|| (m->i % m->w) < 2 || (m->i % m->w) > (m->w - 3))
			m->map[m->i] = EDGE;
		else if ((m->i / m->w) & 1 && !(m->i & 1))
			m->map[m->i] = FLOOD_A;
		else if (!((m->i / m->w) & 1) && !(m->i & 1))
			m->map[m->i] = RWALL_A;
		else if (m->i > m->w && m->i < (m->h - 1) * m->w
			&& m->i % m->w && m->i % m->w < (m->w - 1))
			m->map[m->i] = RWALL_B;
		else
			m->map[m->i] = FLOOD_A;
		++(m->i);
	}
}

int	mg_north2(t_rmap *m)
{
	if (m->map[m->i - (m->w * 2)] == FLOOD_A)
	{
		m->map[m->i - (m->w * 2)] = FLOOD_B;
		m->map[m->i - (m->w)] = CORRIDOR_B;
		return (m->i - (m->w * 2));
	}
	return (0);
}
