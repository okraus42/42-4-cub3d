/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listfield.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:00:54 by okraus            #+#    #+#             */
/*   Updated: 2024/03/31 14:45:59 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_initlistfields(t_max *max)
{
	t_listfield	listfield;
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
	listfield.listfield = max->menu.listfield;
	listfield.image = max->menuscreen;
	listfield.text[0] = text;
	listfield.text[1] = text;
	listfield.text[2] = text;
	listfield.text[3] = text;
	listfield.text[4] = text;
	listfield.c = C_INACTIVE;
	listfield.x = 200;
	listfield.y = 0;
	listfield.w = 350;
	listfield.h = 150;
	listfield.highlight = 0;
	listfield.state = INACTIVE;
	max->menu.custommap = listfield;
	max->menu.custommap.state = ACTIVE;
	max->menu.custommap.x = 600;
	max->menu.custommap.y = 160;
	max->menu.custommap.files[0] = "maps/validmap1.cub";
	max->menu.custommap.files[1] = "maps/validmap2.cub";
	max->menu.custommap.files[2] = "maps/validmap3.cub";
	max->menu.custommap.files[3] = "maps/validmap4.cub";
	max->menu.custommap.files[4] = "maps/validmap5.cub";
	max->menu.custommap.text[0].text = max->menu.custommap.files[0];
	max->menu.custommap.text[0].sx = max->menu.custommap.x + 120;
	max->menu.custommap.text[0].sy = max->menu.custommap.y + 120;
	max->menu.custommap.text[1].text = max->menu.custommap.files[1];
	max->menu.custommap.text[1].sx = max->menu.custommap.x + 120;
	max->menu.custommap.text[1].sy = max->menu.custommap.y + 200;
	max->menu.custommap.text[2].text = max->menu.custommap.files[2];
	max->menu.custommap.text[2].sx = max->menu.custommap.x + 120;
	max->menu.custommap.text[2].sy = max->menu.custommap.y + 280;
	max->menu.custommap.text[3].text = max->menu.custommap.files[3];
	max->menu.custommap.text[3].sx = max->menu.custommap.x + 120;
	max->menu.custommap.text[3].sy = max->menu.custommap.y + 360;
	max->menu.custommap.text[4].text = max->menu.custommap.files[4];
	max->menu.custommap.text[4].sx = max->menu.custommap.x + 120;
	max->menu.custommap.text[4].sy = max->menu.custommap.y + 440;
}

void	ft_draw_listfield(t_listfield *lf, int state)
{
	int				w;
	int				h;
	int				j;
	int				i;
	int				a;
	unsigned int	c;

	lf->state = state;
	w = lf->listfield->width;
	h = lf->listfield->height;
	j = 0;
	//draw listfield
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			a = (j * w * 4) + (i * 4);
			if (i < w && j < h)
				c = (lf->listfield->pixels[a]) << 24 | (lf->listfield->pixels[a + 1]) << 16 | (lf->listfield->pixels[a + 2]) << 8 | (lf->listfield->pixels[a + 3]);
			else
				c = 0xFF00FFFF;
			if (c & 0xFFFFFF00)
			{
				if (state & INACTIVE)
					mlx_put_pixel(lf->image, i + lf->x, j + lf->y, C_INACTIVE);
				else if (state & ACTIVE)
					mlx_put_pixel(lf->image, i + lf->x, j + lf->y, C_ACTIVE);
				else if (state & SELECTED)
					mlx_put_pixel(lf->image, i + lf->x, j + lf->y, C_SELECTED);
				else if (state & ACTIVATED)
					mlx_put_pixel(lf->image, i + lf->x, j + lf->y, C_ACTIVATED);
			}
			else if ((c & 0xFF) == 0xFF)
				mlx_put_pixel(lf->image, i + lf->x, j + lf->y, c);
			++i;
		}
		++j;
	}
	//draw text
	lf->text[lf->highlight].cb = 0x00FF00FF;
	ft_draw_text(&lf->text[0], state);
	ft_draw_text(&lf->text[1], state);
	ft_draw_text(&lf->text[2], state);
	ft_draw_text(&lf->text[3], state);
	ft_draw_text(&lf->text[4], state);
}

void	ft_choose_in_listfield(t_max *max, t_listfield *listfield)
{
	int	i;

	i = listfield->highlight;
	listfield->text[i].cb = 0;
	if (max->keys[MLX_KEY_UP])
	{
		--i;
		max->keys[MLX_KEY_UP] = 0;
	}
	if (max->keys[MLX_KEY_DOWN])
	{
		++i;
		max->keys[MLX_KEY_DOWN] = 0;
	}
	if (i < 0)
		i = 0;
	if (i > 4)
		i = 4;
	listfield->highlight = i;
}
