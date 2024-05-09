/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:39:32 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 12:10:39 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_menu_2(t_max *max)
{
	ft_selectbutton(max);
	ft_draw_menu(max);
	ft_draw_mainmenubuttons(max);
	if (max->menu.current_buttongroup == NEWWRITING)
	{
		ft_draw_newwritingbuttons(max);
		ft_draw_newwritingtextfields(max);
	}
	if (max->menu.current_buttongroup == NEWDIFFICULTY)
		ft_draw_gamedifficultybuttons(max);
	if (max->menu.current_buttongroup == NEWSELECTION)
		ft_draw_gametypebuttons(max);
	if (max->menu.current_buttongroup == NEWLEVEL)
		ft_draw_maptypebuttons(max);
	if (max->menu.current_buttongroup == NEWMAP)
	{
		ft_draw_newmapbuttons(max);
		ft_draw_newmaplistfields(max);
	}
	if (max->menu.current_buttongroup == NEWRANDOM)
	{
		ft_draw_newrandombuttons(max);
	}
}

void	ft_menu_3(t_max *max)
{
	if (max->menu.current_buttongroup == NEWRANDOMADVANCED)
		ft_draw_newrandomadvancedbuttons(max);
	if (max->menu.current_buttongroup == SAVEGROUP)
	{
		ft_draw_savebuttons(max);
		ft_draw_savelistfields(max);
	}
	if (max->menu.current_buttongroup == LOADGROUP)
	{
		ft_draw_loadbuttons(max);
		ft_draw_loadlistfields(max);
	}
	if (max->menu.current_buttongroup == HALLOFFAMEGROUP)
		ft_draw_halloffamebuttons(max);
	if (max->keys[MLX_KEY_BACKSPACE])
	{
		if (max->menu.current_buttongroup)
			--max->menu.current_buttongroup;
		max->keys[MLX_KEY_BACKSPACE] = 0;
	}
}

void	ft_menu_helper_5_1(t_max *max)
{
	if (max->menu.current_button[NEWLEVEL] == CUSTOM)
	{
		max->menu.current_buttongroup = NEWMAP;
		ft_bigreinitlistfield(max);
		max->menu.current_button[NEWMAP] = CUSTOM;
		max->menu.lf_state = 1;
	}
	else if (max->menu.current_button[NEWLEVEL] == RANDOM)
	{
		max->menu.current_buttongroup = NEWRANDOM;
	}
}

void	ft_menu_helper_9_1(t_max *max)
{
	if (max->menu.saves.text[max->menu
			.saves.highlight].text[0] == 'N')
	{
		ft_snprintf(max->map.file, 4095, "%s%s%03i.ft",
			max->menu.saves.dir, "save", max->menu
			.saves.highlight + max->menu.saves.topfile + 1);
	}
	else
	{
		ft_snprintf(max->map.file, 4095, "%s%s", max->menu.saves
			.dir, max->menu.saves
			.text[max->menu.saves.highlight].text);
	}
	if (ft_save(max, max->map.file))
		ft_dprintf(2, "Unable to save the game, \
			make sure the safe file has proper permissions\n");
	max->menu.current_buttongroup = MAINBUTTONS;
	ft_bigreinitlistfield(max);
}

void	ft_menu_helper_9(t_max *max)
{
	if (max->menu.current_button[SAVEGROUP] == CHOOSESAVE)
	{
		if (max->menu.lf_state)
		{
			max->menu.lf_state = 0;
			max->menu.current_button[SAVEGROUP] = SAVE;
		}
		else
		{
			max->menu.lf_state = 1;
		}
	}
	else if (max->menu.current_button[SAVEGROUP] == SAVE)
		ft_menu_helper_9_1(max);
	else if (max->menu.current_button[SAVEGROUP] == DELETE)
		ft_dprintf(2, "Functionality not implemented\n");
}
