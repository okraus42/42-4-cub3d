/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:38:43 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 19:39:06 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_init_orays_init_c(t_max *max, t_oray *oray)
{
	oray->c[0] = 0x00FF00FF;
	if (oray->length > max->settings.maxdist)
	{
		oray->wall = NOWALL;
		oray->length = max->settings.maxdist;
	}
	if (oray->wall == NOWALL || oray->length > max->settings.lightdist)
	{
		oray->rx = oray->xs + ((max->settings.lightdist)
				* (long long)(max->math->sin[oray->ra])) / 65536;
		oray->ry = oray->ys - ((max->settings.lightdist)
				* (long long)(max->math->cos[oray->ra])) / 65536;
	}
	oray->c[0] = NOWALLCOLOUR;
	if (oray->length > max->settings.lightdist)
		oray->c[1] = max->map.f.rgba;
	else
		ft_init_orays_endcolour(max, oray);
	oray->mx = oray->rx >> 16;
	oray->my = oray->ry >> 16;
	oray->mp = (oray->my << 8) + oray->mx;
	oray->mpos = oray->mp;
}

int	ft_init_orays_while_h_breaker_dw(t_max *max, t_oray *oray)
{
	oray->mp2 = oray->mp;
	oray->hx[oray->hdof] = oray->hx[oray->hdof - 1] + oray->hxo / 2;
	oray->hy[oray->hdof] = oray->hy[oray->hdof - 1] + oray->hyo / 2;
	++oray->hdof;
	oray->mx = oray->hx[oray->hdof - 1] >> 16;
	oray->my = oray->hy[oray->hdof - 1] >> 16;
	oray->mp = (oray->my << 8) + oray->mx;
	if (oray->mp == oray->mp2
		&& (oray->hy[oray->hdof - 1] & 0xFFFF) <= 0x8000)
	{
		if (max->map.doors[oray->mp] & 0x7F
			&& (int)(((max->map.doors[oray->mp] & 0x7F) << 9)
			| 0x1FF) >= (oray->hx[oray->hdof - 1] & 0xFFFF))
		{
			if (oray->ra > WEST || oray->ra < EAST)
				oray->wall |= DOORNORTH;
			else if (oray->ra < WEST && oray->ra > EAST)
				oray->wall |= DOORSOUTH;
			oray->hm = max->map.m[oray->mp];
			return (1);
		}
	}
	return (0);
}

int	ft_init_orays_while_h_breaker_de(t_max *max, t_oray *oray)
{
	oray->mp2 = oray->mp;
	oray->hx[oray->hdof] = oray->hx[oray->hdof - 1] + oray->hxo / 2;
	oray->hy[oray->hdof] = oray->hy[oray->hdof - 1] + oray->hyo / 2;
	++oray->hdof;
	oray->mx = oray->hx[oray->hdof - 1] >> 16;
	oray->my = oray->hy[oray->hdof - 1] >> 16;
	oray->mp = (oray->my << 8) + oray->mx;
	if (oray->mp == oray->mp2
		&& (oray->hy[oray->hdof - 1] & 0xFFFF) <= 0x8000)
	{
		if (max->map.doors[oray->mp] & 0x7F
			&& (int)(((max->map.doors[oray->mp] & 0x7F) << 9)
			| 0x1FF) >= 0xFFFF - (oray->hx[oray->hdof - 1] & 0xFFFF))
		{
			if (oray->ra > WEST || oray->ra < EAST)
				oray->wall |= DOORNORTH;
			else if (oray->ra < WEST && oray->ra > EAST)
				oray->wall |= DOORSOUTH;
			oray->hm = max->map.m[oray->mp];
			return (1);
		}
	}
	return (0);
}

int	ft_init_orays_while_h_breaker(t_max *max, t_oray *oray)
{
	if ((max->map.m[oray->mp]) & WALL)
	{
		if (oray->ra > WEST || oray->ra < EAST)
			oray->wall |= NWALL;
		else if (oray->ra < WEST && oray->ra > EAST)
			oray->wall |= SWALL;
		oray->hm = max->map.m[oray->mp];
		return (1);
	}
	if ((max->map.m[oray->mp]) & DOORWEST)
	{
		if (ft_init_orays_while_h_breaker_dw(max, oray))
			return (1);
		--oray->hdof;
	}
	if ((max->map.m[oray->mp]) & DOOREAST)
	{
		if (ft_init_orays_while_h_breaker_de(max, oray))
			return (1);
		--oray->hdof;
	}
	return (0);
}

void	ft_init_orays_while_h(t_max *max, t_oray *oray)
{
	while (oray->hdof > 0 && oray->hdof <= max->settings.dof)
	{
		oray->mx = oray->hx[oray->hdof - 1] >> 16;
		oray->my = oray->hy[oray->hdof - 1] >> 16;
		oray->mp = (oray->my << 8) + oray->mx;
		if (oray->mp > 0 && oray->mp < 65536)
		{
			if (ft_init_orays_while_h_breaker(max, oray))
				break ;
		}
		else
			break ;
		oray->hx[oray->hdof] = oray->hx[oray->hdof - 1] + oray->hxo;
		oray->hy[oray->hdof] = oray->hy[oray->hdof - 1] + oray->hyo;
		++oray->hdof;
	}
}
