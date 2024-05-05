/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_text.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:43:02 by okraus            #+#    #+#             */
/*   Updated: 2024/04/14 14:36:09 by okraus           ###   ########.fr       */
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
		//printf("char %i %p\n", j, text->font);
		while (i < w)
		{
			//printf("char %i %i %p %p\n", j, i, text->font);
			a = (j * (240 / text->height) * 11400 * 4) + ((i * (240 / text->height) + text->offset) * 4);
			c = (text->font->pixels[a]) << 24 | (text->font->pixels[a + 1]) << 16 | (text->font->pixels[a + 2]) << 8 | (text->font->pixels[a + 3]);
			if (c < 0x7FFFFFFF)
			{
				//printf("chara %i %i\n", j, i);
				mlx_put_pixel(text->image, i + text->x, j + text->y, text->c);
			}
			else if (text->cb)
			{
				//printf("charb %i %i\n", j, i);
				mlx_put_pixel(text->image, i + text->x, j + text->y, text->cb);
			}
			//printf("charc %i %i\n", j, i);
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
	unsigned int	oldc;

	oldcb = text->cb;
	oldc = text->c;
	if (state & INACTIVE)
		text->c = 0x666666FF;
	// else
	// 	text->c = 0xFF;
	
	i = 0;
	text->x = text->sx;
	text->y = text->sy;
	//printf("Hello %s\n", text->text);
	while (text->text[i])
	{
		//printf("Hello %i\n", i);
		if (i == text->highlight)
		{
			text->cb = 0x00FF00FF;
		}
		else
		{
			text->cb = oldcb;
		}
		//printf("Hello2 %i\n", i);
		if (ft_isprint(text->text[i]))
		{
			text->offset = (text->text[i] - ' ') * 120;
			// if (text->offset)
			// 	text->offset -= 2; // add 2 pixels to image
			//printf("Hello3a %i\n", i);
			ft_draw_char(text);
			//printf("Hello3b %i\n", i);
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
	//printf("Farewell\n");
	text->cb = oldcb;
	text->c = oldc;
}
