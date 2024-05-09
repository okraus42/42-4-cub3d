/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:35:29 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:38:24 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_draw_newwritingtextfields(t_max *max)
{
	if (max->menu.current_button[NEWWRITING] == NAME)
	{
		if (max->menu.newwriting == NAME)
			ft_draw_textfield(&max->menu.newwritingfields[NAME], ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[NAME], SELECTED);
	}
	else if (max->menu.current_button[NEWWRITING] == COALITION)
	{
		if (max->menu.newwriting == COALITION)
			ft_draw_textfield(&max->menu
				.newwritingfields[COALITION], ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[COALITION], SELECTED);
	}
	else if (max->menu.current_button[NEWWRITING] == CAMPUS)
	{
		if (max->menu.newwriting == CAMPUS)
			ft_draw_textfield(&max->menu.newwritingfields[CAMPUS], ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[CAMPUS], SELECTED);
	}
}

void	ft_draw_gamedifficultybuttons(t_max *max)
{
	if (max->menu.current_button[NEWDIFFICULTY] == EASY)
	{
		ft_draw_button(&max->menu.gamedifficultybuttons[EASY], SELECTED);
	}
	else if (max->menu.current_button[NEWDIFFICULTY] == MEDIUM)
	{
		ft_draw_button(&max->menu.gamedifficultybuttons[MEDIUM], SELECTED);
	}
	else if (max->menu.current_button[NEWDIFFICULTY] == HARD)
	{
		ft_draw_button(&max->menu.gamedifficultybuttons[HARD], SELECTED);
	}
}

void	ft_draw_gametypebuttons(t_max *max)
{
	if (max->menu.current_button[NEWSELECTION] == CAMPAIGN)
	{
		ft_draw_button(&max->menu.gametypebuttons[CAMPAIGN], SELECTED);
	}
	else if (max->menu.current_button[NEWSELECTION] == TIMETRIAL)
	{
		ft_draw_button(&max->menu.gametypebuttons[TIMETRIAL], SELECTED);
	}
	else if (max->menu.current_button[NEWSELECTION] == ONEMAP)
	{
		ft_draw_button(&max->menu.gametypebuttons[ONEMAP], SELECTED);
	}
}

void	ft_draw_maptypebuttons(t_max *max)
{
	if (max->menu.current_button[NEWLEVEL] == CUSTOM)
	{
		ft_draw_button(&max->menu.maptypebuttons[CUSTOM], SELECTED);
	}
	else if (max->menu.current_button[NEWLEVEL] == RANDOM)
	{
		ft_draw_button(&max->menu.maptypebuttons[RANDOM], SELECTED);
	}
}

void	ft_draw_newmapbuttons(t_max *max)
{
	if (max->menu.current_button[NEWMAP] == CHOOSELEVEL)
	{
		if (max->menu.lf_state)
			ft_draw_button(&max->menu
				.mapselectionbuttons[CHOOSELEVEL], ACTIVATED);
		else
			ft_draw_button(&max->menu
				.mapselectionbuttons[CHOOSELEVEL], SELECTED);
	}
	else if (max->menu.current_button[NEWMAP] == MSPLAY)
	{
		ft_draw_button(&max->menu.mapselectionbuttons[MSPLAY], SELECTED);
	}
}
