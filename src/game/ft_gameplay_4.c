/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameplay_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:30 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/10 13:25:37 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_game_end(t_max *max)
{
	max->game_in_progress = 0;
	max->menu.current_button[0] = NEWGAME;
	max->menu.current_buttongroup = MAINBUTTONS;
	max->i.menuscreen->enabled = 1;
	max->i.textscreen->enabled = 1;
	max->i.overlay->enabled = 0;
	max->gamems += max->levelms;
	if (!max->bonus)
		mlx_close_window(max->mlx);
}

void	ft_game_win_print(t_max *max)
{
	ft_sprintf(max->gamewon.stats, "              YOU WON!\n\
		\nNAME:         COALITION:    CAMPUS:\n%-10.10s    %-10.10s    %-10.10s\n\
		\nTime: %is\nTotal time: %is\nTime limit: %is",
		max->name, max->coalition, max->campus, max->levelms / 1000,
		max->gamems / 1000, max->limitms / 1000);
}

void	ft_game_win(t_max *max)
{
	if (max->reachedexit)
	{
		max->reachedexit = 0;
		if (max->difficulty == EASY)
			max->score += 500000;
		if (max->difficulty == MEDIUM)
			max->score += 1000000;
		if (max->difficulty == HARD)
			max->score += 2000000;
		max->game_mode = GAMEWON;
		ft_game_end(max);
		if (max->game_type == TIMETRIAL)
			max->timetriallimitms += 60000;
		if (max->game_type == TIMETRIAL)
			ft_sprintf(max->gamewon.stats, "              YOU WON!\n\
				\nNAME:         COALITION:    CAMPUS:\n%-10.10s    %-10.10s    %-10.10s\n\
				\nTime: %is\nTotal time: %is\nTime limit: %is", max->name,
				max->coalition, max->campus,
				max->levelms / 1000, max->gamems / 1000,
				max->timetriallimitms / 1000);
		else if (max->game_type == ONEMAP)
			ft_game_win_print(max);
		else if (max->game_type == CAMPAIGN)
			ft_game_win_print(max);
		return ;
	}
}

void	ft_game_lose_print(t_max *max)
{
	max->game_mode = GAMELOST;
	ft_game_end(max);
	ft_sprintf(max->gamelost.stats, "              YOU LOST!\n\
		\nNAME:         COALITION:    CAMPUS:\n%-10.10s    %-10.10s    %-10.10s\n\
		\nTime: %is\nTotal time: %is\nTime limit: %is", max->name,
		max->coalition, max->campus, max->levelms / 1000,
		max->gamems / 1000, max->limitms / 1000);
}

void	ft_game_lose(t_max *max)
{
	if (!max->game_in_progress)
		return ;
	if (max->game_type == TIMETRIAL)
	{
		if (max->gamems + max->levelms > max->timetriallimitms)
		{
			max->game_mode = GAMELOST;
			ft_game_end(max);
			ft_sprintf(max->gamelost.stats, "              YOU LOST!\n\
				\nNAME:         COALITION:    CAMPUS:\n%-10.10s    %-10.10s    %-10.10s\n\
				\nTime: %is\nTotal time: %is\nTime limit: %is",
				max->name, max->coalition, max->campus, max->levelms / 1000,
				max->gamems / 1000, max->timetriallimitms / 1000);
		}
	}
	else if (max->game_type == ONEMAP)
	{
		if (max->levelms > max->limitms)
			ft_game_lose_print(max);
	}
	else if (max->game_type == CAMPAIGN)
	{
		if (max->levelms > max->limitms)
			ft_game_lose_print(max);
	}
}
