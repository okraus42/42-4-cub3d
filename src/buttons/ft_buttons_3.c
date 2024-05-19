/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:39:41 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 16:40:19 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initbutton_loadgame(t_max *max)
{
	max->menu.mainbuttons[LOADGAME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[LOADGAME].id = LOADGAME;
	max->menu.mainbuttons[LOADGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[LOADGAME].up = &max->menu.mainbuttons[SAVEGAME];
	max->menu.mainbuttons[LOADGAME].down = &max->menu.mainbuttons[SETTINGS];
	max->menu.mainbuttons[LOADGAME].y = 440;
	max->menu.mainbuttons[LOADGAME].text.text = S_LOADGAME;
	max->menu.mainbuttons[LOADGAME].text.sx = max->menu
		.mainbuttons[LOADGAME].x + 40;
	max->menu.mainbuttons[LOADGAME].text.sy = max->menu
		.mainbuttons[LOADGAME].y + 40;
}

void	ft_initbutton_settings(t_max *max)
{
	max->menu.mainbuttons[SETTINGS] = ft_initbutton_helper(max);
	max->menu.mainbuttons[SETTINGS].id = SETTINGS;
	max->menu.mainbuttons[SETTINGS].group = MAINBUTTONS;
	max->menu.mainbuttons[SETTINGS].up = &max->menu.mainbuttons[LOADGAME];
	max->menu.mainbuttons[SETTINGS].down = &max->menu.mainbuttons[HALLOFFAME];
	max->menu.mainbuttons[SETTINGS].y = 580;
	max->menu.mainbuttons[SETTINGS].text.text = S_SETTINGS;
	max->menu.mainbuttons[SETTINGS].text.sx = max->menu
		.mainbuttons[SETTINGS].x + 40;
	max->menu.mainbuttons[SETTINGS].text.sy = max->menu
		.mainbuttons[SETTINGS].y + 40;
}

void	ft_initbutton_halloffame(t_max *max)
{
	max->menu.mainbuttons[HALLOFFAME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[HALLOFFAME].id = HALLOFFAME;
	max->menu.mainbuttons[HALLOFFAME].group = MAINBUTTONS;
	max->menu.mainbuttons[HALLOFFAME].up = &max->menu.mainbuttons[SETTINGS];
	max->menu.mainbuttons[HALLOFFAME].down = &max->menu.mainbuttons[QUITGAME];
	max->menu.mainbuttons[HALLOFFAME].state = ACTIVE;
	max->menu.mainbuttons[HALLOFFAME].y = 720;
	max->menu.mainbuttons[HALLOFFAME].text.text = S_HALLOFFAME;
	max->menu.mainbuttons[HALLOFFAME].text.sx = max->menu
		.mainbuttons[HALLOFFAME].x + 40;
	max->menu.mainbuttons[HALLOFFAME].text.sy = max->menu
		.mainbuttons[HALLOFFAME].y + 40;
	max->menu.mainbuttons[HALLOFFAME].text.height = 40;
}

void	ft_initbutton_quitgame(t_max *max)
{
	max->menu.mainbuttons[QUITGAME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[QUITGAME].id = QUITGAME;
	max->menu.mainbuttons[QUITGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[QUITGAME].up = &max->menu.mainbuttons[HALLOFFAME];
	max->menu.mainbuttons[QUITGAME].state = ACTIVE;
	max->menu.mainbuttons[QUITGAME].y = 860;
	max->menu.mainbuttons[QUITGAME].text.text = S_QUITGAME;
	max->menu.mainbuttons[QUITGAME].text.sx = max->menu
		.mainbuttons[QUITGAME].x + 40;
	max->menu.mainbuttons[QUITGAME].text.sy = max->menu
		.mainbuttons[QUITGAME].y + 40;
}

void	ft_initbutton_name(t_max *max)
{
	max->menu.newwritingbuttons[NAME] = ft_initbutton_helper(max);
	max->menu.newwritingbuttons[NAME].id = NAME;
	max->menu.newwritingbuttons[NAME].group = NEWWRITING;
	max->menu.newwritingbuttons[NAME].down = &max->menu
		.newwritingbuttons[COALITION];
	max->menu.newwritingbuttons[NAME].state = ACTIVE;
	max->menu.newwritingbuttons[NAME].x = 600;
	max->menu.newwritingbuttons[NAME].y = 20;
	max->menu.newwritingbuttons[NAME].text.text = S_NAME;
	max->menu.newwritingbuttons[NAME].text.sx = max->menu
		.newwritingbuttons[NAME].x + 40;
	max->menu.newwritingbuttons[NAME].text.sy = max->menu
		.newwritingbuttons[NAME].y + 40;
}
