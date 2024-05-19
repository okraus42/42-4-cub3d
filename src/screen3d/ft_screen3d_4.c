/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen3d_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:13:32 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 19:14:13 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

static void	ft_put_door(t_max *max, t_walltexture *wt, mlx_texture_t *t)
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

void	ft_draw_screen3d_ds(t_max *max, t_walltexture *wt, int stop)
{
	int	x;

	x = max->map.p.oray[wt->r].rx % 65536;
	if (max->map.m[max->map.p.oray[wt->r].mpos] & (DOOREAST | DOORSOUTH))
		x = 65535 - x;
	x += 65535 - ((max->map.doors[max->map.p.oray[wt->r].mpos]
				& 0x7F) << 9) | 0x1FF;
	wt->u = ((max->t.door->width * x) >> 16);
	while (wt->y < stop)
	{
		ft_put_door(max, wt, max->t.door);
		mlx_put_pixel(max->i.fogscreen, wt->x, wt->y,
			wt->wallfog | wt->wallfogalpha);
		++wt->y;
	}
}

void	ft_draw_screen3d_dn(t_max *max, t_walltexture *wt, int stop)
{
	int	x;

	x = max->map.p.oray[wt->r].rx % 65536;
	if (max->map.m[max->map.p.oray[wt->r].mpos] & (DOOREAST | DOORSOUTH))
		x = 65535 - x;
	x += 65535 - ((max->map.doors[max->map.p.oray[wt->r].mpos]
				& 0x7F) << 9) | 0x1FF;
	wt->u = ((max->t.door->width * x) >> 16);
	while (wt->y < stop)
	{
		ft_put_door(max, wt, max->t.door);
		mlx_put_pixel(max->i.fogscreen, wt->x, wt->y,
			wt->wallfog | wt->wallfogalpha);
		++wt->y;
	}
}

void	ft_draw_screen3d_dw(t_max *max, t_walltexture *wt, int stop)
{
	int	x;

	x = max->map.p.oray[wt->r].ry % 65536;
	if (max->map.m[max->map.p.oray[wt->r].mpos] & (DOOREAST | DOORSOUTH))
		x = 65535 - x;
	x += 65535 - ((max->map.doors[max->map.p.oray[wt->r].mpos]
				& 0x7F) << 9) | 0x1FF;
	wt->u = ((max->t.door->width * x) >> 16);
	while (wt->y < stop)
	{
		ft_put_door(max, wt, max->t.door);
		mlx_put_pixel(max->i.fogscreen, wt->x, wt->y,
			wt->wallfog | wt->wallfogalpha);
		++wt->y;
	}
}

void	ft_draw_screen3d_de(t_max *max, t_walltexture *wt, int stop)
{
	int	x;

	x = max->map.p.oray[wt->r].ry % 65536;
	if (max->map.m[max->map.p.oray[wt->r].mpos] & (DOOREAST | DOORSOUTH))
		x = 65535 - x;
	x += 65535 - ((max->map.doors[max->map.p.oray[wt->r].mpos]
				& 0x7F) << 9) | 0x1FF;
	wt->u = ((max->t.door->width * x) >> 16);
	while (wt->y < stop)
	{
		ft_put_door(max, wt, max->t.door);
		mlx_put_pixel(max->i.fogscreen, wt->x, wt->y, wt->wallfog
			| wt->wallfogalpha);
		++wt->y;
	}
}
