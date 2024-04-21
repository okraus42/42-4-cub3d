/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:20:50 by okraus            #+#    #+#             */
/*   Updated: 2024/04/21 14:51:04 by okraus           ###   ########.fr       */
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
	map->m[(map->sprites[i].y >> 16) * map->w + (map->sprites[i].x >> 16)] &= 0x00000000FFFFFFFF;
	map->m[(map->sprites[i].y >> 16) * map->w + (map->sprites[i].x >> 16)] |= 0xFF80FFFF00000000;
	++map->current_sprite[SPRITE_FLAMINGO];
	++map->total_sprite[SPRITE_FLAMINGO];
	++map->spritecount;
}

void	ft_init_sprites(t_max *max)
{
	int	i;

	i = 0;
	printf("sprite  exit %i init\n", SPRITE_EXIT);
	max->map.sprites[SPRITE_EXIT].state = 0; //OFF
	max->map.sprites[SPRITE_EXIT].texture = EXIT_TEXTURE; //EXITTEXTURE
	max->map.sprites[SPRITE_EXIT].glowtexture = EXIT_GLOW; //EXITT GLOW EXTURE
	max->map.sprites[SPRITE_EXIT].type = SPRITE_EXIT; //EXIT
	max->map.sprites[SPRITE_EXIT].frame = 0;
	max->map.sprites[SPRITE_EXIT].maxframe = 32;
	max->map.sprites[SPRITE_EXIT].z = 20;
	max->map.spritecount = 1;
	while (i < SPRITETYPES)
	{
		max->map.current_sprite[i] = 0;
		max->map.total_sprite[i] = 0;
		++i;
	}
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
	unsigned int	spritefog;
	unsigned int	spritefogalpha;

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
	spritefog = max->map.b.rgba & 0xFFFFFF00;
	//BITWISE MAGIC LATER
	// 900 * 10 / 1000 9
	// printf("spritefog %8x\n", spritefog);
	spritefogalpha = (((long long)sprite->distance * 255 / max->settings.lightdist) & 0xFF);
	if (a > 0x80)
	{
		mlx_put_pixel(max->i.spritescreen, x, y, c);
		mlx_put_pixel(max->i.fogscreen, x, y, spritefog | spritefogalpha);
	}
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
	unsigned int	spritefog;
	unsigned int	spritefogalpha;

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
	spritefog = max->map.b.rgba & 0xFFFFFF00;
	//BITWISE MAGIC LATER
	// 900 * 10 / 1000 9
	// printf("spritefog %8x\n", spritefog);
	spritefogalpha = (((long long)sprite->distance * 255 / max->settings.maxdist) & 0xFF);
	if (a > 0x30)
	{
		mlx_put_pixel(max->i.spritescreen, x, y, c);
		mlx_put_pixel(max->i.fogscreen, x, y, spritefog | spritefogalpha);
	}
}

void	ft_activate_exit(t_max *max)
{
	int	i;

	i = 0;
	while (i < max->map.spritecount)
	{
		if (max->map.sprites[i].type == SPRITE_EXIT)
			max->map.sprites[i].state = 1;
		++i;
	}
}
void	ft_swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_print_sprite_info(t_sprite *sprite)
{
	ft_printf("type %i | state %i | frame %i | maxframe %i\n", sprite->type, sprite->state, sprite->frame, sprite->maxframe);
	// 	int	type;
	// int	state;
	// char	text[16];  //text on sprite e.g. "Libft"
	// int	frame;
	// int	maxframe;
	// int	texture; //map
	// int	glowtexture;
	// int	x;
	// int	y;
	// int	z;
	ft_printf("x %x, y %x, z %i\n", sprite->x, sprite->y, sprite->z);
	// int	spx; //sprite relative position
	// int	spy;
	// int	spz;
	ft_printf("spx %x, spy %x, spz %i\n", sprite->spx, sprite->spy, sprite->spz);
	// int			direction;
	// double		distance;
	printf("direction %i | distance %f\n", sprite->direction, sprite->distance);
	// int			radius; //angle
	// long long	length;
	ft_printf("radius %i | length %Li | height %i\n", sprite->radius, sprite->length, sprite->sprite_height);
	// int			sprite_height;
	// int	xpa;
	// int	relativedirection;
	// int sda;
	// int	xstart;
	// int	xend;
}

void	ft_check_sprites(t_max *max)
{
	int	fullangle; //move to settings?
	int	r;
	t_sprite	*sprite;
	

	//move elsewhere later?
	ft_clean_spritescreen(max);
	int	i;

	i = 0;
	if (max->keys[MLX_KEY_H])
	{
		max->keys[MLX_KEY_H] = 2;
		ft_printf("SPRITE INFO:\n", i);
		ft_printf("px %x py %x\n", max->map.p.x, max->map.p.y);
		while (i < max->map.spritecount)
		{
			sprite = &max->map.sprites[i];
			ft_printf("SPRITE INFO %i:\n", i);
			ft_print_sprite_info(sprite);
			++i;
		}
		i = 0;
	}
	while (i < max->map.spritecount)
	{
		sprite = &max->map.sprites[i];
		if (sprite->type == SPRITE_EXIT && !max->map.current_sprite[SPRITE_FLAMINGO])
			sprite->state = 1;
		sprite->spx = max->map.sprites[i].x - (int)max->map.p.x;
		sprite->spy = max->map.sprites[i].y - (int)max->map.p.y;
		sprite->spz = max->map.sprites[i].z;
		(void)sprite->spz;
		sprite->direction = atan2(sprite->spx, -sprite->spy) * (MAXDEGREE / 2 / M_PI);
		//printf("%f\n", atan2(-spx, spy));
		if (sprite->direction > MAXDEGREE)
			sprite->direction -= MAXDEGREE;
		else if (sprite->direction < 0)
			sprite->direction += MAXDEGREE;
		sprite->distance = sqrt((double)sprite->spx * (double)sprite->spx + (double)sprite->spy * (double)sprite->spy);
		if (!sprite->distance)
			sprite->distance = 1.;
		// good enough sort
		if (max->keys[MLX_KEY_H])
			printf("sprite: %i distance: %f\n", i, sprite->distance);
		if (i)
		{
			if (sprite->distance > max->map.sprites[i - 1].distance)
			{
				ft_swap_sprites(&max->map.sprites[i - 1], sprite);
			}
		}
		if (!sprite->state)
		{
			++i;
			continue ;
		}
		sprite->radius = atan(32768 / sprite->distance) * (MAXDEGREE / 2 / M_PI); //32768 = 65536/2
		// ft_printf("direction = %i\n", direction);
		// ft_printf("radius = %i\n", radius);

		r = 0;
		sprite->length = sprite->distance;
		if (max->settings.fisheyecorrection)
		{
			sprite->length *= max->math->cos[ft_capangle((max->map.p.orientation - max->map.p.oray[r].ra))];
			sprite->length /= 65536;
		}
		sprite->sprite_height = 65536 * SCREENHEIGHT / sprite->length;
		// if (sprite_height > SCREENHEIGHT) //needs offset later
		// 	sprite_height = SCREENHEIGHT;
		if (sprite->distance > (double)max->settings.maxdist)
		{
			++i;
			continue ;
		}
		if (sprite->distance < 65536 && sprite->type == SPRITE_FLAMINGO)
		{
			sprite->state = 0;
			max->score += 25000;
			max->limitms += 5000;
			max->timetriallimitms += 5000;
			max->map.m[(sprite->y >> 16) * max->map.w + (sprite->x >> 16)] &= 0x000000FFFFFFFFFF;
			max->map.m[(sprite->y >> 16) * max->map.w + (sprite->x >> 16)] |= (((unsigned long long)max->map.f.rgba << 32));
			printf("Collected flamingo\n");
			--max->map.current_sprite[SPRITE_FLAMINGO];
			if (!max->map.current_sprite[SPRITE_FLAMINGO])
				ft_activate_exit(max);
		}
		if (sprite->distance < 65536 && sprite->type == SPRITE_EXIT && sprite->state)
		{
			max->reachedexit = 1;
		}
		if (!(max->frame % 4))
			if (++sprite->frame == sprite->maxframe)
				sprite->frame = 0;
		//player angle
		//pa - fov/2 is left edge
		//pa + fov/2 is right edge
		//screenwidth = fov
		//sprite direction
		// x ~ pa - sprite direction + screenwidth/2
		
		sprite->xpa = SCREENWIDTH / 2;
		fullangle = 360 * SCREENWIDTH / max->settings.fov;
		sprite->relativedirection = max->map.p.orientation - sprite->direction;
		if (sprite->relativedirection < 0 - MAXDEGREE / 2)
			sprite->relativedirection += MAXDEGREE;
		if (sprite->relativedirection > MAXDEGREE / 2)
			sprite->relativedirection -= MAXDEGREE;
		//relativedirection is -180 - 180
		sprite->sda = fullangle * sprite->relativedirection / MAXDEGREE;
		sprite->xstart = sprite->xpa - sprite->sda - sprite->sprite_height / 2;
		sprite->xend = sprite->xstart + sprite->sprite_height;
		++i;
	}
	max->keys[MLX_KEY_H] = 0;
}


void	ft_draw_sprites(t_max *max)
{
	int	y;
	int	x;
	int	r;
	t_sprite	*sprite;

	//move elsewhere later?
	ft_clean_spritescreen(max);
	int	i;
	i = 0;
	while (i < max->map.spritecount)
	{
		sprite = &max->map.sprites[i];
		if (!sprite->state)
		{
			++i;
			continue ;
		}
		if (sprite->distance > max->settings.maxdist)
		{
			++i;
			continue ;
		}
		x = sprite->xstart;
		while (x < sprite->xend)
		{
			if (x < 0)
			{
				x = 0;
				continue ;
			}
			if (x >= SCREENWIDTH)
				break ;
			r = x * RAYS / SCREENWIDTH;
			y = (SCREENHEIGHT - sprite->sprite_height) / 2;
			if (y < 0)
				y = 0;
			if (ft_sprite_visible(max, r, sprite->direction, sprite->radius, sprite->distance))
			{
				
				while (y < SCREENHEIGHT / 2 + sprite->sprite_height / 2)
				{
					if (y >= SCREENHEIGHT)
						break ;
					//check if any opacity, otherwise not put pixel
					if (sprite->distance < max->settings.lightdist && sprite->texture)
						ft_put_sprite_colour(max, sprite->xpa - sprite->sda - sprite->sprite_height / 2, x, y, sprite->sprite_height, sprite);
					if (sprite->glowtexture)
						ft_put_sprite_glowcolour(max, sprite->xpa - sprite->sda - sprite->sprite_height / 2, x, y, sprite->sprite_height, sprite);
					//mlx_put_pixel(max->i.screen, x, y, ((unsigned int)(rand() % 0xFFFFFF) << 8) | 0xFF);
					++y;
				}
			}
			++x;
		}
		++i;
	}
}
