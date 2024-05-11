/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:25:50 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 18:27:11 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
