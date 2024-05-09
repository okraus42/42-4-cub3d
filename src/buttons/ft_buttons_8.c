/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons_8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:53:50 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 16:54:31 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initbutton_rratioxi(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RRATIOXI] = button;
	max->menu.randomadvancedbuttons[RRATIOXI].id = RRATIOXI;
	max->menu.randomadvancedbuttons[RRATIOXI].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIOXI].up = &max->menu
		.randomadvancedbuttons[RRATIOLO];
	max->menu.randomadvancedbuttons[RRATIOXI].down = &max->menu
		.randomadvancedbuttons[ROROOMS];
	max->menu.randomadvancedbuttons[RRATIOXI].left = &max->menu
		.randomadvancedbuttons[RRATIOTI];
	max->menu.randomadvancedbuttons[RRATIOXI].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIOXI].x = 1250;
	max->menu.randomadvancedbuttons[RRATIOXI].y = 300;
	max->menu.randomadvancedbuttons[RRATIOXI].str = S_RRATIOXI;
	max->menu.randomadvancedbuttons[RRATIOXI].val = &max->menu.rm.ratioxi;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIOXI].text.str,
		19, "%s: %i", S_RRATIOXI, max->menu
		.randomadvancedbuttons[RRATIOXI].val->value);
	max->menu.randomadvancedbuttons[RRATIOXI].text.text = max->menu
		.randomadvancedbuttons[RRATIOXI].text.str;
	max->menu.randomadvancedbuttons[RRATIOXI].text.sx = max->menu
		.randomadvancedbuttons[RRATIOXI].x + 110;
	max->menu.randomadvancedbuttons[RRATIOXI].text.sy = max->menu
		.randomadvancedbuttons[RRATIOXI].y + 50;
}

void	ft_initbutton_rnorooms(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RNOROOMS] = button;
	max->menu.randomadvancedbuttons[RNOROOMS].id = RNOROOMS;
	max->menu.randomadvancedbuttons[RNOROOMS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RNOROOMS].up = &max->menu
		.randomadvancedbuttons[RRATIOTI];
	max->menu.randomadvancedbuttons[RNOROOMS].down = &max->menu
		.randomadvancedbuttons[RDOORS];
	max->menu.randomadvancedbuttons[RNOROOMS].right = &max->menu
		.randomadvancedbuttons[ROROOMS];
	max->menu.randomadvancedbuttons[RNOROOMS].state = ACTIVE;
	max->menu.randomadvancedbuttons[RNOROOMS].x = 700;
	max->menu.randomadvancedbuttons[RNOROOMS].y = 440;
	max->menu.randomadvancedbuttons[RNOROOMS].str = S_RNOROOMS;
	max->menu.randomadvancedbuttons[RNOROOMS].val = &max->menu.rm.rnorooms;
	ft_snprintf(max->menu.randomadvancedbuttons[RNOROOMS].text.str,
		19, "%s: %i", S_RNOROOMS, max->menu
		.randomadvancedbuttons[RNOROOMS].val->value);
	max->menu.randomadvancedbuttons[RNOROOMS].text.text = max->menu
		.randomadvancedbuttons[RNOROOMS].text.str;
	max->menu.randomadvancedbuttons[RNOROOMS].text.sx = max->menu
		.randomadvancedbuttons[RNOROOMS].x + 110;
	max->menu.randomadvancedbuttons[RNOROOMS].text.sy = max->menu
		.randomadvancedbuttons[RNOROOMS].y + 50;
}

void	ft_initbutton_rorooms(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[ROROOMS] = button;
	max->menu.randomadvancedbuttons[ROROOMS].id = ROROOMS;
	max->menu.randomadvancedbuttons[ROROOMS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[ROROOMS].up = &max->menu
		.randomadvancedbuttons[RRATIOXI];
	max->menu.randomadvancedbuttons[ROROOMS].down = &max->menu
		.randomadvancedbuttons[RDEADENDS];
	max->menu.randomadvancedbuttons[ROROOMS].left = &max->menu
		.randomadvancedbuttons[RNOROOMS];
	max->menu.randomadvancedbuttons[ROROOMS].state = ACTIVE;
	max->menu.randomadvancedbuttons[ROROOMS].x = 1250;
	max->menu.randomadvancedbuttons[ROROOMS].y = 440;
	max->menu.randomadvancedbuttons[ROROOMS].str = S_ROROOMS;
	max->menu.randomadvancedbuttons[ROROOMS].val = &max->menu.rm.rorooms;
	ft_snprintf(max->menu.randomadvancedbuttons[ROROOMS].text.str,
		19, "%s: %i", S_ROROOMS, max->menu
		.randomadvancedbuttons[ROROOMS].val->value);
	max->menu.randomadvancedbuttons[ROROOMS].text.text = max->menu
		.randomadvancedbuttons[ROROOMS].text.str;
	max->menu.randomadvancedbuttons[ROROOMS].text.sx = max->menu
		.randomadvancedbuttons[ROROOMS].x + 110;
	max->menu.randomadvancedbuttons[ROROOMS].text.sy = max->menu
		.randomadvancedbuttons[ROROOMS].y + 50;
}

void	ft_initbutton_rdoors(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RDOORS] = button;
	max->menu.randomadvancedbuttons[RDOORS].id = RDOORS;
	max->menu.randomadvancedbuttons[RDOORS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RDOORS].up = &max->menu
		.randomadvancedbuttons[RNOROOMS];
	max->menu.randomadvancedbuttons[RDOORS].down = &max->menu
		.randomadvancedbuttons[RPLAY];
	max->menu.randomadvancedbuttons[RDOORS].right = &max->menu
		.randomadvancedbuttons[RDEADENDS];
	max->menu.randomadvancedbuttons[RDOORS].state = ACTIVE;
	max->menu.randomadvancedbuttons[RDOORS].x = 700;
	max->menu.randomadvancedbuttons[RDOORS].y = 580;
	max->menu.randomadvancedbuttons[RDOORS].str = S_RDOORS;
	max->menu.randomadvancedbuttons[RDOORS].val = &max->menu.rm.rdoors;
	ft_snprintf(max->menu.randomadvancedbuttons[RDOORS].text.str,
		19, "%s: %i", S_RDOORS, max->menu
		.randomadvancedbuttons[RDOORS].val->value);
	max->menu.randomadvancedbuttons[RDOORS].text.text = max->menu
		.randomadvancedbuttons[RDOORS].text.str;
	max->menu.randomadvancedbuttons[RDOORS].text.sx = max->menu
		.randomadvancedbuttons[RDOORS].x + 110;
	max->menu.randomadvancedbuttons[RDOORS].text.sy = max->menu
		.randomadvancedbuttons[RDOORS].y + 50;
}

void	ft_initbutton_rdeadends(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RDEADENDS] = button;
	max->menu.randomadvancedbuttons[RDEADENDS].id = RDEADENDS;
	max->menu.randomadvancedbuttons[RDEADENDS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RDEADENDS].up = &max->menu
		.randomadvancedbuttons[ROROOMS];
	max->menu.randomadvancedbuttons[RDEADENDS].down = &max->menu
		.randomadvancedbuttons[RPLAY];
	max->menu.randomadvancedbuttons[RDEADENDS].left = &max->menu
		.randomadvancedbuttons[RDOORS];
	max->menu.randomadvancedbuttons[RDEADENDS].state = ACTIVE;
	max->menu.randomadvancedbuttons[RDEADENDS].x = 1250;
	max->menu.randomadvancedbuttons[RDEADENDS].y = 580;
	max->menu.randomadvancedbuttons[RDEADENDS].str = S_RDEADENDS;
	max->menu.randomadvancedbuttons[RDEADENDS].val = &max->menu.rm.rdeadends;
	ft_snprintf(max->menu.randomadvancedbuttons[RDEADENDS].text.str,
		19, "%s: %i", S_RDEADENDS, max->menu
		.randomadvancedbuttons[RDEADENDS].val->value);
	max->menu.randomadvancedbuttons[RDEADENDS].text.text = max->menu
		.randomadvancedbuttons[RDEADENDS].text.str;
	max->menu.randomadvancedbuttons[RDEADENDS].text.sx = max->menu
		.randomadvancedbuttons[RDEADENDS].x + 110;
	max->menu.randomadvancedbuttons[RDEADENDS].text.sy = max->menu
		.randomadvancedbuttons[RDEADENDS].y + 50;
}
