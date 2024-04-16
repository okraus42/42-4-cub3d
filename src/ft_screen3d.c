/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:38:24 by okraus            #+#    #+#             */
/*   Updated: 2024/04/16 13:26:09 by okraus           ###   ########.fr       */
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

int	ft_capangle(int angle)
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

int	ft_exit_visible(t_max *max, int r, int direction, int radius, long long distance)
{
	int	minangle;
	int	maxangle;

	minangle = direction - radius;
	maxangle = direction + radius;
	if (minangle < 0)
		minangle += MAXDEGREE;
	if (maxangle >= MAXDEGREE)
		maxangle -= MAXDEGREE;
	// 180 +/- 20
	// 160 - 200
	// 10
	// 350 - 30
	// 350
	// 330 - 10
	if (max->map.p.oray[r].wall && distance > max->map.p.oray[r].length)
		return (0);
	// if (minangle < maxangle)
	// {
	// 	if (max->map.p.oray[r].ra < minangle || max->map.p.oray[r].ra > maxangle)
	// 		return (0);
	// }
	// else
	// {
	// 	if (max->map.p.oray[r].ra < minangle && max->map.p.oray[r].ra > maxangle)
	// 		return (0);
	// }
	return (1);
}

void	ft_clean_spritescreen(t_max *max)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREENWIDTH)
	{
		y = 0;
		while (y < SCREENHEIGHT)
		{
			mlx_put_pixel(max->i.spritescreen, x, y, 0);
			++y;
		}
		++x;
	}
}

unsigned int	ft_get_sprite_colour(t_max *max, int startx, int x, int y, int size) //add sprite
{
	unsigned int	c;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
	int				u;
	int				v;
	int				w;
	int				p;
	int				h;
	int				starty;

	starty = (SCREENHEIGHT - size) / 2;

	w = max->t.sprites[SPRITE_EXIT]->width;
	h = max->t.sprites[SPRITE_EXIT]->height;
	
	// startx -40 size 50 x 10 w 256
	// u?
	
	u = ((x - startx) * (w / max->map.exit.maxframe)) / (size);
	u += max->map.exit.frame * (w / max->map.exit.maxframe);
	v = ((y - starty) * h) / (size);
	// printf("%i %i %i %i\n", x, startx, w, size);
	// printf("%i %i\n", u, v);
	p = w * 4 * (v) + (4 * (u));

// 	w = img->width;
// 	h = img->height;
// 	p = w * 4 * (h * y / wh) + (4 * (w * x / xw));
// 	//ft_printf("%i %i\n",(h * y / wh), (w * x / xw));
// 	r.rgba = (img->pixels[p] << 24) | (img->pixels[p + 1] << 16) | (img->pixels[p + 2] << 8) | 0x0000FF;
	r = max->t.sprites[SPRITE_EXIT]->pixels[p];
	g = max->t.sprites[SPRITE_EXIT]->pixels[p + 1];
	b = max->t.sprites[SPRITE_EXIT]->pixels[p + 2];
	a = max->t.sprites[SPRITE_EXIT]->pixels[p + 3];
	c = r << 24 | g << 16 | b << 8 | a;
	return (c);
}

void	ft_draw_exit(t_max *max)
{
	int	spx; //sprite relative position
	int	spy;
	int	spz;
	// long long	cs;	//cos
	// long long	sn;	//sin
	// long long	scx;	//sprite screen posiiton
	// long long	scy;
	int			direction;
	double		distance;
	int			radius; //angle
	long long	length;
	int			sprite_height;
	int	y;
	int	x;
	int	r;

	//move elsewhere later?
	ft_clean_spritescreen(max);
	spx = max->map.exit.x - max->map.p.x;
	spy = max->map.exit.y - max->map.p.y;
	spz = max->map.exit.z;
	(void)spz;
	// printf("exit x %i exit y %i\n", max->map.exit.x, max->map.exit.y);
	// printf("player x %i player y %i\n", max->map.p.x, max->map.p.y);
	// printf("spx %i spy %i\n", spx, spy);
	// // ft_printf("\nspx %i, spy %i\n", spx, spy);
	// direction = max->map.p.orientation;
	// direction -= MAXDEGREE / 4;
	// if (direction > MAXDEGREE)
	// 	direction -= MAXDEGREE;
	// cs = max->math->cos[direction];
	// sn = max->math->sin[direction];
	// scx = spy * cs + spx * sn;
	// scy = spx * cs - spy * sn;
	// ft_printf("scx %i, scy %i\n", scx, scy);
	// scx = (scx * 256 / scy) + (SCREENWIDTH / 2);
	// scy = (spz * 256 / scy) + (SCREENHEIGHT / 2);
	// ft_printf("scx %i, scy %i\n", scx, scy);
	direction = atan2(spx, -spy) * (MAXDEGREE / 2 / M_PI);
	//printf("%f\n", atan2(-spx, spy));
	if (direction > MAXDEGREE)
		direction -= MAXDEGREE;
	else if (direction < 0)
		direction += MAXDEGREE;
	distance = sqrt((double)spx * (double)spx + (double)spy * (double)spy);
	radius = atan(32768 / distance) * (MAXDEGREE / 2 / M_PI); //32768 = 65536/2
	// ft_printf("direction = %i\n", direction);
	// ft_printf("radius = %i\n", radius);
	x = 0;
	r = x * RAYS / SCREENWIDTH;
	length = distance;
	if (max->settings.fisheyecorrection)
	{
		length *= max->math->cos[ft_capangle((max->map.p.orientation - max->map.p.oray[r].ra))];
		length /= 65536;
	}
	sprite_height = 65536 * SCREENHEIGHT / length;
	// if (sprite_height > SCREENHEIGHT) //needs offset later
	// 	sprite_height = SCREENHEIGHT;
	if (distance > max->settings.maxdist * 2)
		return ;
	if (!(max->frame % 4))
		if (++max->map.exit.frame == max->map.exit.maxframe)
			max->map.exit.frame = 0;
	//player angle
	//pa - fov/2 is left edge
	//pa + fov/2 is right edge
	//screenwidth = fov
	//sprite direction
	// x ~ pa - sprite direction + screenwidth/2
	int	xpa = SCREENWIDTH / 2;
	int	fullangle = 360 * SCREENWIDTH / max->settings.fov;
	int	relativedirection = max->map.p.orientation - direction;
	if (relativedirection < 0 - MAXDEGREE / 2)
		relativedirection += MAXDEGREE;
	if (relativedirection > MAXDEGREE / 2)
		relativedirection -= MAXDEGREE;
	//relativedirection is -180 - 180
	int sda = fullangle * relativedirection / MAXDEGREE;
	x = xpa - sda - sprite_height / 2;
	int	xend = x + sprite_height;
	
	while (x < xend)
	{
		if (x < 0)
		{
			++x;
			continue ;
		}
		if (x >= SCREENWIDTH)
			break ;
		r = x * RAYS / SCREENWIDTH;
		y = (SCREENHEIGHT - sprite_height) / 2;
		if (y < 0)
			y = 0;
		if (ft_exit_visible(max, r, direction, radius, distance))
		{
			
			while (y < SCREENHEIGHT / 2 + sprite_height / 2)
			{
				if (y >= SCREENHEIGHT)
					break ;
				mlx_put_pixel(max->i.spritescreen, x, y, ft_get_sprite_colour(max, xpa - sda - sprite_height / 2, x, y, sprite_height));
				//mlx_put_pixel(max->i.screen, x, y, ((unsigned int)(rand() % 0xFFFFFF) << 8) | 0xFF);
				++y;
			}
		}
		++x;
	}
}

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
		if (length > max->settings.maxdist || !max->map.p.oray[r].wall)
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
	ft_draw_exit(max);
}