/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:44:57 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 16:45:40 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initbutton_hardlvl(t_max *max)
{
	max->menu.gamedifficultybuttons[HARD] = ft_initbutton_helper(max);
	max->menu.gamedifficultybuttons[HARD].id = HARD;
	max->menu.gamedifficultybuttons[HARD].group = NEWDIFFICULTY;
	max->menu.gamedifficultybuttons[HARD].up = &max->menu
		.gamedifficultybuttons[MEDIUM];
	max->menu.gamedifficultybuttons[HARD].state = ACTIVE;
	max->menu.gamedifficultybuttons[HARD].x = 1000;
	max->menu.gamedifficultybuttons[HARD].y = 600;
	max->menu.gamedifficultybuttons[HARD].text.text = S_HARD;
	max->menu.gamedifficultybuttons[HARD].text.sx = max->menu
		.gamedifficultybuttons[HARD].x + 40;
	max->menu.gamedifficultybuttons[HARD].text.sy = max->menu
		.gamedifficultybuttons[HARD].y + 40;
}

void	ft_initbutton_campaign(t_max *max)
{
	max->menu.gametypebuttons[CAMPAIGN] = ft_initbutton_helper(max);
	max->menu.gametypebuttons[CAMPAIGN].id = CAMPAIGN;
	max->menu.gametypebuttons[CAMPAIGN].group = NEWSELECTION;
	max->menu.gametypebuttons[CAMPAIGN].down = &max->menu
		.gametypebuttons[TIMETRIAL];
	max->menu.gametypebuttons[CAMPAIGN].state = ACTIVE;
	max->menu.gametypebuttons[CAMPAIGN].x = 1000;
	max->menu.gametypebuttons[CAMPAIGN].y = 200;
	max->menu.gametypebuttons[CAMPAIGN].text.text = S_CAMPAIGN;
	max->menu.gametypebuttons[CAMPAIGN].text.sx = max->menu
		.gametypebuttons[CAMPAIGN].x + 40;
	max->menu.gametypebuttons[CAMPAIGN].text.sy = max->menu
		.gametypebuttons[CAMPAIGN].y + 40;
}

void	ft_initbutton_timetrial(t_max *max)
{
	max->menu.gametypebuttons[TIMETRIAL] = ft_initbutton_helper(max);
	max->menu.gametypebuttons[TIMETRIAL].id = TIMETRIAL;
	max->menu.gametypebuttons[TIMETRIAL].group = NEWSELECTION;
	max->menu.gametypebuttons[TIMETRIAL].up = &max->menu
		.gametypebuttons[CAMPAIGN];
	max->menu.gametypebuttons[TIMETRIAL].down = &max->menu
		.gametypebuttons[ONEMAP];
	max->menu.gametypebuttons[TIMETRIAL].state = ACTIVE;
	max->menu.gametypebuttons[TIMETRIAL].x = 1000;
	max->menu.gametypebuttons[TIMETRIAL].y = 400;
	max->menu.gametypebuttons[TIMETRIAL].text.text = S_TIMETRIAL;
	max->menu.gametypebuttons[TIMETRIAL].text.sx = max->menu
		.gametypebuttons[TIMETRIAL].x + 40;
	max->menu.gametypebuttons[TIMETRIAL].text.sy = max->menu
		.gametypebuttons[TIMETRIAL].y + 40;
}

void	ft_initbutton_onemap(t_max *max)
{
	max->menu.gametypebuttons[ONEMAP] = ft_initbutton_helper(max);
	max->menu.gametypebuttons[ONEMAP].id = ONEMAP;
	max->menu.gametypebuttons[ONEMAP].group = NEWSELECTION;
	max->menu.gametypebuttons[ONEMAP].up = &max->menu
		.gametypebuttons[TIMETRIAL];
	max->menu.gametypebuttons[ONEMAP].state = ACTIVE;
	max->menu.gametypebuttons[ONEMAP].x = 1000;
	max->menu.gametypebuttons[ONEMAP].y = 600;
	max->menu.gametypebuttons[ONEMAP].text.text = S_ONEMAP;
	max->menu.gametypebuttons[ONEMAP].text.sx = max->menu
		.gametypebuttons[ONEMAP].x + 40;
	max->menu.gametypebuttons[ONEMAP].text.sy = max->menu
		.gametypebuttons[ONEMAP].y + 40;
}

void	ft_initbutton_custom(t_max *max)
{
	max->menu.maptypebuttons[CUSTOM] = ft_initbutton_helper(max);
	max->menu.maptypebuttons[CUSTOM].id = CUSTOM;
	max->menu.maptypebuttons[CUSTOM].group = NEWLEVEL;
	max->menu.maptypebuttons[CUSTOM].down = &max->menu.maptypebuttons[RANDOM];
	max->menu.maptypebuttons[CUSTOM].state = ACTIVE;
	max->menu.maptypebuttons[CUSTOM].x = 1000;
	max->menu.maptypebuttons[CUSTOM].y = 300;
	max->menu.maptypebuttons[CUSTOM].text.text = S_CUSTOM;
	max->menu.maptypebuttons[CUSTOM].text.sx = max->menu
		.maptypebuttons[CUSTOM].x + 40;
	max->menu.maptypebuttons[CUSTOM].text.sy = max->menu
		.maptypebuttons[CUSTOM].y + 40;
}
