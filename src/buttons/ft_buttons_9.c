/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons_9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:57:50 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 16:58:35 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initbutton_rrandomize(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RRANDOMIZE] = button;
	max->menu.randomadvancedbuttons[RRANDOMIZE].id = RRANDOMIZE;
	max->menu.randomadvancedbuttons[RRANDOMIZE].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRANDOMIZE].up = &max->menu
		.randomadvancedbuttons[RDOORS];
	max->menu.randomadvancedbuttons[RRANDOMIZE].right = &max->menu
		.randomadvancedbuttons[RPLAY];
	max->menu.randomadvancedbuttons[RRANDOMIZE].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRANDOMIZE].x = 850;
	max->menu.randomadvancedbuttons[RRANDOMIZE].y = 860;
	max->menu.randomadvancedbuttons[RRANDOMIZE].text.text = S_RANDOMIZE;
	max->menu.randomadvancedbuttons[RRANDOMIZE].text.sx = max->menu
		.randomadvancedbuttons[RRANDOMIZE].x + 40;
	max->menu.randomadvancedbuttons[RRANDOMIZE].text.sy = max->menu
		.randomadvancedbuttons[RRANDOMIZE].y + 40;
}

void	ft_initbutton_rplay(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RPLAY] = button;
	max->menu.randomadvancedbuttons[RPLAY].id = RPLAY;
	max->menu.randomadvancedbuttons[RPLAY].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RPLAY].up = &max->menu
		.randomadvancedbuttons[RDEADENDS];
	max->menu.randomadvancedbuttons[RPLAY].left = &max->menu
		.randomadvancedbuttons[RRANDOMIZE];
	max->menu.randomadvancedbuttons[RPLAY].state = ACTIVE;
	max->menu.randomadvancedbuttons[RPLAY].x = 1250;
	max->menu.randomadvancedbuttons[RPLAY].y = 860;
	max->menu.randomadvancedbuttons[RPLAY].text.text = S_PLAY;
	max->menu.randomadvancedbuttons[RPLAY].text.sx = max->menu
		.randomadvancedbuttons[RPLAY].x + 40;
	max->menu.randomadvancedbuttons[RPLAY].text.sy = max->menu
		.randomadvancedbuttons[RPLAY].y + 40;
}

void	ft_initbutton_choosesave(t_max *max, t_button button)
{
	max->menu.savegamebuttons[CHOOSESAVE] = button;
	max->menu.savegamebuttons[CHOOSESAVE].id = CHOOSESAVE;
	max->menu.savegamebuttons[CHOOSESAVE].group = SAVEGROUP;
	max->menu.savegamebuttons[CHOOSESAVE].down = &max->menu
		.savegamebuttons[SAVE];
	max->menu.savegamebuttons[CHOOSESAVE].state = ACTIVE;
	max->menu.savegamebuttons[CHOOSESAVE].x = 800;
	max->menu.savegamebuttons[CHOOSESAVE].y = 20;
	max->menu.savegamebuttons[CHOOSESAVE].text.text = S_CHOOSESAVE;
	max->menu.savegamebuttons[CHOOSESAVE].text.height = 40;
	max->menu.savegamebuttons[CHOOSESAVE].text.sx = max->menu
		.savegamebuttons[CHOOSESAVE].x + 40;
	max->menu.savegamebuttons[CHOOSESAVE].text.sy = max->menu
		.savegamebuttons[CHOOSESAVE].y + 40;
}

void	ft_initbutton_delete(t_max *max, t_button button)
{
	max->menu.savegamebuttons[DELETE] = button;
	max->menu.savegamebuttons[DELETE].id = DELETE;
	max->menu.savegamebuttons[DELETE].group = SAVEGROUP;
	max->menu.savegamebuttons[DELETE].up = &max->menu
		.savegamebuttons[CHOOSELEVEL];
	max->menu.savegamebuttons[DELETE].right = &max->menu
		.savegamebuttons[SAVE];
	max->menu.savegamebuttons[DELETE].state = ACTIVE;
	max->menu.savegamebuttons[DELETE].x = 800;
	max->menu.savegamebuttons[DELETE].y = 860;
	max->menu.savegamebuttons[DELETE].text.text = S_DELETE;
	max->menu.savegamebuttons[DELETE].text.sx = max->menu
		.savegamebuttons[DELETE].x + 40;
	max->menu.savegamebuttons[DELETE].text.sy = max->menu
		.savegamebuttons[DELETE].y + 40;
}

void	ft_initbutton_save(t_max *max, t_button button)
{
	max->menu.savegamebuttons[SAVE] = button;
	max->menu.savegamebuttons[SAVE].id = SAVE;
	max->menu.savegamebuttons[SAVE].group = SAVEGROUP;
	max->menu.savegamebuttons[SAVE].up = &max->menu
		.savegamebuttons[CHOOSELEVEL];
	max->menu.savegamebuttons[SAVE].left = &max->menu.savegamebuttons[DELETE];
	max->menu.savegamebuttons[SAVE].state = ACTIVE;
	max->menu.savegamebuttons[SAVE].x = 1200;
	max->menu.savegamebuttons[SAVE].y = 860;
	max->menu.savegamebuttons[SAVE].text.text = S_SAVE;
	max->menu.savegamebuttons[SAVE].text.sx = max->menu
		.savegamebuttons[SAVE].x + 40;
	max->menu.savegamebuttons[SAVE].text.sy = max->menu
		.savegamebuttons[SAVE].y + 40;
}
