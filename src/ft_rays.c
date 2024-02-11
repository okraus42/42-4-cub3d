/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:17:37 by okraus            #+#    #+#             */
/*   Updated: 2024/02/11 16:51:45 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	ft_otest(t_oray *oray, t_max *max)
{
	int	h;
	int	v;

	if (oray->vdof < 0)
		return (0);
	if (oray->hdof < 0)
		return (1);
	h = oray->hdof;
	v = oray->vdof;
	oray->hl = (oray->hx[h] - oray->xs) * (oray->hx[h] - oray->xs) + (oray->hy[h] - oray->ys) * (oray->hy[h] - oray->ys);
	oray->vl = (oray->vx[v] - oray->xs) * (oray->vx[v] - oray->xs) + (oray->vy[v] - oray->ys) * (oray->vy[v] - oray->ys);
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
		return (0);
	}
}

void	ft_init_orays(t_max *max)
{
	int			mx;
	int			my;
	int			mp;
	int			r;
	long long	pd;
	long long	pl;
	long long	maxdist;
	t_oray		*oray;

	pl = 65536 * WIDTH;
	pd = (pl / 2) / tan((FOV / 2 * 0.01745329));
	maxdist = MAXDIST;
	r = 0;
	//ft_printf("\nNEWNEW\n\n\n");
	while (r < RAYS)
	{	
		oray = &max->map->p.oray[r];
		oray->xs = ((int)max->map->p.x);// * 256;
		oray->ys = ((int)max->map->p.y);// * 256;
		oray->hxo = 65536;
		oray->hyo = 65536;
		oray->vxo = 65536;
		oray->vyo = 65536;
		oray->wall = 0;
		//ft_printf("r0 = %i\n", r);
		if (NOFISHEYE)
			oray->ra = max->map->p.orientation - atan((double)(pl / RAYS * (RAYS / 2 - r)) / (double)pd) * 16384LL / 6.28318530718;
		else //need check
			oray->ra = max->map->p.orientation - max->map->p.fov2 + r * max->map->p.fov * 16384LL / (RAYS - 1) / 360;
		if (oray->ra < 0)
			oray->ra += MAXDEGREE; 
		else if (oray->ra >= MAXDEGREE)
			oray->ra -= MAXDEGREE;
		oray->hdof = 1;
		if (oray->ra > WEST || oray->ra < EAST)
		{
			oray->hy[0] = ((oray->ys >> 16) << 16) - 1;
			oray->hx[0] = (((oray->ys - oray->hy[0]) * max->math->tan[oray->ra]) >> 16) + oray->xs;

			oray->hxo = ((65536 * max->math->tan[oray->ra]) >> 16);
			oray->hyo = -65536;
			oray->wall |= NWALL;
		}
		else if (oray->ra < WEST && oray->ra > EAST)
		{
			oray->hy[0] = ((oray->ys >> 16) << 16) + 65536;
			oray->hx[0] = (((oray->ys - oray->hy[0]) * max->math->tan[oray->ra]) >> 16) + oray->xs;
			oray->hxo = ((65536 * max->math->ntan[oray->ra]) >> 16); //check where to put minus and bitshifting
			oray->hyo = 65536;
			oray->wall |= SWALL;
		}
		else
		{
			oray->hy[0] = INT_MAX;
			oray->hx[0] = INT_MAX;
			oray->hdof = -1;
		}
		while (oray->hdof > 0 && oray->hdof < DOF)
		{
			mx = oray->hx[oray->hdof - 1] >> 16;
			my = oray->hy[oray->hdof - 1] >> 16;
			// ft_printf("%x %x\n", mx, my);
			mp = (my << 8) + mx;
			if (mp > 0 && mp < 65536)
			{
				//max->map->m[mp] |= VISITED;
				if ((max->map->m[mp]) & WALL)
				{
					oray->hm = max->map->m[mp];
					break ;
				}
			}
			else
			{
				//oray->hdof = DOF;
				break ;
			}
			oray->hx[oray->hdof] = oray->hx[oray->hdof - 1] + oray->hxo;
			oray->hy[oray->hdof] = oray->hy[oray->hdof - 1] + oray->hyo;
			++oray->hdof;
		}
		// oray->rx = oray->hx;
		// oray->ry = oray->hy;
		oray->vdof = 1;
		if (oray->ra < SOUTH && oray->ra > NORTH)
		{
			oray->vx[0] = ((oray->xs >> 16) << 16) + 65536;
			oray->vy[0] = (((oray->xs - oray->vx[0]) * max->math->atan[oray->ra]) >> 16) + oray->ys;
			oray->vxo = 65536;//check where to put minus and bitshifting
			oray->vyo = ((65536 * max->math->natan[oray->ra]) >> 16);
			oray->wall |= EWALL;
		}
		else if (oray->ra > SOUTH && oray->ra < MAXDEGREE)
		{
			oray->vx[0] = ((oray->xs >> 16) << 16) - 1;
			oray->vy[0] = (((oray->xs - oray->vx[0]) * max->math->atan[oray->ra]) >> 16) + oray->ys;

			oray->vxo = -65536;
			oray->vyo = (65536 * max->math->atan[oray->ra]) >> 16;
			oray->wall |= WWALL;
		}
		//looking up or down
		else
		{
			oray->vy[0] = INT_MAX;
			oray->vx[0] = INT_MAX;
			oray->vdof = -1;
		}
		while (oray->vdof > 0 && oray->vdof < DOF)
		{
			mx = oray->vx[oray->vdof - 1] >> 16;
			my = oray->vy[oray->vdof - 1] >> 16;
			mp = (my << 8) + mx;
			mp = (my << 8) + mx;
			if (mp > 0 && mp < 65536)
			{
				if ((max->map->m[mp]) & WALL)
				{
					oray->vm = max->map->m[mp];
					break ;
				}
			}
			else
			{
				//oray->vdof = DOF;
				break ;
			}
			oray->vx[oray->vdof] = oray->vx[oray->vdof - 1] + oray->vxo;
			oray->vy[oray->vdof] = oray->vy[oray->vdof - 1] + oray->vyo;
			++oray->vdof;
		}
		--oray->vdof;
		--oray->hdof;
		if (ft_otest(oray, max))
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
		// ft_printf("hx = %Li hy = %Li | ", oray->hx, oray->hy);
		// ft_printf("vx = %Li vy = %Li | ", oray->vx, oray->vy);
		// ft_printf("rx = %Li ry = %Li\n", oray->rx, oray->ry);
		// ft_printf("hdof = %i vdof = %Li | ", oray->hdof, oray->vdof);
		// ft_printf("hxo = %Li hyo = %Li | ", oray->hxo, oray->hyo);
		// ft_printf("vxo = %Li vyo = %Li\n", oray->vxo, oray->vyo);
		// oray->rx = oray->vx;
		// oray->ry = oray->vy;
		if (!oray->hv)
		{
			oray->dof = oray->hdof;
			oray->wall &= NSWALL;
		}
		else
		{
			oray->dof = oray->vdof;
			oray->wall &= EWWALL;
		}
		if (oray->dof >= DOF)
			oray->wall = NOWALL;
		oray->length2 = oray->length;
		// ft_printf("r1 = %i\n", r);
		// ft_printf("hdof = %i\n", oray->hdof);
		// ft_printf("vdof = %i\n", oray->vdof);
		if (1)
		{
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
			//ft_printf("startloop\n");
			while (oray->tdof >= 0)
			{
				//ft_printf("hdof1 = %i\n", oray->hdof);
				mp = ((max->map->p.oray[r].ty >> 16) << 8) | (max->map->p.oray[r].tx >> 16);
				//ft_printf("tdof2 = %i, mp = %i\n", oray->tdof, mp);
				// if (mp < 0 || mp > 65536)
				// {
				// 	ft_printf("%i oray->tdof %i | ", oray->hv, oray->tdof);
				// 	ft_printf("oray->tx %Lx oray->ty %Lx | ", oray->tx, oray->ty);
				// 	ft_printf("vx %Lx vy %Lx  hx %Lx  hy %Lx \n", oray->vx[oray->vdof], oray->vy[oray->vdof], oray->hx[oray->hdof], oray->hy[oray->hdof]);
				// 	ft_printf("oray->vdof %i oray->hdof %i\n", oray->vdof, oray->hdof);
				// 	ft_printf("oray->txo %Lx, oray->tyo %Lx, oray->vxo %Lx, oray->vyo %Lx, oray->hxo %Lx, oray->hyo %Lx\n", oray->txo, oray->tyo, oray->vxo, oray->vyo, oray->hxo, oray->hyo);
				// 	break ;
				// }
				if (oray->length2 < MAXDIST)
					max->map->m[mp] |= VISITED;
				//ft_printf("hdof2.5 = %i\n", oray->hdof);
				oray->length2 -= oray->ldof;
				//ft_printf("hdof3 = %i\n", oray->hdof);
				oray->tx -= oray->txo;
				oray->ty -= oray->tyo;
				//ft_printf("hdof4 = %i\n", oray->hdof);
				--oray->tdof;
				//ft_printf("hdof5 = %i\n", oray->hdof);
			}
			//ft_printf("endloop\n");
			// else
			// {
			// 	if (oray->vdof)
			// 		oray->ldof = oray->length / oray->vdof;
			// 	else
			// 		oray->ldof = 1;
			// 	while (oray->vdof > 0)
			// 	{
			// 		mp = ((max->map->p.oray[r].vy[oray->vdof] >> 16) << 8) | (max->map->p.oray[r].vx[oray->vdof] >> 16);
			// 		if (oray->length2 < MAXDIST)
			// 			max->map->m[mp] |= VISITED;
			// 		oray->length2 -= oray->ldof;
			// 		oray->vx[oray->vdof] -= oray->vxo;
			// 		oray->vy[oray->vdof] -= oray->vyo;
			// 		--oray->vdof;
			// 		//ft_printf("vdof = %i\n", oray->vdof);
			// 	}
			// 	//ft_printf("endloop\n");
			// }
		}
		//ft_printf("r2 = %i\n", r);
		
		if (oray->length > MAXDIST)
		{
			oray->wall = NOWALL;
			oray->length = MAXDIST;
		}
		if (oray->wall == NOWALL)
		{
			// x^2 + y^2 = RADIUS^2
			// radius == MAXDIST
			oray->rx = oray->xs + (MAXDIST * (max->math->sin[oray->ra])) / 65536;
			oray->ry = oray->ys - (MAXDIST * (max->math->cos[oray->ra])) / 65536;
		}
		//ft_printf("r3 = %i\n", r);
		// oray->rx = oray->hx;
		// oray->ry = oray->hy;
		// if (oray->wall == NOWALL)
		// 	oray->c[0] = NOWALLCOLOUR;
		// else if (oray->wall == WWALL)
		// 	oray->c[0] = WWALLCOLOUR;
		// else if (oray->wall == EWALL)
		// 	oray->c[0] = EWALLCOLOUR;
		// else if (oray->wall == NWALL)
		// 	oray->c[0] = NWALLCOLOUR;
		// else if (oray->wall == SWALL)
		// 	oray->c[0] = SWALLCOLOUR;
		// else
		// {
		// 	oray->c[0] = 0xFFFF00FF;
		// }
		if (r == 0)
				oray->c[0] = 0x00FF00FF;
			else if (r == RAYS - 1)
				oray->c[0] = 0xFF0000FF;
			else
				oray->c[0] = 0xFFFF00FF;
		if (oray->length > maxdist)
			oray->c[1] = 0x000000ff;
		else
		{
			oray->c1a = 0xff;
			// oray->c1b = oray->c0b * (255 - (255 * oray->length / maxdist)) / 256;
			// oray->c1g = oray->c0g * (255 - (255 * oray->length / maxdist)) / 256;
			// oray->c1r = oray->c0r * (255 - (255 * oray->length / maxdist)) / 256;
			int	r = max->map->f.r;
			int	g = max->map->f.g;
			int	b = max->map->f.b;

			oray->c1r = oray->c0r * (255 - (255 * oray->length / maxdist)) / 256
				+ r * ((255 * oray->length / maxdist)) / 256;
			oray->c1g = oray->c0g * (255 - (255 * oray->length / maxdist)) / 256
				+ g * ((255 * oray->length / maxdist)) / 256;
			oray->c1b = oray->c0b * (255 - (255 * oray->length / maxdist)) / 256
				+ b * ((255 * oray->length / maxdist)) / 256;
		}
		++r;
	}
}