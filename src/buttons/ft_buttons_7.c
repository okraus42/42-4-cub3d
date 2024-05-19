/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons_7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:50:48 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 16:51:45 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initbutton_rwidth(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RWIDTH] = button;
	max->menu.randomadvancedbuttons[RWIDTH].id = RWIDTH;
	max->menu.randomadvancedbuttons[RWIDTH].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RWIDTH].down = &max->menu
		.randomadvancedbuttons[RRATIODE];
	max->menu.randomadvancedbuttons[RWIDTH].right = &max->menu
		.randomadvancedbuttons[RHEIGHT];
	max->menu.randomadvancedbuttons[RWIDTH].state = ACTIVE;
	max->menu.randomadvancedbuttons[RWIDTH].x = 700;
	max->menu.randomadvancedbuttons[RWIDTH].y = 20;
	max->menu.randomadvancedbuttons[RWIDTH].str = S_RWIDTH;
	max->menu.randomadvancedbuttons[RWIDTH].val = &max->menu.rm.width;
	ft_snprintf(max->menu.randomadvancedbuttons[RWIDTH].text.str,
		19, "%s: %i", S_RWIDTH, max->menu
		.randomadvancedbuttons[RWIDTH].val->value);
	max->menu.randomadvancedbuttons[RWIDTH].text.text = max->menu
		.randomadvancedbuttons[RWIDTH].text.str;
	max->menu.randomadvancedbuttons[RWIDTH].text.sx = max->menu
		.randomadvancedbuttons[RWIDTH].x + 110;
	max->menu.randomadvancedbuttons[RWIDTH].text.sy = max->menu
		.randomadvancedbuttons[RWIDTH].y + 50;
}

void	ft_initbutton_rheight(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RHEIGHT] = button;
	max->menu.randomadvancedbuttons[RHEIGHT].id = RHEIGHT;
	max->menu.randomadvancedbuttons[RHEIGHT].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RHEIGHT].down = &max->menu
		.randomadvancedbuttons[RRATIOLO];
	max->menu.randomadvancedbuttons[RHEIGHT].left = &max->menu
		.randomadvancedbuttons[RWIDTH];
	max->menu.randomadvancedbuttons[RHEIGHT].state = ACTIVE;
	max->menu.randomadvancedbuttons[RHEIGHT].x = 1250;
	max->menu.randomadvancedbuttons[RHEIGHT].y = 20;
	max->menu.randomadvancedbuttons[RHEIGHT].str = S_RHEIGHT;
	max->menu.randomadvancedbuttons[RHEIGHT].val = &max->menu.rm.height;
	ft_snprintf(max->menu.randomadvancedbuttons[RHEIGHT].text.str,
		19, "%s: %i", S_RHEIGHT, max->menu
		.randomadvancedbuttons[RHEIGHT].val->value);
	max->menu.randomadvancedbuttons[RHEIGHT].text.text = max->menu
		.randomadvancedbuttons[RHEIGHT].text.str;
	max->menu.randomadvancedbuttons[RHEIGHT].text.sx = max->menu
		.randomadvancedbuttons[RHEIGHT].x + 110;
	max->menu.randomadvancedbuttons[RHEIGHT].text.sy = max->menu
		.randomadvancedbuttons[RHEIGHT].y + 50;
}

void	ft_initbutton_rratiode(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RRATIODE] = button;
	max->menu.randomadvancedbuttons[RRATIODE].id = RRATIODE;
	max->menu.randomadvancedbuttons[RRATIODE].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIODE].up = &max->menu
		.randomadvancedbuttons[RWIDTH];
	max->menu.randomadvancedbuttons[RRATIODE].down = &max->menu
		.randomadvancedbuttons[RRATIOTI];
	max->menu.randomadvancedbuttons[RRATIODE].right = &max->menu
		.randomadvancedbuttons[RRATIOLO];
	max->menu.randomadvancedbuttons[RRATIODE].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIODE].x = 700;
	max->menu.randomadvancedbuttons[RRATIODE].y = 160;
	max->menu.randomadvancedbuttons[RRATIODE].str = S_RRATIODE;
	max->menu.randomadvancedbuttons[RRATIODE].val = &max->menu.rm.ratiode;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIODE].text.str,
		19, "%s: %i", S_RRATIODE, max->menu
		.randomadvancedbuttons[RRATIODE].val->value);
	max->menu.randomadvancedbuttons[RRATIODE].text.text = max->menu
		.randomadvancedbuttons[RRATIODE].text.str;
	max->menu.randomadvancedbuttons[RRATIODE].text.sx = max->menu
		.randomadvancedbuttons[RRATIODE].x + 110;
	max->menu.randomadvancedbuttons[RRATIODE].text.sy = max->menu
		.randomadvancedbuttons[RRATIODE].y + 50;
}

void	ft_initbutton_rratiolo(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RRATIOLO] = button;
	max->menu.randomadvancedbuttons[RRATIOLO].id = RRATIOLO;
	max->menu.randomadvancedbuttons[RRATIOLO].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIOLO].up = &max->menu
		.randomadvancedbuttons[RHEIGHT];
	max->menu.randomadvancedbuttons[RRATIOLO].down = &max->menu
		.randomadvancedbuttons[RRATIOXI];
	max->menu.randomadvancedbuttons[RRATIOLO].left = &max->menu
		.randomadvancedbuttons[RRATIODE];
	max->menu.randomadvancedbuttons[RRATIOLO].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIOLO].x = 1250;
	max->menu.randomadvancedbuttons[RRATIOLO].y = 160;
	max->menu.randomadvancedbuttons[RRATIOLO].str = S_RRATIOLO;
	max->menu.randomadvancedbuttons[RRATIOLO].val = &max->menu.rm.ratiolo;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIOLO].text.str,
		19, "%s: %i", S_RRATIOLO, max->menu
		.randomadvancedbuttons[RRATIOLO].val->value);
	max->menu.randomadvancedbuttons[RRATIOLO].text.text = max->menu
		.randomadvancedbuttons[RRATIOLO].text.str;
	max->menu.randomadvancedbuttons[RRATIOLO].text.sx = max->menu
		.randomadvancedbuttons[RRATIOLO].x + 110;
	max->menu.randomadvancedbuttons[RRATIOLO].text.sy = max->menu
		.randomadvancedbuttons[RRATIOLO].y + 50;
}

void	ft_initbutton_rratioti(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RRATIOTI] = button;
	max->menu.randomadvancedbuttons[RRATIOTI].id = RRATIOTI;
	max->menu.randomadvancedbuttons[RRATIOTI].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIOTI].up = &max->menu
		.randomadvancedbuttons[RRATIODE];
	max->menu.randomadvancedbuttons[RRATIOTI].down = &max->menu
		.randomadvancedbuttons[RNOROOMS];
	max->menu.randomadvancedbuttons[RRATIOTI].right = &max->menu
		.randomadvancedbuttons[RRATIOXI];
	max->menu.randomadvancedbuttons[RRATIOTI].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIOTI].x = 700;
	max->menu.randomadvancedbuttons[RRATIOTI].y = 300;
	max->menu.randomadvancedbuttons[RRATIOTI].str = S_RRATIOTI;
	max->menu.randomadvancedbuttons[RRATIOTI].val = &max->menu.rm.ratioti;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIOTI].text.str,
		19, "%s: %i", S_RRATIOTI, max->menu
		.randomadvancedbuttons[RRATIOTI].val->value);
	max->menu.randomadvancedbuttons[RRATIOTI].text.text = max->menu
		.randomadvancedbuttons[RRATIOTI].text.str;
	max->menu.randomadvancedbuttons[RRATIOTI].text.sx = max->menu
		.randomadvancedbuttons[RRATIOTI].x + 110;
	max->menu.randomadvancedbuttons[RRATIOTI].text.sy = max->menu
		.randomadvancedbuttons[RRATIOTI].y + 50;
}
