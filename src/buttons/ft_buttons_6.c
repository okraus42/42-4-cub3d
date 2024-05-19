/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:47:55 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 16:48:23 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initbutton_random(t_max *max)
{
	max->menu.maptypebuttons[RANDOM] = ft_initbutton_helper(max);
	max->menu.maptypebuttons[RANDOM].id = RANDOM;
	max->menu.maptypebuttons[RANDOM].group = NEWLEVEL;
	max->menu.maptypebuttons[RANDOM].up = &max->menu.maptypebuttons[CUSTOM];
	max->menu.maptypebuttons[RANDOM].state = ACTIVE;
	max->menu.maptypebuttons[RANDOM].x = 1000;
	max->menu.maptypebuttons[RANDOM].y = 600;
	max->menu.maptypebuttons[RANDOM].text.text = S_RANDOM;
	max->menu.maptypebuttons[RANDOM].text.sx = max->menu
		.maptypebuttons[RANDOM].x + 40;
	max->menu.maptypebuttons[RANDOM].text.sy = max->menu
		.maptypebuttons[RANDOM].y + 40;
}

void	ft_initbutton_chooselvl(t_max *max)
{
	max->menu.mapselectionbuttons[CHOOSELEVEL] = ft_initbutton_helper(max);
	max->menu.mapselectionbuttons[CHOOSELEVEL].id = CUSTOM;
	max->menu.mapselectionbuttons[CHOOSELEVEL].group = NEWMAP;
	max->menu.mapselectionbuttons[CHOOSELEVEL].down = &max->menu
		.mapselectionbuttons[MSPLAY];
	max->menu.mapselectionbuttons[CHOOSELEVEL].state = ACTIVE;
	max->menu.mapselectionbuttons[CHOOSELEVEL].x = 800;
	max->menu.mapselectionbuttons[CHOOSELEVEL].y = 20;
	max->menu.mapselectionbuttons[CHOOSELEVEL].text.text = S_CHOOSELEVEL;
	max->menu.mapselectionbuttons[CHOOSELEVEL].text.height = 40;
	max->menu.mapselectionbuttons[CHOOSELEVEL].text.sx = max->menu
		.mapselectionbuttons[CHOOSELEVEL].x + 40;
	max->menu.mapselectionbuttons[CHOOSELEVEL].text.sy = max->menu
		.mapselectionbuttons[CHOOSELEVEL].y + 40;
}

void	ft_initbutton_msplay(t_max *max)
{
	max->menu.mapselectionbuttons[MSPLAY] = ft_initbutton_helper(max);
	max->menu.mapselectionbuttons[MSPLAY].id = MSPLAY;
	max->menu.mapselectionbuttons[MSPLAY].group = NEWMAP;
	max->menu.mapselectionbuttons[MSPLAY].up = &max->menu
		.mapselectionbuttons[CHOOSELEVEL];
	max->menu.mapselectionbuttons[MSPLAY].state = INACTIVE;
	max->menu.mapselectionbuttons[MSPLAY].x = 1200;
	max->menu.mapselectionbuttons[MSPLAY].y = 860;
	max->menu.mapselectionbuttons[MSPLAY].text.text = S_PLAY;
	max->menu.mapselectionbuttons[MSPLAY].text.sx = max->menu
		.mapselectionbuttons[MSPLAY].x + 40;
	max->menu.mapselectionbuttons[MSPLAY].text.sy = max->menu
		.mapselectionbuttons[MSPLAY].y + 40;
}

void	ft_initbutton_rsplay(t_max *max)
{
	max->menu.randomselectionbuttons[RSPLAY] = ft_initbutton_helper(max);
	max->menu.randomselectionbuttons[RSPLAY].id = RSPLAY;
	max->menu.randomselectionbuttons[RSPLAY].group = NEWRANDOM;
	max->menu.randomselectionbuttons[RSPLAY].down = &max->menu
		.randomselectionbuttons[RSADVANCED];
	max->menu.randomselectionbuttons[RSPLAY].state = ACTIVE;
	max->menu.randomselectionbuttons[RSPLAY].x = 1000;
	max->menu.randomselectionbuttons[RSPLAY].y = 300;
	max->menu.randomselectionbuttons[RSPLAY].text.text = S_PLAY;
	max->menu.randomselectionbuttons[RSPLAY].text.sx = max->menu
		.randomselectionbuttons[RSPLAY].x + 40;
	max->menu.randomselectionbuttons[RSPLAY].text.sy = max->menu
		.randomselectionbuttons[RSPLAY].y + 40;
}

void	ft_initbutton_rsadvanced(t_max *max)
{
	max->menu.randomselectionbuttons[RSADVANCED] = ft_initbutton_helper(max);
	max->menu.randomselectionbuttons[RSADVANCED].id = RSADVANCED;
	max->menu.randomselectionbuttons[RSADVANCED].group = NEWRANDOM;
	max->menu.randomselectionbuttons[RSADVANCED].up = &max->menu
		.randomselectionbuttons[RSPLAY];
	max->menu.randomselectionbuttons[RSADVANCED].state = ACTIVE;
	max->menu.randomselectionbuttons[RSADVANCED].x = 1000;
	max->menu.randomselectionbuttons[RSADVANCED].y = 600;
	max->menu.randomselectionbuttons[RSADVANCED].text.text = S_ADVANCED;
	max->menu.randomselectionbuttons[RSADVANCED].text.sx = max->menu
		.randomselectionbuttons[RSADVANCED].x + 40;
	max->menu.randomselectionbuttons[RSADVANCED].text.sy = max->menu
		.randomselectionbuttons[RSADVANCED].y + 40;
}
