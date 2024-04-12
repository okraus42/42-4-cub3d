/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textfield.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:33:59 by okraus            #+#    #+#             */
/*   Updated: 2024/04/12 09:17:12 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_inittextfields(t_max *max)
{
	t_textfield	textfield;
	t_text		text;

	text.font = max->font.asciitest;
	text.image = max->i.menuscreen;
	text.text = "";
	text.c = 0XFF;
	text.cb = 0;
	text.sx = 0;
	text.sy = 0;
	text.x = 0;
	text.y = 0;
	text.height = 60;
	text.highlight = -1;
	text.i = 0;
	text.offset = 0;
	textfield.textfield = max->menu.textfield;
	textfield.image = max->i.menuscreen;
	textfield.text = text;
	textfield.c = C_INACTIVE;
	textfield.x = 200;
	textfield.y = 0;
	textfield.w = 350;
	textfield.h = 150;
	textfield.state = INACTIVE;
	max->menu.newwritingfields[NAME] = textfield;
	max->menu.newwritingfields[NAME].state = ACTIVE;
	max->menu.newwritingfields[NAME].x = 600;
	max->menu.newwritingfields[NAME].y = 160;
	max->menu.newwritingfields[NAME].text.text = max->name;
	max->menu.newwritingfields[NAME].text.sx = max->menu.newwritingfields[NAME].x + 80;
	max->menu.newwritingfields[NAME].text.sy = max->menu.newwritingfields[NAME].y + 50;
	max->menu.newwritingfields[COALITION] = textfield;
	max->menu.newwritingfields[COALITION].state = ACTIVE;
	max->menu.newwritingfields[COALITION].x = 600;
	max->menu.newwritingfields[COALITION].y = 440;
	max->menu.newwritingfields[COALITION].text.text = max->coalition;
	max->menu.newwritingfields[COALITION].text.sx = max->menu.newwritingfields[COALITION].x + 80;
	max->menu.newwritingfields[COALITION].text.sy = max->menu.newwritingfields[COALITION].y + 50;
	max->menu.newwritingfields[CAMPUS] = textfield;
	max->menu.newwritingfields[CAMPUS].state = ACTIVE;
	max->menu.newwritingfields[CAMPUS].x = 600;
	max->menu.newwritingfields[CAMPUS].y = 720;
	max->menu.newwritingfields[CAMPUS].text.text = max->campus;
	max->menu.newwritingfields[CAMPUS].text.sx = max->menu.newwritingfields[CAMPUS].x + 80;
	max->menu.newwritingfields[CAMPUS].text.sy = max->menu.newwritingfields[CAMPUS].y + 50;
}

void	ft_draw_textfield(t_textfield *tf, int state)
{
	int				w;
	int				h;
	int				j;
	int				i;
	int				a;
	unsigned int	c;

	tf->state = state;
	w = tf->textfield->width;
	h = tf->textfield->height;
	j = 0;
	//draw textfield
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			a = (j * w * 4) + (i * 4);
			if (i < w && j < h)
				c = (tf->textfield->pixels[a]) << 24 | (tf->textfield->pixels[a + 1]) << 16 | (tf->textfield->pixels[a + 2]) << 8 | (tf->textfield->pixels[a + 3]);
			else
				c = 0xFF00FFFF;
			if (c & 0xFFFFFF00)
			{
				if (state & INACTIVE)
					mlx_put_pixel(tf->image, i + tf->x, j + tf->y, C_INACTIVE);
				else if (state & ACTIVE)
					mlx_put_pixel(tf->image, i + tf->x, j + tf->y, C_ACTIVE);
				else if (state & SELECTED)
					mlx_put_pixel(tf->image, i + tf->x, j + tf->y, C_SELECTED);
				else if (state & ACTIVATED)
					mlx_put_pixel(tf->image, i + tf->x, j + tf->y, C_ACTIVATED);
			}
			else if ((c & 0xFF) == 0xFF)
				mlx_put_pixel(tf->image, i + tf->x, j + tf->y, c);
			++i;
		}
		++j;
	}
	//draw text
	ft_draw_text(&tf->text, state);
}

void	ft_write_in_textfield(t_max *max, t_textfield *textfield)
{
	int	i;
	//int	c;
	// int	shift;

	// shift = 0;
	// if (max->keys[MLX_KEY_LEFT_SHIFT] || max->keys[MLX_KEY_RIGHT_SHIFT])
	// 	shift = -32;
	i = textfield->text.highlight;
	if (i < 0)
	{
		i = 0;
		while (textfield->text.text[i])
			++i;
	}
	if (i < 0)
		i = 0;
	if (i > 15)
		i = 15;
	textfield->text.text[i] = ' ';
	// if (max->keys[MLX_KEY_LEFT])
	// {
	// 	textfield->text.text[i] = '\0';
	// 	--i;
	// 	max->keys[MLX_KEY_LEFT] = 0;
	// }
	// if (max->keys[MLX_KEY_RIGHT])
	// {
	// 	++i;
	// 	max->keys[MLX_KEY_RIGHT] = 0;
	// }
	// if (max->keys[MLX_KEY_UP] && textfield->text.text[i] > ' ')
	// {
	// 	--textfield->text.text[i];
	// 	max->keys[MLX_KEY_UP] = 0;
	// }
	// if (max->keys[MLX_KEY_DOWN] && textfield->text.text[i] < '~')
	// {
	// 	++textfield->text.text[i];
	// 	max->keys[MLX_KEY_DOWN] = 0;
	// }
	if (max->keys[MLX_KEY_BACKSPACE])
	{
		textfield->text.text[i] = '\0';
		if (i > 0)
			textfield->text.text[i - 1] = '\0';
		max->keys[MLX_KEY_BACKSPACE] = 0;
		--i;
	}
	// c = 32;
	// while (c <= 126)
	// {
	// 	// if (max->keys[c])
	// 	// {
	// 	// 	textfield->text.text[i] = c;
	// 	// 	if (ft_isupper(c))
	// 	// 	{
	// 	// 		textfield->text.text[i] = 32 + c + shift;
	// 	// 	}
	// 	// 	if (c == MLX_KEY_MINUS && shift)
	// 	// 		textfield->text.text[i] = '_';
	// 	// 	max->keys[c] = 0;
	// 		++i;
	// 	}
	// 	++c;
	// }
	if (max->kb.character)
	{
		textfield->text.text[i] = max->kb.character;
		max->kb.character = 0;
		++i;
	}
	textfield->text.highlight = i;
	textfield->text.text[16] = '\0';
	textfield->text.text[17] = '\0';
	textfield->text.text[18] = '\0';
	textfield->text.text[19] = '\0';
}
