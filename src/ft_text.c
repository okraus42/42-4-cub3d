/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_text.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:43:02 by okraus            #+#    #+#             */
/*   Updated: 2024/03/31 16:06:01 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"


void	ft_draw_char(t_text *text)
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
void	ft_draw_text(t_text *text, int state)
{
	int				i;
	unsigned int	oldcb;

	if (state & INACTIVE)
		text->c = 0x666666FF;
	else
		text->c = 0xFF;
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
		if (ft_isprint(text->text[i]))
		{
			text->offset = (text->text[i] - ' ') * 120;
			// if (text->offset)
			// 	text->offset -= 2; // add 2 pixels to image
			ft_draw_char(text);
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