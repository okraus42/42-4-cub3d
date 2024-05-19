/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:29:30 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 18:32:16 by tlukanie         ###   ########.fr       */
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
