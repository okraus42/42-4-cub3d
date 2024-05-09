/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:05:39 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:18:13 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_draw_menu_6(t_max *max)
{
	if (max->menu.current_buttongroup == NEWDIFFICULTY)
	{
		if (max->difficulty == EASY)
			ft_draw_button(&max->menu.gamedifficultybuttons[EASY], ACTIVATED);
		else
			ft_draw_button(&max->menu.gamedifficultybuttons[EASY], ACTIVE);
		if (max->difficulty == MEDIUM)
			ft_draw_button(&max->menu.gamedifficultybuttons[MEDIUM], ACTIVATED);
		else
			ft_draw_button(&max->menu.gamedifficultybuttons[MEDIUM], ACTIVE);
		if (max->difficulty == HARD)
			ft_draw_button(&max->menu.gamedifficultybuttons[HARD], ACTIVATED);
		else
			ft_draw_button(&max->menu.gamedifficultybuttons[HARD], ACTIVE);
	}
}

void	ft_draw_menu_7(t_max *max)
{
	if (max->menu.current_buttongroup == NEWSELECTION)
	{
		ft_draw_button(&max->menu.gametypebuttons[CAMPAIGN], ACTIVE);
		ft_draw_button(&max->menu.gametypebuttons[TIMETRIAL], ACTIVE);
		ft_draw_button(&max->menu.gametypebuttons[ONEMAP], ACTIVE);
	}
	if (max->menu.current_buttongroup == NEWLEVEL)
	{
		ft_draw_button(&max->menu.maptypebuttons[CUSTOM], ACTIVE);
		ft_draw_button(&max->menu.maptypebuttons[RANDOM], ACTIVE);
	}
	if (max->menu.current_buttongroup == NEWMAP)
	{
		ft_draw_button(&max->menu.mapselectionbuttons[CHOOSELEVEL], ACTIVE);
		ft_draw_button(&max->menu.mapselectionbuttons[MSPLAY], ACTIVE);
	}
	if (max->menu.current_buttongroup == NEWMAP)
		ft_draw_listfield(&max->menu.custommap, ACTIVE);
	if (max->menu.current_buttongroup == NEWRANDOM)
	{
		ft_draw_button(&max->menu.randomselectionbuttons[RSPLAY], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RSADVANCED], ACTIVE);
	}
}

void	ft_draw_menu_8(t_max *max)
{
	if (max->menu.current_buttongroup == NEWRANDOMADVANCED)
	{
		ft_draw_button(&max->menu.randomadvancedbuttons[RWIDTH], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RHEIGHT], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RRATIODE], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOLO], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOTI], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOXI], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RNOROOMS], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[ROROOMS], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RDOORS], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RDEADENDS], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RRANDOMIZE], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RPLAY], ACTIVE);
	}
	if (max->menu.current_buttongroup == SAVEGROUP)
	{
		ft_draw_button(&max->menu.savegamebuttons[CHOOSESAVE], ACTIVE);
		ft_draw_button(&max->menu.savegamebuttons[DELETE], ACTIVE);
		ft_draw_button(&max->menu.savegamebuttons[SAVE], ACTIVE);
	}
}
