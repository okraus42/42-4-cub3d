/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:20:50 by okraus            #+#    #+#             */
/*   Updated: 2024/04/19 09:32:58 by okraus           ###   ########.fr       */
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

void	ft_init_sprites_flamingo(t_map *map, int i)
{
	printf("sprite %i init\n", i);
	map->sprites[i].state = 1; //ON
	map->sprites[i].texture = FLAMINGO_TEXTURE; //EXITTEXTURE
	map->sprites[i].glowtexture = FLAMINGO_GLOW; //EXITT GLOW EXTURE
	map->sprites[i].type = SPRITE_FLAMINGO; //EXIT
	map->sprites[i].frame = 0;
	map->sprites[i].maxframe = 1;
	map->sprites[i].z = 20;
	++map->spritecount;
}

void	ft_init_sprites(t_max *max)
{
	printf("sprite  exit %i init\n", SPRITE_EXIT);
	max->map.sprites[SPRITE_EXIT].state = 1; //ON
	max->map.sprites[SPRITE_EXIT].texture = EXIT_TEXTURE; //EXITTEXTURE
	max->map.sprites[SPRITE_EXIT].glowtexture = EXIT_GLOW; //EXITT GLOW EXTURE
	max->map.sprites[SPRITE_EXIT].type = SPRITE_EXIT; //EXIT
	max->map.sprites[SPRITE_EXIT].frame = 0;
	max->map.sprites[SPRITE_EXIT].maxframe = 32;
	max->map.sprites[SPRITE_EXIT].z = 20;
	max->map.spritecount = 1;
}

int	ft_sprite_visible(t_max *max, int r, int direction, int radius, long long distance)
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

void	ft_put_sprite_colour(t_max *max, int startx, int x, int y, int size, t_sprite *sprite) //add sprite
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
	w = max->t.sprites[sprite->texture]->width;
	h = max->t.sprites[sprite->texture]->height;
	
	u = ((x - startx) * (w / sprite->maxframe)) / (size);
	u += sprite->frame * (w / sprite->maxframe);
	v = ((y - starty) * h) / (size);
	p = w * 4 * (v) + (4 * (u));

// 	w = img->width;
// 	h = img->height;
// 	p = w * 4 * (h * y / wh) + (4 * (w * x / xw));
// 	//ft_printf("%i %i\n",(h * y / wh), (w * x / xw));
// 	r.rgba = (img->pixels[p] << 24) | (img->pixels[p + 1] << 16) | (img->pixels[p + 2] << 8) | 0x0000FF;
	r = max->t.sprites[sprite->texture]->pixels[p];
	g = max->t.sprites[sprite->texture]->pixels[p + 1];
	b = max->t.sprites[sprite->texture]->pixels[p + 2];
	a = max->t.sprites[sprite->texture]->pixels[p + 3];
	c = r << 24 | g << 16 | b << 8 | a;
	if (a)
		mlx_put_pixel(max->i.spritescreen, x, y, c);
}

void	ft_put_sprite_glowcolour(t_max *max, int startx, int x, int y, int size, t_sprite *sprite) //add sprite
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
	w = max->t.sprites[sprite->glowtexture]->width;
	h = max->t.sprites[sprite->glowtexture]->height;

	u = ((x - startx) * (w / sprite->maxframe)) / (size);
	u += sprite->frame * (w / sprite->maxframe);
	v = ((y - starty) * h) / (size);
	p = w * 4 * (v) + (4 * (u));

// 	w = img->width;
// 	h = img->height;
// 	p = w * 4 * (h * y / wh) + (4 * (w * x / xw));
// 	//ft_printf("%i %i\n",(h * y / wh), (w * x / xw));
// 	r.rgba = (img->pixels[p] << 24) | (img->pixels[p + 1] << 16) | (img->pixels[p + 2] << 8) | 0x0000FF;
	r = max->t.sprites[sprite->glowtexture]->pixels[p];
	g = max->t.sprites[sprite->glowtexture]->pixels[p + 1];
	b = max->t.sprites[sprite->glowtexture]->pixels[p + 2];
	a = max->t.sprites[sprite->glowtexture]->pixels[p + 3];
	c = r << 24 | g << 16 | b << 8 | a;
	if (a)
		mlx_put_pixel(max->i.spritescreen, x, y, c);
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
	int	i;
	i = 0;
	while (i < max->map.spritecount)
	{
		spx = max->map.sprites[i].x - max->map.p.x;
		spy = max->map.sprites[i].y - max->map.p.y;
		spz = max->map.sprites[i].z;
		(void)spz;
		direction = atan2(spx, -spy) * (MAXDEGREE / 2 / M_PI);
		//printf("%f\n", atan2(-spx, spy));
		if (direction > MAXDEGREE)
			direction -= MAXDEGREE;
		else if (direction < 0)
			direction += MAXDEGREE;
		distance = sqrt((double)spx * (double)spx + (double)spy * (double)spy);
		if (!distance)
			distance = 1;
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
			if (++max->map.sprites[i].frame == max->map.sprites[i].maxframe)
				max->map.sprites[i].frame = 0;
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
				x = 0;
				continue ;
			}
			if (x >= SCREENWIDTH)
				break ;
			r = x * RAYS / SCREENWIDTH;
			y = (SCREENHEIGHT - sprite_height) / 2;
			if (y < 0)
				y = 0;
			if (ft_sprite_visible(max, r, direction, radius, distance))
			{
				
				while (y < SCREENHEIGHT / 2 + sprite_height / 2)
				{
					if (y >= SCREENHEIGHT)
						break ;
					//check if any opacity, otherwise not put pixel
					if (distance < max->settings.lightdist && max->map.sprites[i].texture)
						ft_put_sprite_colour(max, xpa - sda - sprite_height / 2, x, y, sprite_height, &max->map.sprites[i]);
					if (max->map.sprites[i].glowtexture)
						ft_put_sprite_glowcolour(max, xpa - sda - sprite_height / 2, x, y, sprite_height, &max->map.sprites[i]);
					//mlx_put_pixel(max->i.screen, x, y, ((unsigned int)(rand() % 0xFFFFFF) << 8) | 0xFF);
					++y;
				}
			}
			++x;
		}
		++i;
	}
}
