/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:38:24 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 19:15:46 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_draw_screen3d_if(t_max *max, t_walltexture *wt, int stop)
{
	if (max->map.p.oray[wt->r].wall & NWALL)
		ft_draw_screen3d_nw(max, wt, stop);
	else if (max->map.p.oray[wt->r].wall & EWALL)
		ft_draw_screen3d_ew(max, wt, stop);
	else if (max->map.p.oray[wt->r].wall & SWALL)
		ft_draw_screen3d_sw(max, wt, stop);
	else if (max->map.p.oray[wt->r].wall & WWALL)
		ft_draw_screen3d_ww(max, wt, stop);
	else if (max->map.p.oray[wt->r].wall & DOORNORTH)
		ft_draw_screen3d_dn(max, wt, stop);
	else if (max->map.p.oray[wt->r].wall & DOORSOUTH)
		ft_draw_screen3d_ds(max, wt, stop);
	else if (max->map.p.oray[wt->r].wall & DOORWEST)
		ft_draw_screen3d_dw(max, wt, stop);
	else if (max->map.p.oray[wt->r].wall & DOOREAST)
		ft_draw_screen3d_de(max, wt, stop);
}

void	ft_draw_screen3d(t_max *max)
{
	t_walltexture	wt;
	int				stop;

	wt.x = 0;
	while (wt.x < SCREENWIDTH)
	{
		ft_draw_screen3d_init(max, &wt);
		stop = wt.wall_height + wt.offset;
		if (stop > SCREENHEIGHT)
			stop = SCREENHEIGHT;
		ft_draw_screen3d_if(max, &wt, stop);
		while (wt.y < SCREENHEIGHT)
		{
			mlx_put_pixel(max->i.screen, wt.x, wt.y, max->map.f.rgba);
			mlx_put_pixel(max->i.fogscreen, wt.x, wt.y, max->fog[wt.y][wt.x]);
			++wt.y;
		}
		++wt.x;
	}
	ft_draw_sprites(max);
}
