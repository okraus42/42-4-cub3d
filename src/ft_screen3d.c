/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:38:24 by okraus            #+#    #+#             */
/*   Updated: 2024/05/10 20:39:48 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static int	ft_capangle(int angle)
{
	while (angle < 0)
		angle += MAXDEGREE;
	while (angle >= MAXDEGREE)
		angle -= MAXDEGREE;
	return (angle);
}

// h.x = sprite.x - player.x
// h.y = sprite.y - player.y

// p = atan2(-h.y / h.x) * (180 / PI)

// if p > 360:
// 	p -= 360
// if p < 0:
// 	p += 360

// q = player_rot + (fov / 2) - p

// if player_rot in quadrant 1 and p in quadrant 4:
// 	q += 360
// if player_rot in quadrant 4 and p in quadrant 1:
// 	q -= 360

// sprite_screen.x = q * (projection_plane_width / fov)
// sprite_screen.y = 100 (projection_plane_height / 2 = 200 / 2 = 100)

void	ft_init_fogscreen(t_max *max)
{
	int				y;
	int				x;
	int				r;
	unsigned int	fogc;
	unsigned int	foga;
	long long		length;

	fogc = max->map.b.rgba & 0xFFFFFF00;
	x = 0;
	while (x < SCREENWIDTH / 2)
	{
		r = x * RAYS / SCREENWIDTH;
		y = 0;
		while (y < SCREENHEIGHT / 2)
		{
			length = 65536 * SCREENHEIGHT / (SCREENHEIGHT - (y * 2));
			if (max->settings.fisheyecorrection)
			{
				length *= 65536;
				if (max->math->cos[ft_capangle((max->map.p.orientation
								- max->map.p.oray[r].ra))] == 0)
					length /= 1;
				else
					length /= max->math->cos[ft_capangle((max->map.p.orientation
								- max->map.p.oray[r].ra))];
			}
			foga = ((length * 255 / (max->settings.lightdist - 65536)));
			if (foga > 0xFF)
				foga = 0xFF;
			max->fog[y][x] = fogc | foga;
			max->fog[y][SCREENWIDTH - x - 1] = fogc | foga;
			max->fog[SCREENHEIGHT - y - 1][x] = fogc | foga;
			max->fog[SCREENHEIGHT - y - 1][SCREENWIDTH - x - 1] = fogc | foga;
			++y;
		}
		++x;
	}
}

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

void	ft_draw_screen3d(t_max *max)
{
	t_walltexture	wt;
	int				stop;
	int				x;

	wt.x = 0;
	while (wt.x < SCREENWIDTH)
	{
		wt.y = 0;
		wt.r = wt.x * RAYS / SCREENWIDTH;
		wt.length = max->map.p.oray[wt.r].length;
		if (max->settings.fisheyecorrection)
		{
			wt.length *= max->math->cos[ft_capangle((max->map.p.orientation
						- max->map.p.oray[wt.r].ra))];
			wt.length /= 65536;
		}
		wt.wall_height = 65536 * SCREENHEIGHT / wt.length;
		if (wt.length > (max->settings.lightdist - 65536)
			|| !max->map.p.oray[wt.r].wall)
			wt.wall_height = 0;
		wt.offset = SCREENHEIGHT / 2 - wt.wall_height / 2;
		wt.wallfog = max->map.b.rgba & 0xFFFFFF00;
		wt.wallfogalpha = ((wt.length * 255 / (max->settings.lightdist - 65536))
				& 0xFF);
		while (wt.y < wt.offset)
		{
			mlx_put_pixel(max->i.screen, wt.x, wt.y, max->map.c.rgba);
			mlx_put_pixel(max->i.fogscreen, wt.x, wt.y, max->fog[wt.y][wt.x]);
			++wt.y;
		}
		stop = wt.wall_height + wt.offset;
		if (stop > SCREENHEIGHT)
			stop = SCREENHEIGHT;
		if (max->map.p.oray[wt.r].wall & NWALL)
		{
			x = max->map.p.oray[wt.r].rx % 65536;
			wt.u = ((max->t.nwall->width * x) >> 16);
			while (wt.y < stop)
			{
				ft_put_wall(max, &wt, max->t.nwall);
				mlx_put_pixel(max->i.fogscreen, wt.x, wt.y,
					wt.wallfog | wt.wallfogalpha);
				++wt.y;
			}
		}
		else if (max->map.p.oray[wt.r].wall & EWALL)
		{
			x = max->map.p.oray[wt.r].ry % 65536;
			wt.u = ((max->t.ewall->width * x) >> 16);
			while (wt.y < stop)
			{
				ft_put_wall(max, &wt, max->t.ewall);
				mlx_put_pixel(max->i.fogscreen, wt.x, wt.y,
					wt.wallfog | wt.wallfogalpha);
				++wt.y;
			}
		}
		else if (max->map.p.oray[wt.r].wall & SWALL)
		{
			x = 65535 - max->map.p.oray[wt.r].rx % 65536;
			wt.u = ((max->t.swall->width * x) >> 16);
			while (wt.y < stop)
			{
				ft_put_wall(max, &wt, max->t.swall);
				mlx_put_pixel(max->i.fogscreen, wt.x, wt.y,
					wt.wallfog | wt.wallfogalpha);
				++wt.y;
			}
		}
		else if (max->map.p.oray[wt.r].wall & WWALL)
		{
			x = 65535 - max->map.p.oray[wt.r].ry % 65536;
			wt.u = ((max->t.wwall->width * x) >> 16);
			while (wt.y < stop)
			{
				ft_put_wall(max, &wt, max->t.wwall);
				mlx_put_pixel(max->i.fogscreen, wt.x, wt.y,
					wt.wallfog | wt.wallfogalpha);
				++wt.y;
			}
		}
		else if (max->map.p.oray[wt.r].wall & DOORNORTH)
		{
			x = max->map.p.oray[wt.r].rx % 65536;
			if (max->map.m[max->map.p.oray[wt.r].mpos] & (DOOREAST | DOORSOUTH))
				x = 65535 - x;
			x += 65535 - ((max->map.doors[max->map.p.oray[wt.r].mpos]
						& 0x7F) << 9) | 0x1FF;
			wt.u = ((max->t.door->width * x) >> 16);
			while (wt.y < stop)
			{
				ft_put_door(max, &wt, max->t.door);
				mlx_put_pixel(max->i.fogscreen, wt.x, wt.y,
					wt.wallfog | wt.wallfogalpha);
				++wt.y;
			}
		}
		else if (max->map.p.oray[wt.r].wall & DOORSOUTH)
		{
			x = max->map.p.oray[wt.r].rx % 65536;
			if (max->map.m[max->map.p.oray[wt.r].mpos] & (DOOREAST | DOORSOUTH))
				x = 65535 - x;
			x += 65535 - ((max->map.doors[max->map.p.oray[wt.r].mpos]
						& 0x7F) << 9) | 0x1FF;
			wt.u = ((max->t.door->width * x) >> 16);
			while (wt.y < stop)
			{
				ft_put_door(max, &wt, max->t.door);
				mlx_put_pixel(max->i.fogscreen, wt.x, wt.y,
					wt.wallfog | wt.wallfogalpha);
				++wt.y;
			}
		}
		else if (max->map.p.oray[wt.r].wall & DOORWEST)
		{
			x = max->map.p.oray[wt.r].ry % 65536;
			if (max->map.m[max->map.p.oray[wt.r].mpos] & (DOOREAST | DOORSOUTH))
				x = 65535 - x;
			x += 65535 - ((max->map.doors[max->map.p.oray[wt.r].mpos]
						& 0x7F) << 9) | 0x1FF;
			wt.u = ((max->t.door->width * x) >> 16);
			while (wt.y < stop)
			{
				ft_put_door(max, &wt, max->t.door);
				mlx_put_pixel(max->i.fogscreen, wt.x, wt.y,
					wt.wallfog | wt.wallfogalpha);
				++wt.y;
			}
		}
		else if (max->map.p.oray[wt.r].wall & DOOREAST)
		{
			x = max->map.p.oray[wt.r].ry % 65536;
			if (max->map.m[max->map.p.oray[wt.r].mpos] & (DOOREAST | DOORSOUTH))
				x = 65535 - x;
			x += 65535 - ((max->map.doors[max->map.p.oray[wt.r].mpos]
						& 0x7F) << 9) | 0x1FF;
			wt.u = ((max->t.door->width * x) >> 16);
			while (wt.y < stop)
			{
				ft_put_door(max, &wt, max->t.door);
				mlx_put_pixel(max->i.fogscreen, wt.x, wt.y, wt.wallfog
					| wt.wallfogalpha);
				++wt.y;
			}
		}
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
