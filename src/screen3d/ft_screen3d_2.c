/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen3d_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:04:54 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 19:07:13 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

static int	ft_capangle(int angle)
{
	while (angle < 0)
		angle += MAXDEGREE;
	while (angle >= MAXDEGREE)
		angle -= MAXDEGREE;
	return (angle);
}

void	ft_init_fogscreen_inner(t_max *max, t_fs *fs)
{
	fs->length = 65536 * SCREENHEIGHT / (SCREENHEIGHT - (fs->y * 2));
	if (max->settings.fisheyecorrection)
	{
		fs->length *= 65536;
		if (max->math->cos[ft_capangle((max->map.p.orientation
						- max->map.p.oray[fs->r].ra))] == 0)
			fs->length /= 1;
		else
			fs->length /= max->math->cos[ft_capangle((max->map.p.orientation
						- max->map.p.oray[fs->r].ra))];
	}
	fs->foga = ((fs->length * 255 / (max->settings.lightdist - 65536)));
	if (fs->foga > 0xFF)
		fs->foga = 0xFF;
	max->fog[fs->y][fs->x] = fs->fogc | fs->foga;
	max->fog[fs->y][SCREENWIDTH - fs->x - 1] = fs->fogc | fs->foga;
	max->fog[SCREENHEIGHT - fs->y - 1][fs->x] = fs->fogc | fs->foga;
	max->fog[SCREENHEIGHT - fs->y - 1][SCREENWIDTH - fs->x - 1]
		= fs->fogc | fs->foga;
}

void	ft_init_fogscreen(t_max *max)
{
	t_fs	fs;

	fs.fogc = max->map.b.rgba & 0xFFFFFF00;
	fs.x = 0;
	while (fs.x < SCREENWIDTH / 2)
	{
		fs.r = fs.x * RAYS / SCREENWIDTH;
		fs.y = 0;
		while (fs.y < SCREENHEIGHT / 2)
		{
			ft_init_fogscreen_inner(max, &fs);
			++fs.y;
		}
		++fs.x;
	}
}

void	ft_draw_screen3d_init(t_max *max, t_walltexture *wt)
{
	wt->y = 0;
	wt->r = wt->x * RAYS / SCREENWIDTH;
	wt->length = max->map.p.oray[wt->r].length;
	if (max->settings.fisheyecorrection)
	{
		wt->length *= max->math->cos[ft_capangle((max->map.p.orientation
					- max->map.p.oray[wt->r].ra))];
		wt->length /= 65536;
	}
	wt->wall_height = 65536 * SCREENHEIGHT / wt->length;
	if (wt->length > (max->settings.lightdist - 65536)
		|| !max->map.p.oray[wt->r].wall)
		wt->wall_height = 0;
	wt->offset = SCREENHEIGHT / 2 - wt->wall_height / 2;
	wt->wallfog = max->map.b.rgba & 0xFFFFFF00;
	wt->wallfogalpha = ((wt->length * 255 / (max->settings.lightdist - 65536))
			& 0xFF);
	while (wt->y < wt->offset)
	{
		mlx_put_pixel(max->i.screen, wt->x, wt->y, max->map.c.rgba);
		mlx_put_pixel(max->i.fogscreen, wt->x, wt->y, max->fog[wt->y][wt->x]);
		++wt->y;
	}
}
