/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:33:07 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 19:34:00 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	ft_otest_1(t_oray *oray, t_max *max, int h, int v)
{
	if (oray->vdof < 0)
	{
		oray->hv = 0;
		if (ft_abs(max->math->cos[oray->ra]) > 1024)
			oray->length = ft_abs((oray->hy[h] - oray->ys) * 65536
					/ max->math->cos[oray->ra]);
		else
			oray->length = ft_abs((oray->hx[h] - oray->xs) * 65536
					/ max->math->sin[oray->ra]);
		return (0);
	}
	if (oray->hdof < 0)
	{
		oray->hv = 1;
		if (ft_abs(max->math->sin[oray->ra]) > 1024)
			oray->length = ft_abs((oray->vx[v] - oray->xs)
					* 65536 / max->math->sin[oray->ra]);
		else
			oray->length = ft_abs((oray->vy[v] - oray->ys)
					* 65536 / max->math->cos[oray->ra]);
		return (1);
	}
	return (-1);
}

int	ft_otest_2(t_oray *oray, t_max *max, int h, int v)
{
	if (oray->hl > oray->vl)
	{
		oray->hv = 1;
		if (ft_abs(max->math->sin[oray->ra]) > 1024)
			oray->length = ft_abs((oray->vx[v] - oray->xs)
					* 65536 / max->math->sin[oray->ra]);
		else
			oray->length = ft_abs((oray->vy[v] - oray->ys)
					* 65536 / max->math->cos[oray->ra]);
		return (1);
	}
	else
	{
		oray->hv = 0;
		if (ft_abs(max->math->cos[oray->ra]) > 1024)
			oray->length = ft_abs((oray->hy[h] - oray->ys)
					* 65536 / max->math->cos[oray->ra]);
		else
			oray->length = ft_abs((oray->hx[h] - oray->xs)
					* 65536 / max->math->sin[oray->ra]);
		return (0);
	}
}

int	ft_otest(t_oray *oray, t_max *max)
{
	int	h;
	int	v;
	int	r;

	h = oray->hdof;
	v = oray->vdof;
	r = ft_otest_1(oray, max, h, v);
	if (r >= 0)
		return (r);
	oray->hl = (oray->hx[h] - oray->xs) * (oray->hx[h] - oray->xs)
		+ (oray->hy[h] - oray->ys) * (oray->hy[h] - oray->ys);
	oray->vl = (oray->vx[v] - oray->xs) * (oray->vx[v] - oray->xs)
		+ (oray->vy[v] - oray->ys) * (oray->vy[v] - oray->ys);
	return (ft_otest_2(oray, max, h, v));
}

void	ft_visit_neighbours(t_map *map, int mp, unsigned long long visit)
{
	unsigned long long	visit2;

	visit2 = (visit >> 1) & VISITED;
	map->m[mp] |= visit;
	if ((mp % 256))
		map->m[mp - 1] |= visit2;
	if ((mp % 256) < map->hh)
		map->m[mp + 1] |= visit2;
	if ((mp / 256))
		map->m[mp - map->w] |= visit2;
	if ((mp / 256) < map->ww)
		map->m[mp + map->w] |= visit2;
	if ((mp % 256) && (mp / 256))
		map->m[mp - 1 - map->w] |= visit2;
	if ((mp % 256) && (mp / 256) < map->ww)
		map->m[mp -1 + map->w] |= visit2;
	if ((mp % 256) < map->hh && (mp / 256))
		map->m[mp + 1 - map->w] |= visit2;
	if ((mp % 256) < map->hh && (mp / 256) < map->ww)
		map->m[mp + 1 + map->w] |= visit2;
}

void	ft_visit_map(t_map *map, long long length, long long dist, int mp)
{
	if (length < dist)
		ft_visit_neighbours(map, mp, (VISITED >> 2) & VISITED);
	if (length < dist / 2)
		ft_visit_neighbours(map, mp, (VISITED >> 1) & VISITED);
	if (length < dist / 4)
		ft_visit_neighbours(map, mp, VISITED);
}
