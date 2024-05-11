/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textfield.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:33:59 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 19:46:36 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_inittextfields(t_max *max)
{
	t_textfield	textfield;
	t_text		text;

	ft_inittextfields_init(max, &textfield, &text);
	ft_inittextfields_init_name(max, &textfield);
	max->menu.newwritingfields[COALITION] = textfield;
	max->menu.newwritingfields[COALITION].state = ACTIVE;
	max->menu.newwritingfields[COALITION].x = 600;
	max->menu.newwritingfields[COALITION].y = 440;
	max->menu.newwritingfields[COALITION].text.text = max->coalition;
	max->menu.newwritingfields[COALITION].text.sx
		= max->menu.newwritingfields[COALITION].x + 80;
	max->menu.newwritingfields[COALITION].text.sy
		= max->menu.newwritingfields[COALITION].y + 50;
	max->menu.newwritingfields[CAMPUS] = textfield;
	max->menu.newwritingfields[CAMPUS].state = ACTIVE;
	max->menu.newwritingfields[CAMPUS].x = 600;
	max->menu.newwritingfields[CAMPUS].y = 720;
	max->menu.newwritingfields[CAMPUS].text.text = max->campus;
	max->menu.newwritingfields[CAMPUS].text.sx
		= max->menu.newwritingfields[CAMPUS].x + 80;
	max->menu.newwritingfields[CAMPUS].text.sy
		= max->menu.newwritingfields[CAMPUS].y + 50;
}

void	ft_draw_textfield_inner(t_textfield *tf, int state, t_db dt)
{
	dt.a = (dt.j * dt.w * 4) + (dt.i * 4);
	if (dt.i < dt.w && dt.j < dt.h)
		dt.c = (tf->textfield->pixels[dt.a]) << 24
			| (tf->textfield->pixels[dt.a + 1]) << 16
			| (tf->textfield->pixels[dt.a + 2]) << 8
			| (tf->textfield->pixels[dt.a + 3]);
	else
		dt.c = 0xFF00FFFF;
	if (dt.c & 0xFFFFFF00)
	{
		if (state & INACTIVE)
			mlx_put_pixel(tf->image, dt.i + tf->x, dt.j + tf->y, C_INACTIVE);
		else if (state & ACTIVE)
			mlx_put_pixel(tf->image, dt.i + tf->x, dt.j + tf->y, C_ACTIVE);
		else if (state & SELECTED)
			mlx_put_pixel(tf->image, dt.i + tf->x, dt.j + tf->y, C_SELECTED);
		else if (state & ACTIVATED)
			mlx_put_pixel(tf->image, dt.i + tf->x, dt.j + tf->y, C_ACTIVATED);
	}
	else if ((dt.c & 0xFF) == 0xFF)
		mlx_put_pixel(tf->image, dt.i + tf->x, dt.j + tf->y, dt.c);
}

void	ft_draw_textfield(t_textfield *tf, int state)
{
	t_db	dt;

	tf->state = state;
	dt.w = tf->textfield->width;
	dt.h = tf->textfield->height;
	dt.j = 0;
	while (dt.j < dt.h)
	{
		dt.i = 0;
		while (dt.i < dt.w)
		{
			ft_draw_textfield_inner(tf, state, dt);
			++dt.i;
		}
		++dt.j;
	}
	ft_draw_text(&tf->text, state);
}

void	ft_write_in_textfield_init(t_textfield *textfield, int *i)
{
	if (*i < 0)
	{
		*i = 0;
		while (textfield->text.text[*i])
			++*i;
	}
	if (*i < 0)
		*i = 0;
	if (*i > 15)
		*i = 15;
}

void	ft_write_in_textfield(t_max *max, t_textfield *textfield)
{
	int	i;

	i = textfield->text.highlight;
	ft_write_in_textfield_init(textfield, &i);
	textfield->text.text[i] = ' ';
	if (max->keys[MLX_KEY_BACKSPACE])
	{
		textfield->text.text[i] = '\0';
		if (i > 0)
			textfield->text.text[i - 1] = '\0';
		max->keys[MLX_KEY_BACKSPACE] = 0;
		--i;
	}
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
