/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:06:09 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:35:09 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	ft_selectbutton_helper_6(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_buttongroup == LOADGROUP)
	{
		if (max->menu.lf_state)
		{
			ft_choose_in_listfield(max, &max->menu.loads);
			return (r);
		}
		ft_selectnewbutton(max, &max->menu
			.loadgamebuttons[max->menu.current_button[LOADGROUP]]);
	}
	else
		r = 0;
	return (r);
}

int	ft_selectbutton_helper_5(t_max *max)
{
	int	r;

	r = 1;
	if (max->menu.current_buttongroup == SAVEGROUP)
	{
		if (max->menu.lf_state)
		{
			ft_choose_in_listfield(max, &max->menu.saves);
			return (r);
		}
		ft_selectnewbutton(max, &max->menu
			.savegamebuttons[max->menu.current_button[SAVEGROUP]]);
	}
	else if (ft_selectbutton_helper_6(max))
	{
	}
	else
		r = 0;
	return (r);
}

void	ft_draw_mainmenubuttons_2(t_max *max)
{
	if (max->menu.current_button[MAINBUTTONS] == RESUME)
	{
		ft_draw_button(&max->menu.mainbuttons[RESUME], SELECTED);
	}
	if (max->menu.current_button[MAINBUTTONS] == NEWGAME)
	{
		if (max->menu.current_buttongroup == MAINBUTTONS)
			ft_draw_button(&max->menu.mainbuttons[NEWGAME], SELECTED);
		else
			ft_draw_button(&max->menu.mainbuttons[NEWGAME], ACTIVATED);
	}
	if (max->menu.current_button[MAINBUTTONS] == SAVEGAME)
	{
		if (max->menu.current_buttongroup == MAINBUTTONS)
			ft_draw_button(&max->menu.mainbuttons[SAVEGAME], SELECTED);
		else
			ft_draw_button(&max->menu.mainbuttons[SAVEGAME], ACTIVATED);
	}
}

void	ft_draw_mainmenubuttons(t_max *max)
{
	ft_draw_mainmenubuttons_2(max);
	if (max->menu.current_button[MAINBUTTONS] == LOADGAME)
	{
		if (max->menu.current_buttongroup == MAINBUTTONS)
			ft_draw_button(&max->menu.mainbuttons[LOADGAME], SELECTED);
		else
			ft_draw_button(&max->menu.mainbuttons[LOADGAME], ACTIVATED);
	}
	if (max->menu.current_button[MAINBUTTONS] == HALLOFFAME)
	{
		if (max->menu.current_buttongroup == MAINBUTTONS)
			ft_draw_button(&max->menu.mainbuttons[HALLOFFAME], SELECTED);
		else
			ft_draw_button(&max->menu.mainbuttons[HALLOFFAME], ACTIVATED);
	}
	if (max->menu.current_button[MAINBUTTONS] == QUITGAME)
	{
		ft_draw_button(&max->menu.mainbuttons[QUITGAME], SELECTED);
	}
}

void	ft_draw_newwritingbuttons(t_max *max)
{
	if (max->menu.current_button[NEWWRITING] == NAME)
	{
		if (max->menu.newwriting == NAME)
			ft_draw_button(&max->menu.newwritingbuttons[NAME], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[NAME], SELECTED);
	}
	else if (max->menu.current_button[NEWWRITING] == COALITION)
	{
		if (max->menu.newwriting == COALITION)
			ft_draw_button(&max->menu.newwritingbuttons[COALITION], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[COALITION], SELECTED);
	}
	else if (max->menu.current_button[NEWWRITING] == CAMPUS)
	{
		if (max->menu.newwriting == CAMPUS)
			ft_draw_button(&max->menu.newwritingbuttons[CAMPUS], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[CAMPUS], SELECTED);
	}
	else if (max->menu.current_button[NEWWRITING] == NWCONFIRM)
	{
		ft_draw_button(&max->menu.newwritingbuttons[NWCONFIRM], SELECTED);
	}
}
