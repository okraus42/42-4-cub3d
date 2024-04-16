/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:20:50 by okraus            #+#    #+#             */
/*   Updated: 2024/04/16 15:28:56 by okraus           ###   ########.fr       */
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
	
	u = ((x - startx) * (w / max->map.exit.maxframe)) / (size);
	u += max->map.exit.frame * (w / max->map.exit.maxframe);
	v = ((y - starty) * h) / (size);
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

void	ft_draw_sprites(t_max *max)
{
	int	spx; //sprite relative position
	int	spy;
	int	spz;
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
	if (distance > max->settings.maxdist)
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
