/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:20:50 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 18:33:08 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
