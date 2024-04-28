/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:38:24 by okraus            #+#    #+#             */
/*   Updated: 2024/04/28 15:00:58 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

// Weird psychadelich stuff
// unsigned int	ft_get_colour(int x, int xw, int y, int wh, mlx_texture_t *img)
// {
// 	unsigned int	r;
// 	int				h;
// 	int				w;
// 	int				p;

// 	w = img->width;
// 	h = img->height;
// 	p = w * y / wh + 0 * h;
// 	r = (img->pixels[p] << 24) | (img->pixels[p + 1] << 16) | (img->pixels[p + 2] << 8) | 0x0000FF;
// 	(void)x;
// 	(void)xw;
// 	return (r);
// }

// unsigned int	ft_get_colour(t_max *max, int x, long long length, int y, int wh, mlx_texture_t *img)
// {
// 	t_clr			r;
// 	int				h;
// 	int				w;
// 	int				p;
// 	int				xw;

// 	xw = 65536;
// 	w = img->width;
// 	h = img->height;
// 	p = w * 4 * (h * y / wh) + (4 * (w * x / xw));
// 	//ft_printf("%i %i\n",(h * y / wh), (w * x / xw));
// 	r.rgba = (img->pixels[p] << 24) | (img->pixels[p + 1] << 16) | (img->pixels[p + 2] << 8) | 0x0000FF;
// 	if (length > max->settings.maxdist)
// 		length = max->settings.maxdist;
// 	r.r = max->math->brumered[r.r][length * 255LL / max->settings.maxdist];
// 	r.g = max->math->brumegreen[r.g][length * 255LL / max->settings.maxdist];
// 	r.b = max->math->brumeblue[r.b][length * 255LL / max->settings.maxdist];
// 	return (r.rgba);
// }

// unsigned int	ft_get_colour2(t_max *max, unsigned int c, int y, int fake_offset)
// {
// 	t_clr			r;
// 	int				length;
// 	int				start;
// 	int				offset;

// 	r.rgba = c;
// 	offset = HEIGHT / 2 - fake_offset;
// 	start = 2 * offset;
// 	if (y < HEIGHT / 2)
// 		length = PERCENTIL(0, 255, start + y, HEIGHT / 2 + offset);
// 	else
// 		length = PERCENTIL(0, 255, start + (HEIGHT - y), HEIGHT / 2 + offset);
// 	// if (y < HEIGHT / 2)
// 	//  	ft_printf("%i %i %i %i || %i %i\n", start, length, y, offset, start + y, HEIGHT / 2 + offset);
// 	//ft_printf("1 %3i %3i %3i %3i || ", r.r, r.g, r.b, length); 
// 	r.r = max->math->brumered[r.r][length];
// 	r.g = max->math->brumegreen[r.g][length];
// 	r.b = max->math->brumeblue[r.b][length];
// 	//ft_printf("2 %3i %3i %3i %3i\n", r.r, r.g, r.b, length); 
// 	return (r.rgba);
// }

// void	ft_get_colour3(t_max *max, unsigned int c, int y, int fake_offset)
// {
// 	t_clr			r;
// 	int				length;
// 	int				start;
// 	int				offset;

// 	r.rgba = c;
// 	offset = HEIGHT / 2 - fake_offset;
// 	start = 2 * offset;
// 	if (y < HEIGHT / 2)
// 		length = PERCENTIL(0, 255, start + y, HEIGHT / 2 + offset);
// 	else
// 		length = PERCENTIL(0, 255, start + (HEIGHT - y), HEIGHT / 2 + offset);
// 	// if (y < HEIGHT / 2)
// 	//  	ft_printf("%i %i %i %i || %i %i\n", start, length, y, offset, start + y, HEIGHT / 2 + offset);
// 	ft_printf("1 %3i %3i %3i %3i || ", r.r, r.g, r.b, length); 
// 	r.r = max->math->brumered[r.r][length];
// 	r.g = max->math->brumegreen[r.g][length];
// 	r.b = max->math->brumeblue[r.b][length];
// 	ft_printf("2 %3i %3i %3i %3i\n", r.r, r.g, r.b, length); 
// }

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
	int	y;
	int	x;
	int	r;
	unsigned int	fogc;
	unsigned int	foga;
	long long		length;

		// fake_wall_height = 65536 * SCREENHEIGHT / fake_length;
	
	fogc = max->map.b.rgba & 0xFFFFFF00;
	x = 0;
	while (x < SCREENWIDTH / 2)
	{
		r = x * RAYS / SCREENWIDTH;
		(void)r;
		y = 0;
		while (y < SCREENHEIGHT / 2)
		{
			length = 65536 * SCREENHEIGHT / (SCREENHEIGHT - (y * 2));
			if (max->settings.fisheyecorrection)
			{
				length *= 65536;
				length /= max->math->cos[ft_capangle((max->map.p.orientation - max->map.p.oray[r].ra))];
			}
			foga = ((length * 255 / max->settings.lightdist));
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
// fake_length *= max->math->cos[ft_capangle((max->map.p.orientation - max->map.p.oray[r].ra))];

static void	ft_put_wall(t_max *max, t_walltexture *wt, mlx_texture_t *t, int x)
{
	t_clr			r;
	int				h;
	int				w;
	int				p;
	int				xw;

	xw = 65536;
	w = t->width;
	h = t->height;
	wt->u = (w * x / xw);
	wt->v = (h * (wt->y - wt->offset) / wt->wall_height);
	p = (wt->v * w * 4) + (4 * wt->u);
	//ft_printf("%i %i\n",(h * y / wh), (w * x / xw));
	r.r = t->pixels[p];
	r.g = t->pixels[p + 1];
	r.b = t->pixels[p + 2];
	r.a = 0x0000FF;
	//r.rgba = () | () | () | ;
	mlx_put_pixel(max->i.screen, wt->x, wt->y, r.rgba);
}


static void	ft_put_door(t_max *max, t_walltexture *wt, mlx_texture_t *t, int x)
{
	t_clr			r;
	int				p;
	int				xw;
	int				offset;

	if (max->map.m[max->map.p.oray[wt->r].mpos] & (DOOREAST | DOORSOUTH))
		x = 65535 - x;
	offset = 65535 - ((max->map.doors[max->map.p.oray[wt->r].mpos] & 0x7F) << 9) | 0x1FF;
	//printf("%i %u \n", offset, max->map.doors[max->map.p.oray[wt->r].mpos]);
	//offset = 0;
	x += offset;
	xw = 65536;
	wt->u = (t->width * x / xw);
	wt->v = (t->height * (wt->y - wt->offset) / wt->wall_height);
	p = (wt->v * t->width * 4) + (4 * wt->u);
	//ft_printf("%i %i\n",(h * y / wh), (w * x / xw));
	r.r = t->pixels[p];
	r.g = t->pixels[p + 1];
	r.b = t->pixels[p + 2];
	r.a = 0x0000FF;
	//r.rgba = () | () | () | ;
	mlx_put_pixel(max->i.screen, wt->x, wt->y, r.rgba);
}

// static void	ft_put_inverse_wall(t_max *max, t_walltexture *wt, mlx_texture_t *t, int x)
// {
// 	t_clr			r;
// 	int				h;
// 	int				w;
// 	int				p;
// 	int				xw;

// 	xw = 65536;
// 	w = t->width;
// 	h = t->height;
// 	wt->u = (w * x / xw);
// 	wt->v = (h * (wt->y - wt->offset) / wt->wall_height);
// 	p = (wt->v * w * 4) + (4 * wt->u);
// 	//ft_printf("%i %i\n",(h * y / wh), (w * x / xw));
// 	r.r = t->pixels[p];
// 	r.g = t->pixels[p + 1];
// 	r.b = t->pixels[p + 2];
// 	r.a = 0x0000FF;
// 	//r.rgba = () | () | () | ;
// 	mlx_put_pixel(max->i.screen, wt->x, wt->y, r.rgba);
// }

// p = w * 4 * (h * y / wh) + (4 * (w * x / xw));


void	ft_draw_screen3d(t_max *max)
{
	t_walltexture	wt;

	ft_init_fogscreen(max);
	wt.x = 0;
	while (wt.x < SCREENWIDTH)
	{
		wt.y = 0;
		wt.r = wt.x * RAYS / SCREENWIDTH;
		//ft_printf("new ray\n");
		//ft_printf("%i %i\n", r, x);
		wt.length = max->map.p.oray[wt.r].length;
		wt.fake_length = max->settings.maxdist;
		if (max->settings.fisheyecorrection)
		{
			//ft_printf("L1 %Lx\n", max->map.p.oray[r].length);
			//ft_printf("ANGLE %i\n", (unsigned short)(max->map.p.orientation - max->map.p.oray[r].ra));
			wt.length *= max->math->cos[ft_capangle((max->map.p.orientation - max->map.p.oray[wt.r].ra))];
			wt.fake_length *= max->math->cos[ft_capangle((max->map.p.orientation - max->map.p.oray[wt.r].ra))];
			//ft_printf("L2 %Lx\n", max->map.p.oray[r].length);
			wt.length /= 65536;
			wt.fake_length /= 65536;
			//ft_printf("L3 %Lx\n", max->map.p.oray[r].length);
		}
		//ft_printf("b\n");
		//ft_printf("%i\n", wall_height);
		wt.fake_wall_height = 65536 * SCREENHEIGHT / wt.fake_length;
		wt.wall_height = 65536 * SCREENHEIGHT / wt.length;
		//ft_printf("wall: %i %i\n", wall_height, fake_wall_height);
		//ft_printf("c\n");
		// if (wall_height > SCREENHEIGHT)
		// 	wall_height = SCREENHEIGHT;
		if (wt.length > max->settings.lightdist || !max->map.p.oray[wt.r].wall)
			wt.wall_height = 0;
		wt.offset = SCREENHEIGHT / 2 - wt.wall_height / 2;
		wt.fake_offset = SCREENHEIGHT / 2 - wt.fake_wall_height / 2;
		// ft_printf("offset: %i %i\n", offset, fake_offset);
		while (wt.y < SCREENHEIGHT)
		{
			if (wt.y < wt.offset && wt.y < wt.fake_offset)
			{
				//mlx_put_pixel(max->screen, x, y, 0x000000FF);
				//mlx_put_pixel(max->screen, x, y, max->map.c.rgba);
				// if (x == 512)
				// 	ft_get_colour3(max, max->map.c.rgba, y, fake_offset);
				//mlx_put_pixel(max->screen, x, y, ft_get_colour2(max, max->map.c.rgba, y, fake_offset));
				mlx_put_pixel(max->i.screen, wt.x, wt.y, max->map.c.rgba);
			}
			else if (wt.y >= wt.offset && wt.y < wt.wall_height + wt.offset)
			{
				//ft_printf("AAAAAA\n");
				//mlx_put_pixel(max->screen, x, y, max->map.p.oray[r].c[1]);
				// if (max->map.p.oray[r].wall & NWALL)
				// {
				// 	//mlx_put_pixel(max->screen, x, y, ft_get_colour(x / 4, 1920 / 4, y - offset, wall_height, max->t->nwall));

				// 	mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map.p.oray[r].rx % 65536, max->map.p.oray[r].length, y - offset, wall_height, max->t->nwall));
				// }
				// else if (max->map.p.oray[r].wall & EWALL)
				// 	mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map.p.oray[r].ry % 65536, max->map.p.oray[r].length, y - offset, wall_height, max->t->ewall));
				// else if (max->map.p.oray[r].wall & SWALL)
				// 	mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map.p.oray[r].rx % 65536, max->map.p.oray[r].length, y - offset, wall_height, max->t->swall));
				// else if (max->map.p.oray[r].wall & WWALL)
				// 	mlx_put_pixel(max->screen, x, y, ft_get_colour(max, max->map.p.oray[r].ry % 65536, max->map.p.oray[r].length, y - offset, wall_height, max->t->wwall));
				// else
				// 	mlx_put_pixel(max->screen, x, y, 0xFF00FFFF);
				if (max->map.p.oray[wt.r].wall & NWALL)
				{
					//mlx_put_pixel(max->screen, x, y, ft_get_colour(x / 4, 1920 / 4, y - offset, wall_height, max->t->nwall));
					ft_put_wall(max, &wt, max->t.nwall, max->map.p.oray[wt.r].rx % 65536);
					//mlx_put_pixel(max->i.screen, wt.x, wt.y, NWALLCOLOUR);
				}
				else if (max->map.p.oray[wt.r].wall & EWALL)
					ft_put_wall(max, &wt, max->t.ewall, max->map.p.oray[wt.r].ry % 65536);
				else if (max->map.p.oray[wt.r].wall & SWALL)
					ft_put_wall(max, &wt, max->t.swall, 65535 - max->map.p.oray[wt.r].rx % 65536);
				else if (max->map.p.oray[wt.r].wall & WWALL)
					ft_put_wall(max, &wt, max->t.wwall, 65535 - max->map.p.oray[wt.r].ry % 65536);
				else if (max->map.p.oray[wt.r].wall & DOORNORTH)
				{
					ft_put_door(max, &wt, max->t.door, max->map.p.oray[wt.r].rx % 65536);
					//mlx_put_pixel(max->i.screen, wt.x, wt.y, DOORCOLOUR);
				}
				else if (max->map.p.oray[wt.r].wall & DOORSOUTH)
					ft_put_door(max, &wt, max->t.door, max->map.p.oray[wt.r].rx % 65536);
				else if (max->map.p.oray[wt.r].wall & DOORWEST)
					ft_put_door(max, &wt, max->t.door, max->map.p.oray[wt.r].ry % 65536);
				else if (max->map.p.oray[wt.r].wall & DOOREAST)
					ft_put_door(max, &wt, max->t.door, max->map.p.oray[wt.r].ry % 65536);
				else
					mlx_put_pixel(max->i.screen, wt.x, wt.y, NOWALLCOLOUR);
			}
			else if (wt.y < wt.fake_wall_height + wt.fake_offset)
			{
				mlx_put_pixel(max->i.screen, wt.x, wt.y, max->map.b.rgba);
			}
			else
			{
				//mlx_put_pixel(max->screen, wt.x, wt.y, 0x000000FF);
				//mlx_put_pixel(max->screen, wt.x, wt.y, max->map.f.rgba);
				mlx_put_pixel(max->i.screen, wt.x, wt.y, max->map.f.rgba);
				// mlx_put_pixel(max->screen, wt.x, wt.y, ft_get_colour2(mawt.x, wt.max->map.f.rgba, y, fake_offset));

			}
			++wt.y;
		}
		++wt.x;
	}
	//draw fog
	wt.x = 0;
	while (wt.x < SCREENWIDTH)
	{
		wt.y = 0;
		wt.r = wt.x * RAYS / SCREENWIDTH;
		wt.length = max->map.p.oray[wt.r].length;
		wt.fake_length = max->settings.maxdist;
		if (max->settings.fisheyecorrection)
		{
			wt.length *= max->math->cos[ft_capangle((max->map.p.orientation - max->map.p.oray[wt.r].ra))];
			wt.fake_length *= max->math->cos[ft_capangle((max->map.p.orientation - max->map.p.oray[wt.r].ra))];
			wt.length /= 65536;
			wt.fake_length /= 65536;
		}
		wt.fake_wall_height = 65536 * SCREENHEIGHT / wt.fake_length;
		wt.wall_height = 65536 * SCREENHEIGHT / wt.length;
		if (wt.length > max->settings.lightdist || !max->map.p.oray[wt.r].wall)
			wt.wall_height = 0;
		wt.offset = SCREENHEIGHT / 2 - wt.wall_height / 2;
		wt.fake_offset = SCREENHEIGHT / 2 - wt.fake_wall_height / 2;
		unsigned int	wallfog;
		unsigned int	wallfogalpha;
		wallfog = max->map.b.rgba & 0xFFFFFF00;
		//BITWISE MAGIC LATER
		// 900 * 10 / 1000 9
		// printf("wallfog %8x\n", wallfog);
		wallfogalpha = ((wt.length * 255 / max->settings.lightdist) & 0xFF);
		//wallfog |= wallfogalpha;
		// printf("wallfog %8x\n", wallfog);
		while (wt.y < SCREENHEIGHT)
		{
			if (wt.y < wt.offset && wt.y < wt.fake_offset)
				mlx_put_pixel(max->i.fogscreen, wt.x, wt.y, max->fog[wt.y][wt.x]);
			else if (wt.y >= wt.offset && wt.y < wt.wall_height + wt.offset)
				mlx_put_pixel(max->i.fogscreen, wt.x, wt.y, wallfog | wallfogalpha);
			else
				mlx_put_pixel(max->i.fogscreen, wt.x, wt.y , max->fog[wt.y][wt.x]);
			// if (y < offset && y < fake_offset)
			// {
			// 	mlx_put_pixel(max->i.screen, wt.x, wt.y, max->map.c.rgba);
			// }
			// else if (y >= offset && y < wall_height + offset)
			// {
			// 	if (max->map.p.oray[wt.r].wall & NWALL)
			// 	{
			// 		mlx_put_pixel(max->i.screen, wt.x, wt.y, NWALLCOLOUR);
			// 	}
			// 	else if (max->map.p.oray[wt.r].wall & EWALL)
			// 		mlx_put_pixel(max->i.screen, wt.x, wt.y, EWALLCOLOUR);
			// 	else if (max->map.p.oray[wt.r].wall & SWALL)
			// 		mlx_put_pixel(max->i.screen, wt.x, wt.y, SWALLCOLOUR);
			// 	else if (max->map.p.oray[wt.r].wall & WWALL)
			// 		mlx_put_pixel(max->i.screen, wt.x, wt.y, WWALLCOLOUR);
			// 	else
			// 		mlx_put_pixel(max->i.screen, wt.x, wt.y, NOWALLCOLOUR);
			// }
			// else if (y < fake_wall_height + fake_offset)
			// {
			// 	mlx_put_pixel(max->i.screen, wt.x, wt.y, max->map.b.rgba);
			// }
			// else
			// {
			// 	mlx_put_pixel(max->i.screen, wt.x, wt.y, max->map.f.rgba);

			// }
			++wt.y;
		}
		++wt.x;
	}
	ft_draw_sprites(max);
}