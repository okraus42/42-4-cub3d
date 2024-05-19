/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen3d_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:10:17 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 19:11:21 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

static void	ft_put_wall(t_max *max, t_walltexture *wt, mlx_texture_t *t)
{
	t_clr			r;
	int				p;

	wt->v = (t->height * (wt->y - wt->offset) / wt->wall_height);
	p = (wt->v * t->width * 4) + (4 * wt->u);
	r.r = t->pixels[p];
	r.g = t->pixels[p + 1];
	r.b = t->pixels[p + 2];
	r.a = 0x0000FF;
	mlx_put_pixel(max->i.screen, wt->x, wt->y, r.rgba);
}

void	ft_draw_screen3d_nw(t_max *max, t_walltexture *wt, int stop)
{
	int	x;

	x = max->map.p.oray[wt->r].rx % 65536;
	wt->u = ((max->t.nwall->width * x) >> 16);
	while (wt->y < stop)
	{
		ft_put_wall(max, wt, max->t.nwall);
		mlx_put_pixel(max->i.fogscreen, wt->x, wt->y,
			wt->wallfog | wt->wallfogalpha);
		++wt->y;
	}
}

void	ft_draw_screen3d_sw(t_max *max, t_walltexture *wt, int stop)
{
	int	x;

	x = 65535 - max->map.p.oray[wt->r].rx % 65536;
	wt->u = ((max->t.swall->width * x) >> 16);
	while (wt->y < stop)
	{
		ft_put_wall(max, wt, max->t.swall);
		mlx_put_pixel(max->i.fogscreen, wt->x, wt->y,
			wt->wallfog | wt->wallfogalpha);
		++wt->y;
	}
}

void	ft_draw_screen3d_ew(t_max *max, t_walltexture *wt, int stop)
{
	int	x;

	x = max->map.p.oray[wt->r].ry % 65536;
	wt->u = ((max->t.ewall->width * x) >> 16);
	while (wt->y < stop)
	{
		ft_put_wall(max, wt, max->t.ewall);
		mlx_put_pixel(max->i.fogscreen, wt->x, wt->y,
			wt->wallfog | wt->wallfogalpha);
		++wt->y;
	}
}

void	ft_draw_screen3d_ww(t_max *max, t_walltexture *wt, int stop)
{
	int	x;

	x = 65535 - max->map.p.oray[wt->r].ry % 65536;
	wt->u = ((max->t.wwall->width * x) >> 16);
	while (wt->y < stop)
	{
		ft_put_wall(max, wt, max->t.wwall);
		mlx_put_pixel(max->i.fogscreen, wt->x, wt->y,
			wt->wallfog | wt->wallfogalpha);
		++wt->y;
	}
}
