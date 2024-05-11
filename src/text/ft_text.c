/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_text.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:43:02 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 16:52:08 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_draw_char(t_text *text)
{
	t_db	dc;

	dc.w = text->height / 2;
	dc.h = text->height;
	dc.j = 0;
	while (dc.j < dc.h)
	{
		dc.i = 0;
		while (dc.i < dc.w)
		{
			dc.a = (dc.j * (240 / text->height) * 11400 * 4)
				+ ((dc.i * (240 / text->height) + text->offset) * 4);
			dc.c = (text->font->pixels[dc.a]) << 24
				| (text->font->pixels[dc.a + 1]) << 16
				| (text->font->pixels[dc.a + 2]) << 8
				| (text->font->pixels[dc.a + 3]);
			if (dc.c < 0x7FFFFFFF)
				mlx_put_pixel(text->image, dc.i + text->x, dc.j + text->y, text->c);
			else if (text->cb)
				mlx_put_pixel(text->image, dc.i + text->x, dc.j + text->y, text->cb);
			++dc.i;
		}
		++dc.j;
	}
}

void	ft_draw_text(t_text *text, int state)
{
	int				i;
	unsigned int	oldcb;
	unsigned int	oldc;

	oldcb = text->cb;
	oldc = text->c;
	if (state & INACTIVE)
		text->c = 0x666666FF;
	i = 0;
	text->x = text->sx;
	text->y = text->sy;
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
	text->cb = oldcb;
	text->c = oldc;
}
