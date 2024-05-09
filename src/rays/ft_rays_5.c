/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:41:33 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 19:42:06 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	ft_init_orays_while_h_breaker_dn(t_max *max, t_oray *oray)
{
	oray->mp2 = oray->mp;
	oray->vx[oray->vdof] = oray->vx[oray->vdof - 1] + oray->vxo / 2;
	oray->vy[oray->vdof] = oray->vy[oray->vdof - 1] + oray->vyo / 2;
	++oray->vdof;
	oray->mx = oray->vx[oray->vdof - 1] >> 16;
	oray->my = oray->vy[oray->vdof - 1] >> 16;
	oray->mp = (oray->my << 8) + oray->mx;
	if (oray->mp == oray->mp2
		&& (oray->vx[oray->vdof - 1] & 0xFFFF) <= 0x8000)
	{
		if (max->map.doors[oray->mp] & 0x7F
			&& (int)(((max->map.doors[oray->mp] & 0x7F) << 9)
			| 0x1FF) >= (oray->vy[oray->vdof - 1] & 0xFFFF))
		{
			if (oray->ra < SOUTH && oray->ra > NORTH)
				oray->wall |= DOOREAST;
			else if (oray->ra > SOUTH && oray->ra < MAXDEGREE)
				oray->wall |= DOORWEST;
			oray->vm = max->map.m[oray->mp];
			return (1);
		}
	}
	return (0);
}

int	ft_init_orays_while_h_breaker_ds(t_max *max, t_oray *oray)
{
	oray->mp2 = oray->mp;
	oray->vx[oray->vdof] = oray->vx[oray->vdof - 1] + oray->vxo / 2;
	oray->vy[oray->vdof] = oray->vy[oray->vdof - 1] + oray->vyo / 2;
	++oray->vdof;
	oray->mx = oray->vx[oray->vdof - 1] >> 16;
	oray->my = oray->vy[oray->vdof - 1] >> 16;
	oray->mp = (oray->my << 8) + oray->mx;
	if (oray->mp == oray->mp2
		&& (oray->vx[oray->vdof - 1] & 0xFFFF) <= 0x8000)
	{
		if (max->map.doors[oray->mp] & 0x7F
			&& (int)(((max->map.doors[oray->mp] & 0x7F) << 9)
			| 0x1FF) >= 0xFFFF - (oray->vy[oray->vdof - 1] & 0xFFFF))
		{
			if (oray->ra < SOUTH && oray->ra > NORTH)
				oray->wall |= DOOREAST;
			else if (oray->ra > SOUTH && oray->ra < MAXDEGREE)
				oray->wall |= DOORWEST;
			oray->vm = max->map.m[oray->mp];
			return (1);
		}
	}
	return (0);
}

int	ft_init_orays_while_v_breaker(t_max *max, t_oray *oray)
{
	if ((max->map.m[oray->mp]) & WALL)
	{
		if (oray->ra < SOUTH && oray->ra > NORTH)
			oray->wall |= EWALL;
		else if (oray->ra > SOUTH && oray->ra < MAXDEGREE)
			oray->wall |= WWALL;
		oray->vm = max->map.m[oray->mp];
		return (1);
	}
	if ((max->map.m[oray->mp]) & DOORNORTH)
	{
		if (ft_init_orays_while_h_breaker_dn(max, oray))
			return (1);
		--oray->vdof;
	}
	if ((max->map.m[oray->mp]) & DOORSOUTH)
	{
		if (ft_init_orays_while_h_breaker_ds(max, oray))
			return (1);
		--oray->vdof;
	}
	return (0);
}
