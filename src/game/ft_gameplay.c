/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameplay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:47:00 by okraus            #+#    #+#             */
/*   Updated: 2024/05/10 13:30:38 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_change_light_dist(t_max *max)
{
	if (max->keys[MLX_KEY_LEFT_BRACKET])
	{
		max->keys[MLX_KEY_LEFT_BRACKET] = 0;
		max->settings.lightdist -= 65536;
		if (max->settings.lightdist < 65536 * 2)
			max->settings.lightdist = 65536 * 2;
		ft_init_fogscreen(max);
	}
	if (max->keys[MLX_KEY_RIGHT_BRACKET])
	{
		max->keys[MLX_KEY_RIGHT_BRACKET] = 0;
		max->settings.lightdist += 65536;
		if (max->settings.lightdist > max->settings.maxdist)
			max->settings.lightdist = max->settings.maxdist;
		ft_init_fogscreen(max);
	}
}

void	ft_gameplay_2(t_max *max)
{
	max->score -= max->framems;
	max->map.p.turnspeed = max->framems * 8;
	max->map.p.speed = MIN(4 * 8 * 128, 128 * 8 * max->framems);
	max->map.p.xspeed = (max->map.p.speed * max->math->cos[max->map.p
			.orientation]) / 65536;
	max->map.p.yspeed = -(max->map.p.speed * max->math->sin[max->map.p
			.orientation]) / 65536;
	++max->frame;
	if (max->i.maximap->enabled)
		max->levelms += (max->framems);
	max->levelms += (max->framems * (256ULL * max->settings
				.lightdist) / (max->settings.maxdist / 4)) / 256ULL;
	max->map.p.dx = -max->math->sin[max->map.p.orientation];
	max->map.p.dy = -max->math->cos[max->map.p.orientation];
	max->map.p.cx = max->math->cos[max->map.p.orientation];
	max->map.p.cy = max->math->sin[max->map.p.orientation];
}

void	ft_gameplay_3(t_max *max)
{
	if (max->keys[MLX_KEY_LEFT_SHIFT])
	{
		max->map.p.xspeed *= 2;
		max->map.p.yspeed *= 2;
		max->map.p.turnspeed /= 2;
	}
	if (max->keys[MLX_KEY_UP] || max->keys[MLX_KEY_W])
		ft_move_player(&max->map, max->map.p.y - max->map.p.xspeed,
			max->map.p.x - max->map.p.yspeed);
	if (max->keys[MLX_KEY_DOWN] || max->keys[MLX_KEY_S])
		ft_move_player(&max->map, max->map.p.y + max->map.p.xspeed,
			max->map.p.x + max->map.p.yspeed);
	if (max->keys[MLX_KEY_A])
		ft_move_player(&max->map, max->map.p.y + max->map.p.yspeed,
			max->map.p.x - max->map.p.xspeed);
	if (max->keys[MLX_KEY_D])
		ft_move_player(&max->map, max->map.p.y - max->map.p.yspeed,
			max->map.p.x + max->map.p.xspeed);
	if (max->keys[MLX_KEY_LEFT] || max->keys[MLX_KEY_Q])
	{
		max->map.p.orientation -= max->map.p.turnspeed;
		if (max->map.p.orientation < 0)
			max->map.p.orientation += MAXDEGREE;
	}
}

void	ft_gameplay_4(t_max *max)
{
	if (max->keys[MLX_KEY_RIGHT] || max->keys[MLX_KEY_E])
	{
		max->map.p.orientation += max->map.p.turnspeed;
		if (max->map.p.orientation >= MAXDEGREE)
			max->map.p.orientation -= MAXDEGREE;
	}
	ft_visit_map(&max->map, 16, 256, (max->map.p.x >> 16)
		+ ((max->map.p.y >> 16) * max->map.w));
	if (max->keys[MLX_KEY_SPACE])
	{
		max->map.p.reveal = 1;
		max->limitms -= 15000;
		max->timetriallimitms -= 15000;
		max->keys[MLX_KEY_SPACE] = 0;
	}
	if (max->keys[MLX_KEY_TAB])
	{
		ft_discover_full_map(&max->map);
		max->limitms -= 60000;
		max->timetriallimitms -= 60000;
		max->keys[MLX_KEY_TAB] = 0;
	}
}
