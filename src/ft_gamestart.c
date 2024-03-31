/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamestart.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:57:06 by okraus            #+#    #+#             */
/*   Updated: 2024/03/31 14:46:54 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_initgamestart(t_max *max)
{
	ft_load_texture("./textures/woodenboard.png", &max->gamestart.background);
	max->gamestart.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
	max->gamestart.font = max->font.asciitest;
	max->gamestart.image = max->textscreen;
	max->gamestart.c = 0XFF;
	max->gamestart.cb = 0;
	max->gamestart.sx = 200;
	max->gamestart.sy = 100;
	max->gamestart.x = 0;
	max->gamestart.y = 0;
	max->gamestart.height = 80;
	max->gamestart.highlight = -1;
	max->gamestart.i = 0;
}

void	ft_draw_background(t_max *max)
{
	int				w;
	int				h;
	int				y;
	int				x;
	int				a;
	unsigned int	c;

	w = max->gamestart.background->width;
	h = max->gamestart.background->height;
	y = 0;
	//draw background
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			a = (y * w * 4) + (x * 4);
			if (x < w && y < h)
				c = (max->gamestart.background->pixels[a]) << 24 | (max->gamestart.background->pixels[a + 1]) << 16 | (max->gamestart.background->pixels[a + 2]) << 8 | 0xFF;
			else
				c = 0xFF00FFFF;
			mlx_put_pixel(max->textscreen, x, y, c);
			++x;
		}
		++y;
	}
}

void	ft_draw_gamestartchar(t_gametext *text)
{
	int				w;
	int				h;
	int				j;
	int				i;
	int				a;
	unsigned int	c;

	w = text->height / 2;
	h = text->height;
	j = 0;
	//draw letter
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			//720 length of png
			a = (j * (240 / text->height) * 11400 * 4) + ((i * (240 / text->height) + text->offset) * 4);
			c = (text->font->pixels[a]) << 24 | (text->font->pixels[a + 1]) << 16 | (text->font->pixels[a + 2]) << 8 | (text->font->pixels[a + 3]);
			if (c < 0x7FFFFFFF)
			{
				mlx_put_pixel(text->image, i + text->x, j + text->y, text->c);
			}
			else if (text->cb)
			{
				mlx_put_pixel(text->image, i + text->x, j + text->y, text->cb);
			}
			// (void)colour;
			// mlx_put_pixel(image, i + x, j + y, c);
			++i;
		}
		++j;
	}
}

//(120) for the width of the character in the font.png
void	ft_draw_gamestarttext(t_gametext *text)
{
	int				i;
	unsigned int	oldcb;

	oldcb = text->cb;
	i = 0;
	text->x = text->sx;
	text->y = text->sy;
	while (text->text[i])
	{
		if (i == text->highlight)
		{
			text->cb = 0x00FF00FF;
		}
		else
		{
			text->cb = oldcb;
		}
		if (i > text->i)
			return ;
		if (text->x > 1920 - 200 - text->height / 2)
		{
			text->y += text->height;
			text->x = text->sx;
		}
		if (text->y > 1080 - 100 - text->height)
		{
			return ;
		}
		if (ft_isprint(text->text[i]))
		{
			text->offset = (text->text[i] - ' ') * 120;
			if (text->offset)
				text->offset -= 2; // add 2 pixels to image
			ft_draw_gamestartchar(text);
			text->x += text->height / 2;
		}
		else if (text->text[i] == '\t')
		{
			text->x += text->height * 2;
		}
		else if (text->text[i] == '\n')
		{
			text->y += text->height;
			text->x = text->sx;
		}
		++i;
	}
	text->cb = oldcb;
}

void	ft_gamestart(t_max *max)
{
	max->gamestart.timems += max->framems;

	ft_draw_background(max);
	if (max->gamestart.timems >= 25)
	{
		max->gamestart.timems = 0;
		if (max->gamestart.i <= (int)ft_strlen(max->gamestart.text))
			++max->gamestart.i;
	}
	ft_draw_gamestarttext(&max->gamestart);

	//launch game after user input
	if (max->keys[MLX_KEY_ENTER])
	{
		max->game_mode = GAMEPLAY;
		max->textscreen->enabled = 0;
		max->game_in_progress = 1;
		max->gamestart.i = 0;
		max->keys[MLX_KEY_ENTER] = 0;
	}
	//launch game
}