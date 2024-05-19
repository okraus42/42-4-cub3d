/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textfield_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:43:28 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 19:44:30 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_inittextfields_init(t_max *max, t_textfield *textfield, t_text *text)
{
	text->font = max->font.asciitest;
	text->image = max->i.menuscreen;
	text->text = "";
	text->c = 0XFF;
	text->cb = 0;
	text->sx = 0;
	text->sy = 0;
	text->x = 0;
	text->y = 0;
	text->height = 60;
	text->highlight = -1;
	text->i = 0;
	text->offset = 0;
	textfield->textfield = max->menu.textfield;
	textfield->image = max->i.menuscreen;
	textfield->text = *text;
	textfield->c = C_INACTIVE;
	textfield->x = 200;
	textfield->y = 0;
	textfield->w = 350;
	textfield->h = 150;
	textfield->state = INACTIVE;
}

void	ft_inittextfields_init_name(t_max *max, t_textfield *textfield)
{
	max->menu.newwritingfields[NAME] = *textfield;
	max->menu.newwritingfields[NAME].state = ACTIVE;
	max->menu.newwritingfields[NAME].x = 600;
	max->menu.newwritingfields[NAME].y = 160;
	max->menu.newwritingfields[NAME].text.text = max->name;
	max->menu.newwritingfields[NAME].text.sx
		= max->menu.newwritingfields[NAME].x + 80;
	max->menu.newwritingfields[NAME].text.sy
		= max->menu.newwritingfields[NAME].y + 50;
}
