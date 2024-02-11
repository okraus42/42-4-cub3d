/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:17:37 by okraus            #+#    #+#             */
/*   Updated: 2024/02/11 09:54:35 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	ft_test(t_ray *ray, t_max *max)
{

	ray->hl = (ray->hx - ray->xs) * (ray->hx - ray->xs) + (ray->hy - ray->ys) * (ray->hy - ray->ys);
	ray->vl = (ray->vx - ray->xs) * (ray->vx - ray->xs) + (ray->vy - ray->ys) * (ray->vy - ray->ys);	
	if (ray->hl > ray->vl)
	{
		ray->hv = 1;
		if (ABS(max->math->sin[ray->ra]) > 1024)
		{
			ray->length = ABS((ray->vx - ray->xs) * 65536 / max->math->sin[ray->ra]);
		}
		else
		{
			ray->length =  ABS((ray->vy - ray->ys) * 65536 / max->math->cos[ray->ra]);
		}
		return (1);
	}
	else
	{
		ray->hv = 0;
		if (ABS(max->math->cos[ray->ra]) > 1024)
		{
			ray->length  = ABS((ray->hy - ray->ys) * 65536 / max->math->cos[ray->ra]);
		}
		else
		{
			ray->length  = ABS((ray->hx - ray->xs) * 65536 / max->math->sin[ray->ra]);
		}
		return (0);
	}
}

int	ft_otest(t_oray *oray, t_max *max)
{
	oray->hl = (oray->hx - oray->xs) * (oray->hx - oray->xs) + (oray->hy - oray->ys) * (oray->hy - oray->ys);
	oray->vl = (oray->vx - oray->xs) * (oray->vx - oray->xs) + (oray->vy - oray->ys) * (oray->vy - oray->ys);
	if (oray->hl > oray->vl)
	{
		oray->hv = 1;
		if (ABS(max->math->sin[oray->ra]) > 1024)
		{
			oray->length = ABS((oray->vx - oray->xs) * 65536 / max->math->sin[oray->ra]);
		}
		else
		{
			oray->length =  ABS((oray->vy - oray->ys) * 65536 / max->math->cos[oray->ra]);
		}
		return (1);
	}
	else
	{
		oray->hv = 0;
		if (ABS(max->math->cos[oray->ra]) > 1024)
		{
			oray->length  = ABS((oray->hy - oray->ys) * 65536 / max->math->cos[oray->ra]);
		}
		else
		{
			oray->length  = ABS((oray->hx - oray->xs) * 65536 / max->math->sin[oray->ra]);
		}
		return (0);
	}
}

void	ft_init_rays(t_max *max)
{
	int	mx;
	int	my;
	int	mp;
	int	r;
	long long	pd;
	long long	pl;
	long long	maxdist;
	t_ray	*ray;

	pl = 65536 * WIDTH;
	pd = (pl / 2) / tan((FOV / 2 * 0.01745329));
	maxdist = MAXDIST;
	r = 0;
	while (r < RAYS)
	{	
		ray = &max->map->p.ray[r];
		ray->xs = ((int)max->map->p.x);// * 256;
		ray->ys = ((int)max->map->p.y);// * 256;
		ray->hxo = 65536;
		ray->hyo = 65536;
		ray->vxo = 65536;
		ray->vyo = 65536;
		ray->wall = 0;
		if (NOFISHEYE)
			ray->ra = max->map->p.orientation + atan((double)(pl / RAYS * (RAYS / 2 - r)) / (double)pd) * 65536LL / 6.28318530718;
		else
			ray->ra = max->map->p.orientation + max->map->p.fov2 - r * max->map->p.fov * 65536LL / (RAYS - 1) / 360;
		ray->hdof = 0;
		if (ray->ra > WEST + 4 || ray->ra < EAST - 4)
		{
			ray->hy = ((ray->ys >> 16) << 16) - 1;
			ray->hx = (((ray->ys - ray->hy) * max->math->ntan[ray->ra]) >> 16) + ray->xs;

			ray->hxo = ((65536 * max->math->ntan[ray->ra]) >> 16);
			ray->hyo = -65536;
			ray->wall |= NWALL;
		}
		else if (ray->ra < WEST -4 && ray->ra > EAST + 4)
		{
			ray->hy = ((ray->ys >> 16) << 16) + 65536;
			ray->hx = (((ray->ys - ray->hy) * max->math->ntan[ray->ra]) >> 16) + ray->xs;
			ray->hxo = -((65536 * max->math->ntan[ray->ra]) >> 16); //check where to put minus and bitshifting
			ray->hyo = 65536;
			ray->wall |= SWALL;
		}
		else
		{
			ray->hy = INT_MAX;
			ray->hx = INT_MAX;
			ray->hdof = DOF;
		}
		while (ray->hdof < DOF)
		{
			mx = ray->hx >> 16;
			my = ray->hy >> 16;
			// ft_printf("%x %x\n", mx, my);
			mp = (my << 8) + mx;
			if (mp > 0 && mp < 65536)
			{
				//max->map->m[mp] |= VISITED;
				if ((max->map->m[mp]) & WALL)
				{
					ray->hm = max->map->m[mp];
					break ;
				}
			}
			else
			{
				ray->hdof = DOF;
				break ;
			}
			ray->hx += ray->hxo;
			ray->hy += ray->hyo;
			++ray->hdof;
		}

		ray->vdof = 0;
		if (ray->ra < SOUTH - 4 && ray->ra > NORTH + 4)
		{
			ray->vx = ((ray->xs >> 16) << 16) - 1;
			ray->vy = (((ray->xs - ray->vx) * max->math->atan[ray->ra]) >> 16) + ray->ys;
			ray->vxo = -65536;
			ray->vyo = (65536 * max->math->atan[ray->ra]) >> 16;
			ray->wall |= WWALL;
		}
		else if (ray->ra > SOUTH + 4 && ray->ra < (unsigned short)(NORTH - 4))
		{
			ray->vx = ((ray->xs >> 16) << 16) + 65536;
			ray->vy = (((ray->xs - ray->vx) * max->math->atan[ray->ra]) >> 16) + ray->ys;
			ray->vxo = 65536;//check where to put minus and bitshifting
			ray->vyo = -((65536 * max->math->atan[ray->ra]) >> 16);
			ray->wall |= EWALL;
		}
		//looking up or down
		else
		{
			ray->vy = INT_MAX;
			ray->vx = INT_MAX;
			ray->vdof = DOF;
		}
		while (ray->vdof < DOF)
		{
			mx = ray->vx >> 16;
			my = ray->vy >> 16;
			mp = (my << 8) + mx;
			mp = (my << 8) + mx;
			if (mp > 0 && mp < 65536)
			{
				if ((max->map->m[mp]) & WALL)
				{
					ray->vm = max->map->m[mp];
					break ;
				}
			}
			else
			{
				ray->vdof = DOF;
				break ;
			}
			ray->vx += ray->vxo;
			ray->vy += ray->vyo;
			++ray->vdof;
		}

		if (ft_test(ray, max))
		{
			ray->rx = ray->vx;
			ray->ry = ray->vy;
			ray->m = ray->vm;
		}
		else
		{
			ray->rx = ray->hx;
			ray->ry = ray->hy;
			ray->m = ray->hm;
		}

		if (!ray->hv)
		{
			ray->dof = ray->hdof;
			ray->wall &= NSWALL;
		}
		else
		{
			ray->dof = ray->vdof;
			ray->wall &= EWWALL;
		}
		if (ray->dof >= DOF)
			ray->wall = NOWALL;
		if (!(r % 32) || r == RAYS - 1)
		{
			if (!ray->hv)
			{
				while (ray->hdof >= 0)
				{
					mp = ((max->map->p.ray[r].hy >> 16) << 8) | (max->map->p.ray[r].hx >> 16);
					max->map->m[mp] |= VISITED;
					ray->hx -= ray->hxo;
					ray->hy -= ray->hyo;
					--ray->hdof;
				}
			}
			else
			{
				while (ray->vdof >= 0)
				{
					mp = ((max->map->p.ray[r].vy >> 16) << 8) | (max->map->p.ray[r].vx >> 16);
					max->map->m[mp] |= VISITED;
					ray->vx -= ray->vxo;
					ray->vy -= ray->vyo;
					--ray->vdof;
				}
			}
		}
		if (ray->wall == NOWALL)
			ray->c[0] = NOWALLCOLOUR;
		else if (ray->wall == WWALL)
			ray->c[0] = WWALLCOLOUR;
		else if (ray->wall == EWALL)
			ray->c[0] = EWALLCOLOUR;
		else if (ray->wall == NWALL)
			ray->c[0] = NWALLCOLOUR;
		else if (ray->wall == SWALL)
			ray->c[0] = SWALLCOLOUR;
		else
			ray->c[0] = 0xFFFF00FF;
		if (ray->length > maxdist)
			ray->c[1] = 0x000000ff;
		else
		{
			ray->c1a = 0xff;
			ray->c1b = ray->c0b * (255 - (255 * ray->length / maxdist)) / 256;
			ray->c1g = ray->c0g * (255 - (255 * ray->length / maxdist)) / 256;
			ray->c1r = ray->c0r * (255 - (255 * ray->length / maxdist)) / 256;
		}
		++r;
	}
}

// max->map->p.oray[r].xs
// max->map->p.oray[r].ys
// max->map->p.oray[r].rx
// max->map->p.oray[r].ry
// max->map->p.oray[r].c[0]
// max->map->p.oray[r].c[1]

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
		if (NOFISHEYE)
			oray->ra = max->map->p.orientation - atan((double)(pl / RAYS * (RAYS / 2 - r)) / (double)pd) * 65536LL / 6.28318530718;
		else //need check
			oray->ra = max->map->p.orientation - max->map->p.fov2 + r * max->map->p.fov * 65536LL / (RAYS - 1) / 360;
		//ft_printf("r = %i, ra = %i\n", r, oray->ra);
		oray->hdof = 0;
		if (oray->ra > WEST + 4 || oray->ra < EAST - 4)
		{
			oray->hy = ((oray->ys >> 16) << 16) - 1;
			oray->hx = (((oray->ys - oray->hy) * max->math->tan[oray->ra]) >> 16) + oray->xs;

			oray->hxo = ((65536 * max->math->tan[oray->ra]) >> 16);
			oray->hyo = -65536;
			oray->wall |= NWALL;
		}
		else if (oray->ra < WEST -4 && oray->ra > EAST + 4)
		{
			oray->hy = ((oray->ys >> 16) << 16) + 65536;
			oray->hx = (((oray->ys - oray->hy) * max->math->tan[oray->ra]) >> 16) + oray->xs;
			oray->hxo = ((65536 * max->math->ntan[oray->ra]) >> 16); //check where to put minus and bitshifting
			oray->hyo = 65536;
			oray->wall |= SWALL;
		}
		else
		{
			oray->hy = INT_MAX;
			oray->hx = INT_MAX;
			oray->hdof = DOF;
		}
		while (oray->hdof < DOF)
		{
			mx = oray->hx >> 16;
			my = oray->hy >> 16;
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
				oray->hdof = DOF;
				break ;
			}
			oray->hx += oray->hxo;
			oray->hy += oray->hyo;
			++oray->hdof;
		}
		// oray->rx = oray->hx;
		// oray->ry = oray->hy;
		oray->vdof = 0;
		if (oray->ra < SOUTH - 4 && oray->ra > NORTH + 4)
		{
			oray->vx = ((oray->xs >> 16) << 16) + 65536;
			oray->vy = (((oray->xs - oray->vx) * max->math->atan[oray->ra]) >> 16) + oray->ys;
			oray->vxo = 65536;//check where to put minus and bitshifting
			oray->vyo = ((65536 * max->math->natan[oray->ra]) >> 16);
			oray->wall |= EWALL;
		}
		else if (oray->ra > SOUTH + 4 && oray->ra < (unsigned short)(NORTH - 4))
		{
			oray->vx = ((oray->xs >> 16) << 16) - 1;
			oray->vy = (((oray->xs - oray->vx) * max->math->atan[oray->ra]) >> 16) + oray->ys;

			oray->vxo = -65536;
			oray->vyo = (65536 * max->math->atan[oray->ra]) >> 16;
			oray->wall |= WWALL;
		}
		//looking up or down
		else
		{
			oray->vy = INT_MAX;
			oray->vx = INT_MAX;
			oray->vdof = DOF;
		}
	
		
		while (oray->vdof < DOF)
		{
			mx = oray->vx >> 16;
			my = oray->vy >> 16;
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
				oray->vdof = DOF;
				break ;
			}
			oray->vx += oray->vxo;
			oray->vy += oray->vyo;
			++oray->vdof;
		}
		if (ft_otest(oray, max))
		{
			oray->rx = oray->vx;
			oray->ry = oray->vy;
			oray->m = oray->vm;
		}
		else
		{
			oray->rx = oray->hx;
			oray->ry = oray->hy;
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
		if (1)
		{
			if (!oray->hv)
			{
				while (oray->hdof >= 0)
				{
					mp = ((max->map->p.oray[r].hy >> 16) << 8) | (max->map->p.oray[r].hx >> 16);
					max->map->m[mp] |= VISITED;
					oray->hx -= oray->hxo;
					oray->hy -= oray->hyo;
					--oray->hdof;
				}
			}
			else
			{
				while (oray->vdof >= 0)
				{
					mp = ((max->map->p.oray[r].vy >> 16) << 8) | (max->map->p.oray[r].vx >> 16);
					max->map->m[mp] |= VISITED;
					oray->vx -= oray->vxo;
					oray->vy -= oray->vyo;
					--oray->vdof;
				}
			}
		}
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