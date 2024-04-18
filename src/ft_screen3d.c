/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:38:24 by okraus            #+#    #+#             */
/*   Updated: 2024/04/18 13:53:53 by okraus           ###   ########.fr       */
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



void	ft_draw_screen3d(t_max *max)
{
	int	y;
	int	x;
	int	r;
	int	wall_height;
	int	offset;
	int	fake_wall_height;
	int	fake_offset;
	long long	length;
	long long	fake_length;

	x = 0;
	
	while (x < SCREENWIDTH)
	{
		y = 0;
		r = x * RAYS / SCREENWIDTH;
		//ft_printf("new ray\n");
		//ft_printf("%i %i\n", r, x);
		length = max->map.p.oray[r].length;
		fake_length = max->settings.maxdist;
		if (max->settings.fisheyecorrection)
		{
			//ft_printf("L1 %Lx\n", max->map.p.oray[r].length);
			//ft_printf("ANGLE %i\n", (unsigned short)(max->map.p.orientation - max->map.p.oray[r].ra));
			length *= max->math->cos[ft_capangle((max->map.p.orientation - max->map.p.oray[r].ra))];
			fake_length *= max->math->cos[ft_capangle((max->map.p.orientation - max->map.p.oray[r].ra))];
			//ft_printf("L2 %Lx\n", max->map.p.oray[r].length);
			length /= 65536;
			fake_length /= 65536;
			//ft_printf("L3 %Lx\n", max->map.p.oray[r].length);
		}
		//ft_printf("b\n");
		//ft_printf("%i\n", wall_height);
		fake_wall_height = 65536 * SCREENHEIGHT / fake_length;
		wall_height = 65536 * SCREENHEIGHT / length;
		//ft_printf("wall: %i %i\n", wall_height, fake_wall_height);
		//ft_printf("c\n");
		// if (wall_height > SCREENHEIGHT)
		// 	wall_height = SCREENHEIGHT;
		if (length > max->settings.lightdist || !max->map.p.oray[r].wall)
			wall_height = 0;
		offset = SCREENHEIGHT / 2 - wall_height / 2;
		fake_offset = SCREENHEIGHT / 2 - fake_wall_height / 2;
		// ft_printf("offset: %i %i\n", offset, fake_offset);
		while (y < SCREENHEIGHT)
		{
			if (y < offset && y < fake_offset)
			{
				//mlx_put_pixel(max->screen, x, y, 0x000000FF);
				//mlx_put_pixel(max->screen, x, y, max->map.c.rgba);
				// if (x == 512)
				// 	ft_get_colour3(max, max->map.c.rgba, y, fake_offset);
				//mlx_put_pixel(max->screen, x, y, ft_get_colour2(max, max->map.c.rgba, y, fake_offset));
				mlx_put_pixel(max->i.screen, x, y, max->map.c.rgba);
			}
			else if (y >= offset && y < wall_height + offset)
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
				if (max->map.p.oray[r].wall & NWALL)
				{
					//mlx_put_pixel(max->screen, x, y, ft_get_colour(x / 4, 1920 / 4, y - offset, wall_height, max->t->nwall));
					mlx_put_pixel(max->i.screen, x, y, NWALLCOLOUR);
				}
				else if (max->map.p.oray[r].wall & EWALL)
					mlx_put_pixel(max->i.screen, x, y, EWALLCOLOUR);
				else if (max->map.p.oray[r].wall & SWALL)
					mlx_put_pixel(max->i.screen, x, y, SWALLCOLOUR);
				else if (max->map.p.oray[r].wall & WWALL)
					mlx_put_pixel(max->i.screen, x, y, WWALLCOLOUR);
				else
					mlx_put_pixel(max->i.screen, x, y, NOWALLCOLOUR);
			}
			else if (y < fake_wall_height + fake_offset)
			{
				mlx_put_pixel(max->i.screen, x, y, max->map.b.rgba);
			}
			else
			{
				//mlx_put_pixel(max->screen, x, y, 0x000000FF);
				//mlx_put_pixel(max->screen, x, y, max->map.f.rgba);
				mlx_put_pixel(max->i.screen, x, y, max->map.f.rgba);
				// mlx_put_pixel(max->screen, x, y, ft_get_colour2(max, max->map.f.rgba, y, fake_offset));

			}
			++y;
		}
		++x;
	}
	ft_draw_sprites(max);
}