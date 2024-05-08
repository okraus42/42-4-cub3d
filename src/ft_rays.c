/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:17:37 by okraus            #+#    #+#             */
/*   Updated: 2024/05/08 14:24:08 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	ft_otest(t_oray *oray, t_max *max, int r, int debug)
{
	int	h;
	int	v;

	(void)r;
	h = oray->hdof;
	v = oray->vdof;
	if (oray->vdof < 0)
	{
		oray->hv = 0;
		if (ABS(max->math->cos[oray->ra]) > 1024)
		{
			oray->length  = ABS((oray->hy[h] - oray->ys) * 65536 / max->math->cos[oray->ra]);
		}
		else
		{
			oray->length  = ABS((oray->hx[h] - oray->xs) * 65536 / max->math->sin[oray->ra]);
		}
		if (debug)
		{
			ft_printf("A otest return 0\n");
		}
		return (0);
	}
	if (oray->hdof < 0)
	{
		oray->hv = 1;
		if (ABS(max->math->sin[oray->ra]) > 1024)
		{
			oray->length = ABS((oray->vx[v] - oray->xs) * 65536 / max->math->sin[oray->ra]);
		}
		else
		{
			oray->length =  ABS((oray->vy[v] - oray->ys) * 65536 / max->math->cos[oray->ra]);
		}
		if (debug)
		{
			ft_printf("B otest return 1\n");
		}
		return (1);
	}
	oray->hl = (oray->hx[h] - oray->xs) * (oray->hx[h] - oray->xs) + (oray->hy[h] - oray->ys) * (oray->hy[h] - oray->ys);
	oray->vl = (oray->vx[v] - oray->xs) * (oray->vx[v] - oray->xs) + (oray->vy[v] - oray->ys) * (oray->vy[v] - oray->ys);
	if (debug)
	{
		ft_printf("U hl %llx, vl %llx\n", oray->hl, oray->vl);
		ft_printf("S hl %lli, vl %lli\n", oray->hl, oray->vl);
		ft_printf("U hlx %llx, vlx %llx\n", (oray->hx[h] - oray->xs) * (oray->hx[h] - oray->xs), (oray->vx[v] - oray->xs) * (oray->vx[v] - oray->xs));
		ft_printf("U hly %llx, vly %llx\n", (oray->hy[h] - oray->ys) * (oray->hy[h] - oray->ys), (oray->vy[v] - oray->ys) * (oray->vy[v] - oray->ys));
		ft_printf("S hlx %lli, vlx %lli\n", (oray->hx[h] - oray->xs) * (oray->hx[h] - oray->xs), (oray->vx[v] - oray->xs) * (oray->vx[v] - oray->xs));
		ft_printf("S hly %lli, vly %lli\n", (oray->hy[h] - oray->ys) * (oray->hy[h] - oray->ys), (oray->vy[v] - oray->ys) * (oray->vy[v] - oray->ys));
	}
	if (oray->hl > oray->vl)
	{
		oray->hv = 1;
		if (ABS(max->math->sin[oray->ra]) > 1024)
		{
			oray->length = ABS((oray->vx[v] - oray->xs) * 65536 / max->math->sin[oray->ra]);
		}
		else
		{
			oray->length =  ABS((oray->vy[v] - oray->ys) * 65536 / max->math->cos[oray->ra]);
		}
		if (debug)
		{
			ft_printf("C otest return 1\n");
		}
		return (1);
	}
	else
	{
		oray->hv = 0;
		if (ABS(max->math->cos[oray->ra]) > 1024)
		{
			oray->length  = ABS((oray->hy[h] - oray->ys) * 65536 / max->math->cos[oray->ra]);
		}
		else
		{
			oray->length  = ABS((oray->hx[h] - oray->xs) * 65536 / max->math->sin[oray->ra]);
		}
		if (debug)
		{
			ft_printf("D otest return 0\n");
		}
		return (0);
	}
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
			max->math->rafc[r] = 0 - atan((double)(pl / RAYS * (RAYS / 2 - r)) / (double)pd) * 16384LL / 6.28318530718;
		else
			max->math->ra[r] = 2 * max->map.p.fov2 + r * max->map.p.fov * 16384LL / (RAYS - 1) / 360;
		++r;
	}
}

void	ft_init_orays(t_max *max)
{
	int			mx;
	int			my;
	int			mp;
	int			mp2;
	int			r;
	int			debug;
	t_oray		*oray;

	r = 0;
	while (r < RAYS)
	{
		debug = r == max->ray && max->keys[MLX_KEY_4];
		if (debug)
			max->keys[MLX_KEY_4] = 0;
		oray = &max->map.p.oray[r];
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
		if (debug)
			ft_printf("\nra: %i\n", oray->ra);
		if (oray->ra > WEST || oray->ra < EAST)
		{
			oray->hy[0] = ((oray->ys >> 16) << 16) - 1;
			oray->hx[0] = (((oray->ys - oray->hy[0]) * max->math->tan[oray->ra]) >> 16) + oray->xs;
			oray->hxo = ((65536 * max->math->tan[oray->ra]) >> 16);
			oray->hyo = -65536;
			if (debug)
			{
				ft_printf("I hx %Lx, hy %Lx, hxo %Lx, hyo %Lx\n", oray->hx[0], oray->hy[0], oray->hxo, oray->hyo);
			}
		}
		else if (oray->ra < WEST && oray->ra > EAST)
		{
			oray->hy[0] = ((oray->ys >> 16) << 16) + 65536;
			oray->hx[0] = (((oray->ys - oray->hy[0]) * max->math->tan[oray->ra]) >> 16) + oray->xs;
			oray->hxo = ((65536 * max->math->ntan[oray->ra]) >> 16); //check where to put minus and bitshifting
			oray->hyo = 65536;
			if (debug)
			{
				ft_printf("EI hx %Lx, hy %Lx, hxo %Lx, hyo %Lx\n", oray->hx[0], oray->hy[0], oray->hxo, oray->hyo);
			}
		}
		else
		{
			oray->hy[0] = INT_MAX;
			oray->hx[0] = INT_MAX;
			oray->hdof = -1;
		}
		while (oray->hdof > 0 && oray->hdof <= max->settings.dof)
		{
			mx = oray->hx[oray->hdof - 1] >> 16;
			my = oray->hy[oray->hdof - 1] >> 16;
			if (debug)
				ft_printf("HW %x %x\n", mx, my);
			mp = (my << 8) + mx;
			if (mp > 0 && mp < 65536)
			{
				if ((max->map.m[mp]) & WALL)
				{
					if (oray->ra > WEST || oray->ra < EAST)
						oray->wall |= NWALL;
					else if (oray->ra < WEST && oray->ra > EAST)
						oray->wall |= SWALL;
					oray->hm = max->map.m[mp];
					break ;
				}
				if ((max->map.m[mp]) & DOORWEST)
				{
					mp2 = mp;
					oray->hx[oray->hdof] = oray->hx[oray->hdof - 1] + oray->hxo / 2;
					oray->hy[oray->hdof] = oray->hy[oray->hdof - 1] + oray->hyo / 2;
					++oray->hdof;
					mx = oray->hx[oray->hdof - 1] >> 16;
					my = oray->hy[oray->hdof - 1] >> 16;
					mp = (my << 8) + mx;
					if (mp == mp2 && (oray->hy[oray->hdof - 1] & 0xFFFF) <= 0x8000)
					{
						if (max->map.doors[mp] & 0x7F
							&& (int)(((max->map.doors[mp] & 0x7F) << 9) | 0x1FF) >= (oray->hx[oray->hdof - 1] & 0xFFFF))
						{
							if (oray->ra > WEST || oray->ra < EAST)
								oray->wall |= DOORNORTH;
							else if (oray->ra < WEST && oray->ra > EAST)
								oray->wall |= DOORSOUTH;
							oray->hm = max->map.m[mp];
							break ;
						}
						
					}
					--oray->hdof;
				}
				if ((max->map.m[mp]) & DOOREAST)
				{
					mp2 = mp;
					oray->hx[oray->hdof] = oray->hx[oray->hdof - 1] + oray->hxo / 2;
					oray->hy[oray->hdof] = oray->hy[oray->hdof - 1] + oray->hyo / 2;
					++oray->hdof;
					mx = oray->hx[oray->hdof - 1] >> 16;
					my = oray->hy[oray->hdof - 1] >> 16;
					mp = (my << 8) + mx;
					if (mp == mp2 && (oray->hy[oray->hdof - 1] & 0xFFFF) <= 0x8000)
					{
						if (max->map.doors[mp] & 0x7F
							&& (int)(((max->map.doors[mp] & 0x7F) << 9) | 0x1FF) >= 0xFFFF - (oray->hx[oray->hdof - 1] & 0xFFFF))
						{
							if (oray->ra > WEST || oray->ra < EAST)
								oray->wall |= DOORNORTH;
							else if (oray->ra < WEST && oray->ra > EAST)
								oray->wall |= DOORSOUTH;
							oray->hm = max->map.m[mp];
							break ;
						}
						
					}
					--oray->hdof;
				}
			}
			else
			{
				break ;
			}
			oray->hx[oray->hdof] = oray->hx[oray->hdof - 1] + oray->hxo;
			oray->hy[oray->hdof] = oray->hy[oray->hdof - 1] + oray->hyo;
			if (debug)
				ft_printf("HW %i %x %x\n", oray->hdof, oray->hx[oray->hdof], oray->hy[oray->hdof]);
			++oray->hdof;
		}
		oray->vdof = 1;
		if (oray->ra < SOUTH && oray->ra > NORTH)
		{
			oray->vx[0] = ((oray->xs >> 16) << 16) + 65536;
			oray->vy[0] = (((oray->xs - oray->vx[0]) * max->math->atan[oray->ra]) >> 16) + oray->ys;
			
			oray->vxo = 65536;
			oray->vyo = ((65536 * max->math->natan[oray->ra]) >> 16);
			if (debug)
			{
				ft_printf("I vx %Lx, vy %Lx, vxo %Lx, vyo %Lx\n", oray->vx[0], oray->vy[0], oray->vxo, oray->vyo);
			}
		}
		else if (oray->ra > SOUTH && oray->ra < MAXDEGREE)
		{
			oray->vx[0] = ((oray->xs >> 16) << 16) - 1;
			oray->vy[0] = (((oray->xs - oray->vx[0]) * max->math->atan[oray->ra]) / 65536) + oray->ys;
			oray->vxo = -65536;
			oray->vyo = (65536 * max->math->atan[oray->ra]) >> 16;
			if (debug)
			{
				ft_printf("EI vx %Lx, vy %Lx, vxo %Lx, vyo %Lx\n", oray->vx[0], oray->vy[0], oray->vxo, oray->vyo);
			}
		}
		else
		{
			oray->vy[0] = INT_MAX;
			oray->vx[0] = INT_MAX;
			oray->vdof = -1;
		}
		while (oray->vdof > 0 && oray->vdof <= max->settings.dof)
		{
			mx = oray->vx[oray->vdof - 1] >> 16;
			my = oray->vy[oray->vdof - 1] >> 16;
			mp = (my << 8) + mx;
			if (debug)
				ft_printf("VW %x %x\n", mx, my);
			if (mp > 0 && mp < 65536)
			{
				if ((max->map.m[mp]) & WALL)
				{
					if (oray->ra < SOUTH && oray->ra > NORTH)
						oray->wall |= EWALL;
					else if (oray->ra > SOUTH && oray->ra < MAXDEGREE)
						oray->wall |= WWALL;
					oray->vm = max->map.m[mp];
					break ;
				}
				if ((max->map.m[mp]) & DOORNORTH)
				{
					mp2 = mp;
					oray->vx[oray->vdof] = oray->vx[oray->vdof - 1] + oray->vxo / 2;
					oray->vy[oray->vdof] = oray->vy[oray->vdof - 1] + oray->vyo / 2;
	
					++oray->vdof;
					mx = oray->vx[oray->vdof - 1] >> 16;
					my = oray->vy[oray->vdof - 1] >> 16;
					mp = (my << 8) + mx;
					if (mp == mp2 && (oray->vx[oray->vdof - 1] & 0xFFFF) <= 0x8000)
					{
						if (max->map.doors[mp] & 0x7F
							&& (int)(((max->map.doors[mp] & 0x7F) << 9) | 0x1FF) >= (oray->vy[oray->vdof - 1] & 0xFFFF))
						{
							if (oray->ra < SOUTH && oray->ra > NORTH)
								oray->wall |= DOOREAST;
							else if (oray->ra > SOUTH && oray->ra < MAXDEGREE)
								oray->wall |= DOORWEST;
							oray->vm = max->map.m[mp];
							break ;
						}
						
					}
					--oray->vdof;
				}
				if ((max->map.m[mp]) & DOORSOUTH)
				{
					mp2 = mp;
					oray->vx[oray->vdof] = oray->vx[oray->vdof - 1] + oray->vxo / 2;
					oray->vy[oray->vdof] = oray->vy[oray->vdof - 1] + oray->vyo / 2;
					++oray->vdof;
					mx = oray->vx[oray->vdof - 1] >> 16;
					my = oray->vy[oray->vdof - 1] >> 16;
					mp = (my << 8) + mx;
					if (mp == mp2 && (oray->vx[oray->vdof - 1] & 0xFFFF) <= 0x8000)
					{
						if (max->map.doors[mp] & 0x7F
							&& (int)(((max->map.doors[mp] & 0x7F) << 9) | 0x1FF) >= 0xFFFF - (oray->vy[oray->vdof - 1] & 0xFFFF))
						{
							if (oray->ra < SOUTH && oray->ra > NORTH)
								oray->wall |= DOOREAST;
							else if (oray->ra > SOUTH && oray->ra < MAXDEGREE)
								oray->wall |= DOORWEST;
							oray->vm = max->map.m[mp];
							break ;
						}
					}
					--oray->vdof;
				}
			}
			else
			{
				break ;
			}
			oray->vx[oray->vdof] = oray->vx[oray->vdof - 1] + oray->vxo;
			oray->vy[oray->vdof] = oray->vy[oray->vdof - 1] + oray->vyo;
			if (debug)
				ft_printf("VW %i %x %x\n", oray->vdof, oray->vx[oray->vdof], oray->vy[oray->vdof]);
			++oray->vdof;
		}
		--oray->vdof;
		--oray->hdof;
		if (ft_otest(oray, max, r, debug))
		{
			oray->rx = oray->vx[oray->vdof];
			oray->ry = oray->vy[oray->vdof];
			oray->m = oray->vm;
		}
		else
		{
			oray->rx = oray->hx[oray->hdof];
			oray->ry = oray->hy[oray->hdof];
			oray->m = oray->hm;
		}
		if (debug)
		{
			ft_printf("hx = %Li hy = %Li | ", oray->hx[oray->hdof], oray->hy[oray->hdof]);
			ft_printf("vx = %Li vy = %Li\n", oray->vx[oray->vdof], oray->vy[oray->vdof]);
			ft_printf("rx = %Li ry = %Li", oray->rx, oray->ry);
			ft_printf("hdof = %i vdof = %Li\n", oray->hdof, oray->vdof);
			ft_printf("hxo = %Li hyo = %Li | ", oray->hxo, oray->hyo);
			ft_printf("vxo = %Li vyo = %Li\n", oray->vxo, oray->vyo);
			ft_printf("oray hv = %i", oray->hv);
		}
		if (!oray->hv)
		{
			oray->dof = oray->hdof;
			oray->wall &= (NSWALL | DOORNS);
		}
		else
		{
			oray->dof = oray->vdof;
			oray->wall &= (EWWALL | DOOREW);
		}
		oray->length2 = oray->length;
		if (!oray->hv)
		{
			if (oray->hdof)
				oray->ldof = oray->length / oray->hdof;
			else
				oray->ldof = 1;
			oray->tx = oray->hx[oray->hdof];
			oray->ty = oray->hy[oray->hdof];
			oray->txo = oray->hxo;
			oray->tyo = oray->hyo;
			oray->tdof = oray->hdof;
		}
		else
		{
			if (oray->vdof)
				oray->ldof = oray->length / oray->vdof;
			else
				oray->ldof = 1;
			oray->tx = oray->vx[oray->vdof];
			oray->ty = oray->vy[oray->vdof];
			oray->txo = oray->vxo;
			oray->tyo = oray->vyo;
			oray->tdof = oray->vdof;
		}
		while (oray->tdof >= 0)
		{
			mp = ((max->map.p.oray[r].ty >> 16) << 8) | (max->map.p.oray[r].tx >> 16);
			if (oray->tdof)
			{
				ft_visit_map(&max->map, oray->length2, max->settings.lightdist, mp);
			}
			oray->length2 -= oray->ldof;
			oray->tx -= oray->txo;
			oray->ty -= oray->tyo;
			--oray->tdof;
		}
		if (r == 0)
			oray->c[0] = 0x00FF00FF;
		else if (r == RAYS - 1)
			oray->c[0] = 0xFF0000FF;
		else
			oray->c[0] = 0xFFFF00FF;
		if (oray->length > max->settings.maxdist)
		{
			oray->wall = NOWALL;
			oray->length = max->settings.maxdist;
		}
		
		if (oray->wall == NOWALL || oray->length > max->settings.lightdist)
		{
			oray->rx = oray->xs + ((max->settings.lightdist) * (long long)(max->math->sin[oray->ra])) / 65536;
			oray->ry = oray->ys - ((max->settings.lightdist) * (long long)(max->math->cos[oray->ra])) / 65536;
		}
		oray->c[0] = NOWALLCOLOUR;
		if (oray->length > max->settings.lightdist)
			oray->c[1] = max->map.f.rgba;
		else
		{
			oray->c1a = 0xff;
			int	r = max->map.f.r;
			int	g = max->map.f.g;
			int	b = max->map.f.b;

			oray->c1r = oray->c0r * (255 - (255 * oray->length / max->settings.lightdist)) / 256
				+ r * ((255 * oray->length / max->settings.lightdist)) / 256;
			oray->c1g = oray->c0g * (255 - (255 * oray->length / max->settings.lightdist)) / 256
				+ g * ((255 * oray->length / max->settings.lightdist)) / 256;
			oray->c1b = oray->c0b * (255 - (255 * oray->length / max->settings.lightdist)) / 256
				+ b * ((255 * oray->length / max->settings.lightdist)) / 256;
		}
		mx = oray->rx >> 16;
		my = oray->ry >> 16;
		mp = (my << 8) + mx;
		oray->mpos = mp;
		++r;
	}
}