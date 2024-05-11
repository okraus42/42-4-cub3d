/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randommap_14.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:29:42 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 16:30:02 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	map_refill42(t_rmap *m)
{
	m->i = 0;
	while (m->i < m->s)
	{
		if (m->map[m->i] & RWALL)
			m->map[m->i] = RWALL_A;
		if (m->map[m->i] & CORRIDOR)
			m->map[m->i] = CORRIDOR_A;
		++(m->i);
	}
}
