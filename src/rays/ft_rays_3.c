/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:36:03 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 19:36:36 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_init_rayangles(t_max *max)
{
	long long	pd;
	long long	pl;
	int			r;

	pl = 65536 * WIDTH;
	pd = (pl / 2) / tan((max->settings.fov / 2 * 0.01745329));
	r = 0;
	while (r < RAYS)
	{
		if (max->settings.fisheyecorrection)
			max->math->rafc[r] = 0 - atan((double)(pl / RAYS * (RAYS / 2 - r))
					/ (double)pd) * 16384LL / 6.28318530718;
		else
			max->math->ra[r] = 2 * max->map.p.fov2 + r * max->map.p.fov
				* 16384LL / (RAYS - 1) / 360;
		++r;
	}
}

void	ft_init_orays_endcolour(t_max *max, t_oray *oray)
{
	int	r;
	int	g;
	int	b;

	oray->c1a = 0xff;
	r = max->map.f.r;
	g = max->map.f.g;
	b = max->map.f.b;
	oray->c1r = oray->c0r * (255 - (255 * oray->length
				/ max->settings.lightdist)) / 256
		+ r * ((255 * oray->length / max->settings.lightdist)) / 256;
	oray->c1g = oray->c0g * (255 - (255 * oray->length
				/ max->settings.lightdist)) / 256
		+ g * ((255 * oray->length / max->settings.lightdist)) / 256;
	oray->c1b = oray->c0b * (255 - (255 * oray->length
				/ max->settings.lightdist)) / 256
		+ b * ((255 * oray->length / max->settings.lightdist)) / 256;
}

void	ft_init_orays_init_1(t_max *max, t_oray *oray, int r)
{
	oray->xs = ((int)max->map.p.x);
	oray->ys = ((int)max->map.p.y);
	oray->hxo = 65536;
	oray->hyo = 65536;
	oray->vxo = 65536;
	oray->vyo = 65536;
	oray->wall = 0;
	if (max->settings.fisheyecorrection)
		oray->ra = max->map.p.orientation + max->math->rafc[r];
	else
		oray->ra = max->map.p.orientation + max->math->ra[r];
	while (oray->ra < 0)
		oray->ra += MAXDEGREE;
	while (oray->ra >= MAXDEGREE)
		oray->ra -= MAXDEGREE;
	oray->hdof = 1;
}

void	ft_init_orays_init_h(t_max *max, t_oray *oray)
{
	if (oray->ra > WEST || oray->ra < EAST)
	{
		oray->hy[0] = ((oray->ys >> 16) << 16) - 1;
		oray->hx[0] = (((oray->ys - oray->hy[0])
					* max->math->tan[oray->ra]) >> 16) + oray->xs;
		oray->hxo = ((65536 * max->math->tan[oray->ra]) >> 16);
		oray->hyo = -65536;
	}
	else if (oray->ra < WEST && oray->ra > EAST)
	{
		oray->hy[0] = ((oray->ys >> 16) << 16) + 65536;
		oray->hx[0] = (((oray->ys - oray->hy[0])
					* max->math->tan[oray->ra]) >> 16) + oray->xs;
		oray->hxo = ((65536 * max->math->ntan[oray->ra]) >> 16);
		oray->hyo = 65536;
	}
	else
	{
		oray->hy[0] = INT_MAX;
		oray->hx[0] = INT_MAX;
		oray->hdof = -1;
	}
}

void	ft_init_orays_init_v(t_max *max, t_oray *oray)
{
	oray->vdof = 1;
	if (oray->ra < SOUTH && oray->ra > NORTH)
	{
		oray->vx[0] = ((oray->xs >> 16) << 16) + 65536;
		oray->vy[0] = (((oray->xs - oray->vx[0])
					* max->math->atan[oray->ra]) >> 16) + oray->ys;
		oray->vxo = 65536;
		oray->vyo = ((65536 * max->math->natan[oray->ra]) >> 16);
	}
	else if (oray->ra > SOUTH && oray->ra < MAXDEGREE)
	{
		oray->vx[0] = ((oray->xs >> 16) << 16) - 1;
		oray->vy[0] = (((oray->xs - oray->vx[0])
					* max->math->atan[oray->ra]) / 65536) + oray->ys;
		oray->vxo = -65536;
		oray->vyo = (65536 * max->math->atan[oray->ra]) >> 16;
	}
	else
	{
		oray->vy[0] = INT_MAX;
		oray->vx[0] = INT_MAX;
		oray->vdof = -1;
	}
}
