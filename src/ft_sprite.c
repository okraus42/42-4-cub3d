/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:20:50 by okraus            #+#    #+#             */
/*   Updated: 2024/05/10 20:13:46 by okraus           ###   ########.fr       */
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
	map->sprites[i].state = 1;
	map->sprites[i].texture = FLAMINGO_TEXTURE;
	map->sprites[i].glowtexture = FLAMINGO_GLOW;
	map->sprites[i].type = SPRITE_FLAMINGO;
	map->sprites[i].frame = 0;
	map->sprites[i].maxframe = 1;
	map->sprites[i].z = 20;
	map->m[(map->sprites[i].y >> 16) * map->w + (map->sprites[i].x >> 16)]
		&= 0x00000000FFFFFFFF;
	map->m[(map->sprites[i].y >> 16) * map->w + (map->sprites[i].x >> 16)]
		|= 0xFF80FFFF00000000;
	++map->current_sprite[SPRITE_FLAMINGO];
	++map->total_sprite[SPRITE_FLAMINGO];
	++map->spritecount;
}

void	ft_init_sprites(t_max *max)
{
	int	i;

	i = 0;
	max->map.sprites[SPRITE_EXIT].state = 0;
	max->map.sprites[SPRITE_EXIT].texture = EXIT_TEXTURE;
	max->map.sprites[SPRITE_EXIT].glowtexture = EXIT_GLOW;
	max->map.sprites[SPRITE_EXIT].type = SPRITE_EXIT;
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

int	ft_sprite_visible_check(t_max *max, int minangle, int maxangle)
{
	if (minangle < maxangle)
	{
		if (max->map.p.oray[0].ra < max->map.p.oray[RAYS - 1].ra)
		{
			if (max->map.p.oray[RAYS - 1].ra < minangle
				|| max->map.p.oray[0].ra > maxangle)
				return (0);
		}
		else
		{
			if (max->map.p.oray[RAYS - 1].ra < minangle
				&& max->map.p.oray[0].ra > maxangle)
				return (0);
		}
	}
	else
	{
		if (max->map.p.oray[0].ra < max->map.p.oray[RAYS - 1].ra)
		{
			if (max->map.p.oray[RAYS - 1].ra < minangle
				&& max->map.p.oray[0].ra > maxangle)
				return (0);
		}
	}
	return (1);
}

//if sprite is outsite of field of view, do not draw it
int	ft_sprite_visible(t_max *max, int direction, int radius)
{
	int	minangle;
	int	maxangle;

	minangle = direction - radius;
	maxangle = direction + radius;
	if (minangle < 0)
		minangle += MAXDEGREE;
	if (maxangle >= MAXDEGREE)
		maxangle -= MAXDEGREE;
	return (ft_sprite_visible_check(max, minangle, maxangle));
}

//if sprite is behind a wall, do not draw it
int	ft_sprite_visible2(t_max *max, int r, long long distance)
{
	if (max->map.p.oray[r].wall && distance > max->map.p.oray[r].length)
		return (0);
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

void	ft_put_sprite_colour(t_max *max, t_sprite *sprite, t_sp *sp)
{
	sp->starty = (SCREENHEIGHT - sp->size) / 2;
	sp->w = max->t.sprites[sprite->texture]->width;
	sp->h = max->t.sprites[sprite->texture]->height;
	sp->u = ((sp->x - sp->startx) * (sp->w / sprite->maxframe)) / (sp->size);
	sp->u += sprite->frame * (sp->w / sprite->maxframe);
	sp->v = ((sp->y - sp->starty) * sp->h) / (sp->size);
	sp->p = sp->w * 4 * (sp->v) + (4 * (sp->u));
	sp->r = max->t.sprites[sprite->texture]->pixels[sp->p];
	sp->g = max->t.sprites[sprite->texture]->pixels[sp->p + 1];
	sp->b = max->t.sprites[sprite->texture]->pixels[sp->p + 2];
	sp->a = max->t.sprites[sprite->texture]->pixels[sp->p + 3];
	sp->c = sp->r << 24 | sp->g << 16 | sp->b << 8 | sp->a;
	sp->spritefog = max->map.b.rgba & 0xFFFFFF00;
	sp->spritefogalpha = (((long long)sprite->distance * 255
				/ max->settings.lightdist) & 0xFF);
	if (sp->a > 0x80)
	{
		mlx_put_pixel(max->i.spritescreen, sp->x, sp->y, sp->c);
		mlx_put_pixel(max->i.fogscreen, sp->x, sp->y, sp->spritefog
			| sp->spritefogalpha);
	}
}

void	ft_put_sprite_glowcolour(t_max *max, t_sprite *sprite, t_sp *sp)
{
	sp->starty = (SCREENHEIGHT - sp->size) / 2;
	sp->w = max->t.sprites[sprite->glowtexture]->width;
	sp->h = max->t.sprites[sprite->glowtexture]->height;
	sp->u = ((sp->x - sp->startx) * (sp->w / sprite->maxframe)) / (sp->size);
	sp->u += sprite->frame * (sp->w / sprite->maxframe);
	sp->v = ((sp->y - sp->starty) * sp->h) / (sp->size);
	sp->p = sp->w * 4 * (sp->v) + (4 * (sp->u));
	sp->r = max->t.sprites[sprite->glowtexture]->pixels[sp->p];
	sp->g = max->t.sprites[sprite->glowtexture]->pixels[sp->p + 1];
	sp->b = max->t.sprites[sprite->glowtexture]->pixels[sp->p + 2];
	sp->a = max->t.sprites[sprite->glowtexture]->pixels[sp->p + 3];
	sp->c = sp->r << 24 | sp->g << 16 | sp->b << 8 | sp->a;
	sp->spritefog = max->map.b.rgba & 0xFFFFFF00;
	sp->spritefogalpha = (((long long)sprite->distance * 255
				/ max->settings.maxdist) & 0xFF);
	if (sp->a > 0x30)
	{
		mlx_put_pixel(max->i.spritescreen, sp->x, sp->y, sp->c);
		mlx_put_pixel(max->i.fogscreen, sp->x, sp->y, sp->spritefog
			| sp->spritefogalpha);
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
	ft_printf("type %i | state %i | frame %i | maxframe %i\n",
		sprite->type, sprite->state, sprite->frame, sprite->maxframe);
	ft_printf("x %x, y %x, z %i\n", sprite->x, sprite->y, sprite->z);
	ft_printf("spx %x, spy %x, spz %i\n",
		sprite->spx, sprite->spy, sprite->spz);
	printf("direction %i | distance %f\n",
		sprite->direction, sprite->distance);
	ft_printf("radius %i | length %Li | height %i\n",
		sprite->radius, sprite->length, sprite->sprite_height);
}

// draw left half and right half of the door
// calculate left edge and right edge distance from player
// calculate x start and x end

void	ft_check_sprites_debug(t_max *max)
{
	int			i;
	t_sprite	*sprite;

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
}

void	ft_check_sprites_1(t_max *max, t_sprite *sprite, int i)
{
	if (sprite->type == SPRITE_EXIT
		&& !max->map.current_sprite[SPRITE_FLAMINGO])
		sprite->state = 1;
	sprite->spx = max->map.sprites[i].x - (int)max->map.p.x;
	sprite->spy = max->map.sprites[i].y - (int)max->map.p.y;
	sprite->spz = max->map.sprites[i].z;
	(void)sprite->spz;
	sprite->direction = atan2(sprite->spx, -sprite->spy)
		* (MAXDEGREE / 2 / M_PI);
	if (sprite->direction > MAXDEGREE)
		sprite->direction -= MAXDEGREE;
	else if (sprite->direction < 0)
		sprite->direction += MAXDEGREE;
	sprite->distance = sqrt((double)sprite->spx * (double)sprite->spx
			+ (double)sprite->spy * (double)sprite->spy);
	if (!sprite->distance)
		sprite->distance = 1.;
	if (max->keys[MLX_KEY_H])
		printf("sprite: %i distance: %f\n", i, sprite->distance);
	if (i)
	{
		if (sprite->distance > max->map.sprites[i - 1].distance)
			ft_swap_sprites(&max->map.sprites[i - 1], sprite);
	}
}

void	ft_check_sprites_2(t_max *max, t_sprite *sprite)
{
	sprite->visible = 1;
	sprite->length = sprite->distance;
	if (max->settings.fisheyecorrection)
	{
		sprite->length *= max->math->cos[ft_capangle(max->map.p.orientation
				- sprite->direction)];
		sprite->length /= 65536;
	}
	if (!sprite->length)
		sprite->length = 1;
	sprite->sprite_height = 65536 * SCREENHEIGHT / sprite->length;
}

void	ft_check_sprites_exit(t_max *max, t_sprite *sprite)
{
	if (sprite->distance < 65536 && sprite->type == SPRITE_FLAMINGO)
	{
		sprite->state = 0;
		max->score += 25000;
		max->limitms += 15000;
		max->timetriallimitms += 15000;
		max->map.m[(sprite->y >> 16) * max->map.w + (sprite->x >> 16)]
			&= 0x000000FFFFFFFFFF;
		max->map.m[(sprite->y >> 16) * max->map.w + (sprite->x >> 16)]
			|= (((unsigned long long)max->map.f.rgba << 32));
		ft_printf("Collected flamingo\n");
		--max->map.current_sprite[SPRITE_FLAMINGO];
		if (!max->map.current_sprite[SPRITE_FLAMINGO])
			ft_activate_exit(max);
	}
	if (sprite->distance < 65536 && sprite->type == SPRITE_EXIT
		&& sprite->state)
		max->reachedexit = 1;
}

void	ft_check_sprites_3(t_max *max, t_sprite *sprite)
{
	int	fullangle;

	ft_check_sprites_exit(max, sprite);
	if (!(max->frame % 4))
		if (++sprite->frame == sprite->maxframe)
			sprite->frame = 0;
	sprite->xpa = SCREENWIDTH / 2;
	fullangle = 360 * SCREENWIDTH / max->settings.fov;
	sprite->relativedirection = max->map.p.orientation - sprite->direction;
	if (sprite->relativedirection < 0 - MAXDEGREE / 2)
		sprite->relativedirection += MAXDEGREE;
	if (sprite->relativedirection > MAXDEGREE / 2)
		sprite->relativedirection -= MAXDEGREE;
	sprite->sda = fullangle * sprite->relativedirection / MAXDEGREE;
	sprite->xstart = sprite->xpa - sprite->sda - sprite->sprite_height / 2;
	sprite->xend = sprite->xstart + sprite->sprite_height;
}

void	ft_check_sprites(t_max *max)
{
	int			i;
	t_sprite	*sprite;

	ft_clean_spritescreen(max);
	ft_check_sprites_debug(max);
	i = -1;
	while (++i < max->map.spritecount)
	{
		sprite = &max->map.sprites[i];
		ft_check_sprites_1(max, sprite, i);
		if (!sprite->state)
			continue ;
		sprite->radius = atan(32768 / sprite->distance)
			* (MAXDEGREE / 2 / M_PI);
		if (!ft_sprite_visible(max, sprite->direction, sprite->radius))
		{
			sprite->visible = 0;
			continue ;
		}
		ft_check_sprites_2(max, sprite);
		if (sprite->distance > (double)max->settings.maxdist)
			continue ;
		ft_check_sprites_3(max, sprite);
	}
	max->keys[MLX_KEY_H] = 0;
}

void	ft_draw_sprite(t_max *max, t_sprite *sprite, t_sp *sp)
{
	while (sp->x < sprite->xend)
	{
		if (sp->x >= SCREENWIDTH)
			break ;
		sp->ray = sp->x * RAYS / SCREENWIDTH;
		sp->y = (SCREENHEIGHT - sprite->sprite_height) / 2;
		sp->y = (sp->y <= 0) * (-1) + (sp->y > 0) * (sp->y - 1);
		if (ft_sprite_visible2(max, sp->ray, sprite->distance))
		{
			while (++sp->y < SCREENHEIGHT / 2 + sprite->sprite_height / 2)
			{
				if (sp->y >= SCREENHEIGHT)
					break ;
				sp->startx = sprite->xpa
					- sprite->sda - sprite->sprite_height / 2;
				sp->size = sprite->sprite_height;
				if (sprite->distance < max->settings.lightdist
					&& sprite->texture)
					ft_put_sprite_colour(max, sprite, sp);
				if (sprite->glowtexture)
					ft_put_sprite_glowcolour(max, sprite, sp);
			}
		}
		++sp->x;
	}
}

void	ft_draw_sprites(t_max *max)
{
	t_sp		sp;
	int			i;
	t_sprite	*sprite;

	ft_clean_spritescreen(max);
	i = 0;
	while (i < max->map.spritecount)
	{
		sprite = &max->map.sprites[i];
		if (!sprite->state || !sprite->visible || sprite->distance < 4096
			|| sprite->distance > max->settings.maxdist)
		{
			++i;
			continue ;
		}
		sp.x = sprite->xstart;
		if (sp.x < 0)
			sp.x = 0;
		ft_draw_sprite(max, sprite, &sp);
		++i;
	}
}
