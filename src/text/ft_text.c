/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_text.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:43:02 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 19:20:18 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_draw_char(t_text *text)
{
	t_db	dc;

	dc.w = text->height / 2;
	dc.h = text->height;
	dc.j = -1;
	while (++dc.j < dc.h)
	{
		dc.i = -1;
		while (++dc.i < dc.w)
		{
			dc.a = (dc.j * (240 / text->height) * 11400 * 4)
				+ ((dc.i * (240 / text->height) + text->offset) * 4);
			dc.c = (text->font->pixels[dc.a]) << 24
				| (text->font->pixels[dc.a + 1]) << 16
				| (text->font->pixels[dc.a + 2]) << 8
				| (text->font->pixels[dc.a + 3]);
			if (dc.c < 0x7FFFFFFF)
				mlx_put_pixel(text->image,
					dc.i + text->x, dc.j + text->y, text->c);
			else if (text->cb)
				mlx_put_pixel(text->image,
					dc.i + text->x, dc.j + text->y, text->cb);
		}
	}
}

void	ft_draw_text_loop(t_text *text, unsigned int oldcb)
{
	int	i;

	i = 0;
	while (text->text[i])
	{
		if (i == text->highlight)
			text->cb = 0x00FF00FF;
		else
			text->cb = oldcb;
		if (ft_isprint(text->text[i]))
		{
			text->offset = (text->text[i] - ' ') * 120;
			ft_draw_char(text);
			text->x += text->height / 2;
		}
		else if (text->text[i] == '\t')
			text->x += text->height * 2;
		else if (text->text[i] == '\n')
		{
			text->y += text->height;
			text->x = text->sx;
		}
		++i;
	}
}

void	ft_draw_text(t_text *text, int state)
{
	unsigned int	oldcb;
	unsigned int	oldc;

	oldcb = text->cb;
	oldc = text->c;
	if (state & INACTIVE)
		text->c = 0x666666FF;
	text->x = text->sx;
	text->y = text->sy;
	ft_draw_text_loop(text, oldcb);
	text->cb = oldcb;
	text->c = oldc;
}
