/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamestart.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:57:06 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 14:32:12 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

// void	ft_gamewon_timetrial(t_max *max)
// {
// 	++max->level;
// 	ft_inittimetrialmap(&max->menu.rm, max->level);
// 	ft_snprintf(max->map.file, 4095, "RANDOM");
// 	if (ft_process_random(max))
// 	{
// 		printf("gamestart loop starting...\n");
// 		max->game_mode = GAMESTART;
// 		max->menu.current_button[MAINBUTTONS] = RESUME;
// 		max->menu.current_buttongroup = MAINBUTTONS;
// 		max->game_in_progress = 0;
// 		max->i.menuscreen->enabled = 0;
// 		max->i.textscreen->enabled = 1;
// 	}
// 	else
// 		ft_dprintf(2, "Invalid map\n");
// }

void	ft_gamewon_campaign(t_max *max)
{
	++max->level;
	if (max->level > 4)
	{
		max->game_mode = MENU;
		max->i.textscreen->enabled = 0;
		max->game_in_progress = 0;
		max->gamewon.i = 0;
		max->gamems = 0;
	}
	ft_sprintf(max->campaignmap, "./campaign/map%i.cub", max->level);
	ft_snprintf(max->map.file, 4095, max->campaignmap);
	if (ft_process_file(max))
	{
		printf("gamestart loop starting...\n");
		max->game_mode = GAMESTART;
		max->menu.current_button[MAINBUTTONS] = RESUME;
		max->menu.current_buttongroup = MAINBUTTONS;
		max->game_in_progress = 0;
		max->i.menuscreen->enabled = 0;
		max->i.textscreen->enabled = 1;
	}
	else
		ft_dprintf(2, "Invalid map\n");
}

void	ft_gamewon(t_max *max)
{
	ft_gamewon_init(max);
	ft_draw_gametext(&max->gamewon);
	if (max->keys[MLX_KEY_ENTER])
	{
		max->keys[MLX_KEY_ENTER] = 0;
		max->gamewon.timems = 0;
		if (max->game_type == ONEMAP)
		{
			max->game_mode = MENU;
			max->i.textscreen->enabled = 0;
			max->game_in_progress = 0;
			max->gamewon.i = 0;
		}
		if (max->game_type == TIMETRIAL)
			ft_gamewon_timetrial(max);
		if (max->game_type == CAMPAIGN)
			ft_gamewon_campaign(max);
	}
}

void	ft_initgamelost(t_max *max)
{
	max->gamelost.background = max->gamestart.background;
	max->gamelost.text = max->gamelost.stats;
	ft_sprintf(max->gamelost.stats, "You lost:(\n");
	max->gamelost.font = max->font.asciitest;
	max->gamelost.image = max->i.textscreen;
	max->gamelost.c = 0XFF;
	max->gamelost.cb = 0;
	max->gamelost.sx = 200;
	max->gamelost.sy = 100;
	max->gamelost.x = 0;
	max->gamelost.y = 0;
	max->gamelost.height = 80;
	max->gamelost.highlight = -1;
	max->gamelost.i = 0;
}

void	ft_gamelost_init(t_max *max)
{
	max->gamelost.timems += max->framems;
	ft_draw_background(max);
	if (max->gamelost.timems >= 25)
	{
		max->gamelost.timems = 0;
		if (max->gamelost.i <= (int)ft_strlen(max->gamelost.text))
			++max->gamelost.i;
	}
	if (max->keys[MLX_KEY_SPACE])
	{
		max->gamelost.i = (int)ft_strlen(max->gamelost.text);
		max->keys[MLX_KEY_SPACE] = 0;
	}
}

void	ft_gamelost(t_max *max)
{
	ft_gamelost_init(max);
	ft_draw_gametext(&max->gamelost);
	if (max->keys[MLX_KEY_ENTER])
	{
		max->keys[MLX_KEY_ENTER] = 0;
		max->gamelost.timems = 0;
		max->gamelost.i = 0;
		max->game_in_progress = 0;
		max->gamems = 0;
		max->i.textscreen->enabled = 0;
		max->game_mode = MENU;
		if (max->game_type == TIMETRIAL && ft_writescore(max))
			ft_printf("Warning: Could not write the final score\n");
	}
}
