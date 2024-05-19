/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:34:04 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 16:35:04 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

t_text	ft_inittext_helper(t_max *max)
{
	t_text		text;

	ft_bzero(&text, sizeof(text));
	text.font = max->font.asciitest;
	text.image = max->i.menuscreen;
	text.text = "VOID";
	text.c = 0XFF;
	text.cb = 0;
	text.sx = 0;
	text.sy = 0;
	text.x = 0;
	text.y = 0;
	text.height = 60;
	text.highlight = -1;
	text.i = 0;
	text.offset = 0;
	return (text);
}

t_button	ft_initbutton_helper(t_max *max)
{
	t_button	button;

	ft_bzero(&button, sizeof(button));
	button.button = max->menu.button;
	button.image = max->i.menuscreen;
	button.text = ft_inittext_helper(max);
	button.c = C_INACTIVE;
	button.x = 200;
	button.y = 0;
	button.w = 350;
	button.h = 150;
	button.state = INACTIVE;
	return (button);
}

void	ft_initbutton_resume(t_max *max)
{
	max->menu.mainbuttons[RESUME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[RESUME].id = RESUME;
	max->menu.mainbuttons[RESUME].group = MAINBUTTONS;
	max->menu.mainbuttons[RESUME].down = &max->menu.mainbuttons[NEWGAME];
	max->menu.mainbuttons[RESUME].y = 20;
	max->menu.mainbuttons[RESUME].text.text = S_RESUME;
	max->menu.mainbuttons[RESUME].text.sx = max->menu
		.mainbuttons[RESUME].x + 40;
	max->menu.mainbuttons[RESUME].text.sy = max->menu
		.mainbuttons[RESUME].y + 40;
}

void	ft_initbutton_newgame(t_max *max)
{
	max->menu.mainbuttons[NEWGAME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[NEWGAME].id = NEWGAME;
	max->menu.mainbuttons[NEWGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[NEWGAME].up = &max->menu.mainbuttons[RESUME];
	max->menu.mainbuttons[NEWGAME].down = &max->menu.mainbuttons[SAVEGAME];
	max->menu.mainbuttons[NEWGAME].state = SELECTED;
	max->menu.mainbuttons[NEWGAME].y = 160;
	max->menu.mainbuttons[NEWGAME].text.text = S_NEWGAME;
	max->menu.mainbuttons[NEWGAME].text.sx = max->menu
		.mainbuttons[NEWGAME].x + 40;
	max->menu.mainbuttons[NEWGAME].text.sy = max->menu
		.mainbuttons[NEWGAME].y + 40;
}

void	ft_initbutton_savegame(t_max *max)
{
	max->menu.mainbuttons[SAVEGAME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[SAVEGAME].id = SAVEGAME;
	max->menu.mainbuttons[SAVEGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[SAVEGAME].up = &max->menu.mainbuttons[NEWGAME];
	max->menu.mainbuttons[SAVEGAME].down = &max->menu.mainbuttons[LOADGAME];
	max->menu.mainbuttons[SAVEGAME].y = 300;
	max->menu.mainbuttons[SAVEGAME].text.text = S_SAVEGAME;
	max->menu.mainbuttons[SAVEGAME].text.sx = max->menu
		.mainbuttons[SAVEGAME].x + 40;
	max->menu.mainbuttons[SAVEGAME].text.sy = max->menu
		.mainbuttons[SAVEGAME].y + 40;
}
