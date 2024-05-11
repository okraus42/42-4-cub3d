/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamestart_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:27:20 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 14:29:11 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initgamestart(t_max *max)
{
	max->gamestart.background = max->t.textbg;
	max->gamestart.text = "Lorem ipsum dolor sit amet,\
	consectetur adipiscing elit, sed do eiusmod tempor incididunt\
	ut labore et dolore magna aliqua.";
	max->gamestart.font = max->font.asciitest;
	max->gamestart.image = max->i.textscreen;
	max->gamestart.c = 0XFF;
	max->gamestart.cb = 0;
	max->gamestart.sx = 200;
	max->gamestart.sy = 100;
	max->gamestart.x = 0;
	max->gamestart.y = 0;
	max->gamestart.height = 80;
	max->gamestart.highlight = -1;
	max->gamestart.i = 0;
}

void	ft_gamestart_2(t_max *max)
{
	max->settings.lightdist = max->settings.maxdist / 4;
	max->game_mode = GAMEPLAY;
	ft_init_rayangles(max);
	ft_init_orays(max);
	ft_init_fogscreen(max);
	max->i.textscreen->enabled = 0;
	max->i.maximap->enabled = 0;
	max->i.overlay->enabled = 1;
	max->game_in_progress = 1;
	max->gamestart.i = 0;
	max->levelms = 0;
	max->keys[MLX_KEY_ENTER] = 0;
}

void	ft_gamestart(t_max *max)
{
	max->gamestart.timems += max->framems;
	ft_draw_background(max);
	if (max->gamestart.timems >= 25)
	{
		max->gamestart.timems = 0;
		if (max->gamestart.i <= (int)ft_strlen(max->gamestart.text))
			++max->gamestart.i;
	}
	if (max->keys[MLX_KEY_SPACE])
	{
		max->gamestart.i = (int)ft_strlen(max->gamestart.text);
		max->keys[MLX_KEY_SPACE] = 0;
	}
	ft_draw_gametext(&max->gamestart);
	if (max->keys[MLX_KEY_ENTER])
		ft_gamestart_2(max);
}

void	ft_initgamewon(t_max *max)
{
	max->gamewon.background = max->gamestart.background;
	max->gamewon.text = max->gamewon.stats;
	ft_sprintf(max->gamewon.stats, "You won!\nCongratulations!\n");
	max->gamewon.font = max->font.asciitest;
	max->gamewon.image = max->i.textscreen;
	max->gamewon.c = 0XFF;
	max->gamewon.cb = 0;
	max->gamewon.sx = 200;
	max->gamewon.sy = 100;
	max->gamewon.x = 0;
	max->gamewon.y = 0;
	max->gamewon.height = 80;
	max->gamewon.highlight = -1;
	max->gamewon.i = 0;
}

void	ft_gamewon_init(t_max *max)
{
	max->gamewon.timems += max->framems;
	ft_draw_background(max);
	if (max->gamewon.timems >= 25)
	{
		max->gamewon.timems = 0;
		if (max->gamewon.i <= (int)ft_strlen(max->gamewon.text))
			++max->gamewon.i;
	}
	if (max->keys[MLX_KEY_SPACE])
	{
		max->gamewon.i = (int)ft_strlen(max->gamewon.text);
		max->keys[MLX_KEY_SPACE] = 0;
	}
}
