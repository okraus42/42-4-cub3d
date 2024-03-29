/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textfield.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:33:59 by okraus            #+#    #+#             */
/*   Updated: 2024/03/29 10:22:57 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_inittextfields(t_max *max)
{
	t_textfield	textfield;
	t_text		text;

	text.font = max->font.asciitest;
	text.image = max->menuscreen;
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
	textfield.image = max->menuscreen;
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
	int	c;
	int	shift;

	shift = 0;
	if (max->key.left_shift || max->key.right_shift)
		shift = -32;
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
	// if (max->key.left)
	// {
	// 	textfield->text.text[i] = '\0';
	// 	--i;
	// 	max->key.left = 0;
	// }
	// if (max->key.right)
	// {
	// 	++i;
	// 	max->key.right = 0;
	// }
	// if (max->key.up && textfield->text.text[i] > ' ')
	// {
	// 	--textfield->text.text[i];
	// 	max->key.up = 0;
	// }
	// if (max->key.down && textfield->text.text[i] < '~')
	// {
	// 	++textfield->text.text[i];
	// 	max->key.down = 0;
	// }
	if (max->key.backspace)
	{
		textfield->text.text[i] = '\0';
		if (i > 0)
			textfield->text.text[i - 1] = '\0';
		max->key.backspace = 0;
		--i;
	}
	// if (max->key.zero)
	// {
	// 	textfield->text.text[i] = '0';
	// 	max->key.zero = 0;
	// 	++i;
	// }
	// if (max->key.one)
	// {
	// 	textfield->text.text[i] = '1';
	// 	max->key.one = 0;
	// 	++i;
	// }
	// if (max->key.two)
	// {
	// 	textfield->text.text[i] = '2';
	// 	max->key.two = 0;
	// 	++i;
	// }
	// if (max->key.three)
	// {
	// 	textfield->text.text[i] = '3';
	// 	max->key.three = 0;
	// 	++i;
	// }
	// if (max->key.four)
	// {
	// 	textfield->text.text[i] = '4';
	// 	max->key.four = 0;
	// 	++i;
	// }
	// if (max->key.five)
	// {
	// 	textfield->text.text[i] = '5';
	// 	max->key.five = 0;
	// 	++i;
	// }
	// if (max->key.six)
	// {
	// 	textfield->text.text[i] = '6';
	// 	max->key.six = 0;
	// 	++i;
	// }
	// if (max->key.seven)
	// {
	// 	textfield->text.text[i] = '7';
	// 	max->key.seven = 0;
	// 	++i;
	// }
	// if (max->key.eight)
	// {
	// 	textfield->text.text[i] = '8';
	// 	max->key.eight = 0;
	// 	++i;
	// }
	// if (max->key.nine)
	// {
	// 	textfield->text.text[i] = '9';
	// 	max->key.nine = 0;
	// 	++i;
	// }
	c = 32;
	while (c <= 126)
	{
		if (max->keys[c])
		{
			textfield->text.text[i] = c;
			if (ft_isupper(c))
			{
				textfield->text.text[i] = 32 + c + shift;
			}
			if (c == MLX_KEY_MINUS && shift)
				textfield->text.text[i] = '_';
			max->keys[c] = 0;
			++i;
		}
		++c;
	}
	// if (max->key.space)
	// {
	// 	textfield->text.text[i] = ' ';
	// 	max->key.space = 0;
	// 	++i;
	// }
	// if (max->key.a)
	// {
	// 	textfield->text.text[i] = 'a' + shift;
	// 	max->key.a = 0;
	// 	++i;
	// }
	// if (max->key.b)
	// {
	// 	textfield->text.text[i] = 'b' + shift;
	// 	max->key.b = 0;
	// 	++i;
	// }
	// if (max->key.c)
	// {
	// 	textfield->text.text[i] = 'c' + shift;
	// 	max->key.c = 0;
	// 	++i;
	// }
	// if (max->key.d)
	// {
	// 	textfield->text.text[i] = 'd' + shift;
	// 	max->key.d = 0;
	// 	++i;
	// }
	// if (max->key.e)
	// {
	// 	textfield->text.text[i] = 'e' + shift;
	// 	max->key.e = 0;
	// 	++i;
	// }
	// if (max->key.f)
	// {
	// 	textfield->text.text[i] = 'f' + shift;
	// 	max->key.f = 0;
	// 	++i;
	// }
	// if (max->key.g)
	// {
	// 	textfield->text.text[i] = 'g' + shift;
	// 	max->key.g = 0;
	// 	++i;
	// }
	// if (max->key.h)
	// {
	// 	textfield->text.text[i] = 'h' + shift;
	// 	max->key.h = 0;
	// 	++i;
	// }
	// if (max->key.i)
	// {
	// 	textfield->text.text[i] = 'i' + shift;
	// 	max->key.i = 0;
	// 	++i;
	// }
	// if (max->key.j)
	// {
	// 	textfield->text.text[i] = 'j' + shift;
	// 	max->key.j = 0;
	// 	++i;
	// }
	// if (max->key.k)
	// {
	// 	textfield->text.text[i] = 'k' + shift;
	// 	max->key.k = 0;
	// 	++i;
	// }
	// if (max->key.l)
	// {
	// 	textfield->text.text[i] = 'l' + shift;
	// 	max->key.l = 0;
	// 	++i;
	// }
	// if (max->key.m)
	// {
	// 	textfield->text.text[i] = 'm' + shift;
	// 	max->key.m = 0;
	// 	++i;
	// }
	// if (max->key.n)
	// {
	// 	textfield->text.text[i] = 'n' + shift;
	// 	max->key.n = 0;
	// 	++i;
	// }
	// if (max->key.o)
	// {
	// 	textfield->text.text[i] = 'o' + shift;
	// 	max->key.o = 0;
	// 	++i;
	// }
	// if (max->key.p)
	// {
	// 	textfield->text.text[i] = 'p' + shift;
	// 	max->key.p = 0;
	// 	++i;
	// }
	// if (max->key.q)
	// {
	// 	textfield->text.text[i] = 'q' + shift;
	// 	max->key.q = 0;
	// 	++i;
	// }
	// if (max->key.r)
	// {
	// 	textfield->text.text[i] = 'r' + shift;
	// 	max->key.r = 0;
	// 	++i;
	// }
	// if (max->key.s)
	// {
	// 	textfield->text.text[i] = 's' + shift;
	// 	max->key.s = 0;
	// 	++i;
	// }
	// if (max->key.t)
	// {
	// 	textfield->text.text[i] = 't' + shift;
	// 	max->key.t = 0;
	// 	++i;
	// }
	// if (max->key.u)
	// {
	// 	textfield->text.text[i] = 'u' + shift;
	// 	max->key.u = 0;
	// 	++i;
	// }
	// if (max->key.v)
	// {
	// 	textfield->text.text[i] = 'v' + shift;
	// 	max->key.v = 0;
	// 	++i;
	// }
	// if (max->key.w)
	// {
	// 	textfield->text.	textfield->text.text[1] = '\0';text[i] = 'w' + shift;
	// 	max->key.w = 0;
	// 	++i;
	// }
	// if (max->key.x)
	// {
	// 	textfield->text.text[i] = 'x' + shift;
	// 	max->key.x = 0;
	// 	++i;
	// }
	// if (max->key.y)
	// {
	// 	textfield->text.text[i] = 'y' + shift;
	// 	max->key.y = 0;
	// 	++i;
	// }
	// if (max->key.z)
	// {
	// 	textfield->text.text[i] = 'z' + shift;
	// 	max->key.z = 0;
	// 	++i;
	// }
	textfield->text.highlight = i;
	textfield->text.text[16] = '\0';
	textfield->text.text[17] = '\0';
	textfield->text.text[18] = '\0';
	textfield->text.text[19] = '\0';
}
