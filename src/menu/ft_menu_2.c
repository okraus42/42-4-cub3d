/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:04:56 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 11:06:47 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initrandommapvalues_2(t_randommap *rm)
{
	rm->rnorooms.value = (rm->width.value * rm->height.value / 64 + 1)
		* (rand() % ((rm->width.value + rm->height.value) / 16))
		* (rand() % 8 + 1);
	rm->rorooms.min = 1;
	rm->rorooms.max = 4096;
	rm->rorooms.value = (rm->width.value * rm->height.value / 64 + 1)
		* (rand() % ((rm->width.value + rm->height.value) / 16))
		* (rand() % 8 + 1);
	rm->rdoors.min = 0;
	rm->rdoors.max = 4096;
	rm->rdoors.value = (rand() % 8) * (rand() % 8) * (rand() % 8);
	rm->rdeadends.min = 0;
	rm->rdeadends.max = 4096;
	rm->rdeadends.value = (rand() % 12288);
	if (rm->rdeadends.value > 8192)
		rm->rdeadends.value = 0;
	if (rm->rdeadends.value > 4096)
		rm->rdeadends.value = 1;
	rm->flamingos.min = 0;
	rm->flamingos.max = 64;
	rm->flamingos.value = (rand() % 64);
}

void	ft_initrandommapvalues(t_randommap *rm)
{
	rm->seed = time(0);
	srand(rm->seed);
	rm->width.min = 5;
	rm->width.max = 120;
	rm->width.value = (rand() % 8 + 2) * (rand() % 8 + 2) + 1;
	rm->height.min = 5;
	rm->height.max = 120;
	rm->height.value = (rand() % 8 + 2) * (rand() % 8 + 2) + 1;
	rm->ratiode.min = 0;
	rm->ratiode.max = 4096;
	rm->ratiode.value = (rand() % 64) * (rand() % 8 + 1) * (rand() % 8 + 1);
	rm->ratiolo.min = 0;
	rm->ratiolo.max = 4096;
	rm->ratiolo.value = (rand() % 16) * (rand() % 8 + 1) * (rand() % 4 + 1);
	rm->ratioti.min = 0;
	rm->ratioti.max = 4096;
	rm->ratioti.value = (rand() % 8) * (rand() % 8 + 1);
	rm->ratioxi.min = 0;
	rm->ratioxi.max = 4096;
	rm->ratioxi.value = (rand() % 2) * (rand() % 8 + 1);
	rm->rnorooms.min = 0;
	rm->rnorooms.max = 4096;
	ft_initrandommapvalues_2(rm);
}

void	ft_resume(t_max *max)
{
	max->game_mode = GAMEPLAY;
	max->i.menuscreen->enabled = 0;
	max->i.textscreen->enabled = 0;
	max->i.overlay->enabled = 1;
	mlx_set_mouse_pos(max->mlx, 512, 512);
}

void	ft_newgame(t_max *max)
{
	max->game_mode = GAMESTART;
	max->menu.current_button[MAINBUTTONS] = RESUME;
	max->menu.current_buttongroup = MAINBUTTONS;
	max->game_in_progress = 0;
	max->i.menuscreen->enabled = 0;
	max->i.textscreen->enabled = 1;
	max->gamems = 0;
	if (max->difficulty == EASY)
		max->score = 1000000;
	else if (max->difficulty == MEDIUM)
		max->score = 1500000;
	else if (max->difficulty == HARD)
		max->score = 2000000;
	mlx_set_mouse_pos(max->mlx, 512, 512);
}

void	ft_initmenu(t_max *max)
{
	max->menu.current_button[MAINBUTTONS] = NEWGAME;
	max->menu.background = max->t.menubg;
	max->menu.button = max->t.button;
	max->menu.buttonplus = max->t.buttonplus;
	max->menu.textfield = max->t.textfield;
	max->menu.listfield = max->t.listfield;
	max->font.asciitest = max->t.font;
	ft_initrandommapvalues(&max->menu.rm);
	ft_initbuttons(max);
	ft_inittextfields(max);
	ft_initlistfields(max);
	max->game_type = ONEMAP;
	max->menu.newmap = -1;
	max->menu.current_button[NEWSELECTION] = ONEMAP;
	max->menu.current_button[NEWLEVEL] = CUSTOM;
	max->difficulty = -1;
}
