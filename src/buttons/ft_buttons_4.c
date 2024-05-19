/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:42:19 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 16:42:56 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initbutton_coalition(t_max *max)
{
	max->menu.newwritingbuttons[COALITION] = ft_initbutton_helper(max);
	max->menu.newwritingbuttons[COALITION].id = COALITION;
	max->menu.newwritingbuttons[COALITION].group = NEWWRITING;
	max->menu.newwritingbuttons[COALITION].up = &max->menu
		.newwritingbuttons[NAME];
	max->menu.newwritingbuttons[COALITION].down = &max->menu
		.newwritingbuttons[CAMPUS];
	max->menu.newwritingbuttons[COALITION].state = ACTIVE;
	max->menu.newwritingbuttons[COALITION].x = 600;
	max->menu.newwritingbuttons[COALITION].y = 300;
	max->menu.newwritingbuttons[COALITION].text.text = S_COALITION;
	max->menu.newwritingbuttons[COALITION].text.sx = max->menu
		.newwritingbuttons[COALITION].x + 40;
	max->menu.newwritingbuttons[COALITION].text.sy = max->menu
		.newwritingbuttons[COALITION].y + 40;
}

void	ft_initbutton_campus(t_max *max)
{
	max->menu.newwritingbuttons[CAMPUS] = ft_initbutton_helper(max);
	max->menu.newwritingbuttons[CAMPUS].id = CAMPUS;
	max->menu.newwritingbuttons[CAMPUS].group = NEWWRITING;
	max->menu.newwritingbuttons[CAMPUS].up = &max->menu
		.newwritingbuttons[COALITION];
	max->menu.newwritingbuttons[CAMPUS].down = &max->menu
		.newwritingbuttons[NWCONFIRM];
	max->menu.newwritingbuttons[CAMPUS].state = ACTIVE;
	max->menu.newwritingbuttons[CAMPUS].x = 600;
	max->menu.newwritingbuttons[CAMPUS].y = 580;
	max->menu.newwritingbuttons[CAMPUS].text.text = S_CAMPUS;
	max->menu.newwritingbuttons[CAMPUS].text.sx = max->menu
		.newwritingbuttons[CAMPUS].x + 40;
	max->menu.newwritingbuttons[CAMPUS].text.sy = max->menu
		.newwritingbuttons[CAMPUS].y + 40;
}

void	ft_initbutton_nwconfirm(t_max *max)
{
	max->menu.newwritingbuttons[NWCONFIRM] = ft_initbutton_helper(max);
	max->menu.newwritingbuttons[NWCONFIRM].id = NWCONFIRM;
	max->menu.newwritingbuttons[NWCONFIRM].group = NEWWRITING;
	max->menu.newwritingbuttons[NWCONFIRM].up = &max->menu
		.newwritingbuttons[CAMPUS];
	max->menu.newwritingbuttons[NWCONFIRM].state = ACTIVE;
	max->menu.newwritingbuttons[NWCONFIRM].x = 1200;
	max->menu.newwritingbuttons[NWCONFIRM].y = 860;
	max->menu.newwritingbuttons[NWCONFIRM].text.text = S_CONFIRM;
	max->menu.newwritingbuttons[NWCONFIRM].text.sx = max->menu
		.newwritingbuttons[NWCONFIRM].x + 40;
	max->menu.newwritingbuttons[NWCONFIRM].text.sy = max->menu
		.newwritingbuttons[NWCONFIRM].y + 40;
}

void	ft_initbutton_easylvl(t_max *max)
{
	max->menu.gamedifficultybuttons[EASY] = ft_initbutton_helper(max);
	max->menu.gamedifficultybuttons[EASY].id = EASY;
	max->menu.gamedifficultybuttons[EASY].group = NEWDIFFICULTY;
	max->menu.gamedifficultybuttons[EASY].down = &max->menu
		.gamedifficultybuttons[MEDIUM];
	max->menu.gamedifficultybuttons[EASY].state = ACTIVE;
	max->menu.gamedifficultybuttons[EASY].x = 1000;
	max->menu.gamedifficultybuttons[EASY].y = 200;
	max->menu.gamedifficultybuttons[EASY].text.text = S_EASY;
	max->menu.gamedifficultybuttons[EASY].text.sx = max->menu
		.gamedifficultybuttons[EASY].x + 40;
	max->menu.gamedifficultybuttons[EASY].text.sy = max->menu
		.gamedifficultybuttons[EASY].y + 40;
}

void	ft_initbutton_mediumlvl(t_max *max)
{
	max->menu.gamedifficultybuttons[MEDIUM] = ft_initbutton_helper(max);
	max->menu.gamedifficultybuttons[MEDIUM].id = MEDIUM;
	max->menu.gamedifficultybuttons[MEDIUM].group = NEWDIFFICULTY;
	max->menu.gamedifficultybuttons[MEDIUM].up = &max->menu
		.gamedifficultybuttons[EASY];
	max->menu.gamedifficultybuttons[MEDIUM].down = &max->menu
		.gamedifficultybuttons[HARD];
	max->menu.gamedifficultybuttons[MEDIUM].state = ACTIVE;
	max->menu.gamedifficultybuttons[MEDIUM].x = 1000;
	max->menu.gamedifficultybuttons[MEDIUM].y = 400;
	max->menu.gamedifficultybuttons[MEDIUM].text.text = S_MEDIUM;
	max->menu.gamedifficultybuttons[MEDIUM].text.sx = max->menu
		.gamedifficultybuttons[MEDIUM].x + 40;
	max->menu.gamedifficultybuttons[MEDIUM].text.sy = max->menu
		.gamedifficultybuttons[MEDIUM].y + 40;
}
