/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:17:37 by okraus            #+#    #+#             */
/*   Updated: 2024/05/09 19:43:41 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_init_orays_while_v(t_max *max, t_oray *oray)
{
	while (oray->vdof > 0 && oray->vdof <= max->settings.dof)
	{
		oray->mx = oray->vx[oray->vdof - 1] >> 16;
		oray->my = oray->vy[oray->vdof - 1] >> 16;
		oray->mp = (oray->my << 8) + oray->mx;
		if (oray->mp > 0 && oray->mp < 65536)
		{
			if (ft_init_orays_while_v_breaker(max, oray))
				break ;
		}
		else
			break ;
		oray->vx[oray->vdof] = oray->vx[oray->vdof - 1] + oray->vxo;
		oray->vy[oray->vdof] = oray->vy[oray->vdof - 1] + oray->vyo;
		++oray->vdof;
	}
}

void	ft_init_orays_test(t_max *max, t_oray *oray)
{
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
}

void	ft_init_orays_init_t(t_oray *oray)
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
}

void	ft_init_orays_while_t(t_max *max, t_oray *oray)
{
	while (oray->tdof >= 0)
	{
		oray->mp = ((oray->ty >> 16) << 8)
			| (oray->tx >> 16);
		if (oray->tdof)
			ft_visit_map(&max->map, oray->length2,
				max->settings.lightdist, oray->mp);
		oray->length2 -= oray->ldof;
		oray->tx -= oray->txo;
		oray->ty -= oray->tyo;
		--oray->tdof;
	}
}

void	ft_init_orays(t_max *max)
{
	int			r;
	t_oray		*oray;

	r = 0;
	while (r < RAYS)
	{
		oray = &max->map.p.oray[r];
		ft_init_orays_init_1(max, oray, r);
		ft_init_orays_init_h(max, oray);
		ft_init_orays_while_h(max, oray);
		ft_init_orays_init_v(max, oray);
		ft_init_orays_while_v(max, oray);
		--oray->vdof;
		--oray->hdof;
		ft_init_orays_test(max, oray);
		oray->length2 = oray->length;
		ft_init_orays_init_t(oray);
		ft_init_orays_while_t(max, oray);
		ft_init_orays_init_c(max, oray);
		++r;
	}
}
