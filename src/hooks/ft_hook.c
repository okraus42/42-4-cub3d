/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:08:20 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 18:07:25 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

// void	ft_process_input_loop(t_max *max)
// {
// 	int	c;

// 	c = ' ';
// 	while (c <= 126 && !(max->kb.character))
// 	{
// 		if (max->keys[c])
// 		{
// 			max->kb.character = c;
// 			if (ft_isupper(c))
// 			{
// 				if (max->kb.shift)
// 					max->kb.character = c;
// 				else
// 					max->kb.character = 32 | c;
// 				if (max->kb.caps_lock)
// 					max->kb.character ^= 32;
// 			}
// 			else if (max->kb.shift)
// 				ft_process_input_shift(max, c);
// 			max->keys[c] = 0;
// 		}
// 		++c;
// 	}
// }

// void	ft_process_input(t_max *max)
// {
// 	max->kb.character = 0;
// 	if (max->keys[MLX_KEY_LEFT_SHIFT] | max->keys[MLX_KEY_RIGHT_SHIFT])
// 		max->kb.shift = 1;
// 	else
// 		max->kb.shift = 0;
// 	ft_process_input_loop(max);
// 	if (max->keys[ISO_KEY_BACKSLASH] && !(max->kb.character))
// 	{
// 		if (max->kb.shift)
// 			max->kb.character = '|';
// 		else
// 			max->kb.character = '\\';
// 		max->keys[ISO_KEY_BACKSLASH] = 0;
// 	}
// 	ft_process_input_numpad(max);
// }

// void	ft_menuhook(t_max *max)
// {
// 	ft_process_keylocks(max);
// 	if (max->menu.current_buttongroup == NEWWRITING)
// 		ft_process_input(max);
// 	ft_menu(max);
// }

// void	ft_gameplayhook(t_max *max)
// {
// 	ft_process_keylocks(max);
// 	ft_gameplay(max);
// }

// void	ft_gamestarthook(t_max *max)
// {
// 	ft_gamestart(max);
// }

void	ft_gamewonhook(t_max *max)
{
	ft_gamewon(max);
}

void	ft_gamelosthook(t_max *max)
{
	ft_gamelost(max);
}

void	ft_halloffamehook(t_max *max)
{
	ft_halloffame(max);
}

void	ft_hook(void *param)
{
	t_max	*max;

	max = param;
	max->newms = ft_get_time_in_ms();
	max->framems = (unsigned int)(max->newms - max->oldms);
	max->oldms = max->newms;
	if (max->game_mode == MENU)
		ft_menuhook(max);
	else if (max->game_mode == GAMESTART)
		ft_gamestarthook(max);
	else if (max->game_mode == GAMEWON)
		ft_gamewonhook(max);
	else if (max->game_mode == GAMELOST)
		ft_gamelosthook(max);
	else if (max->game_mode == GAMEPLAY)
		ft_gameplayhook(max);
	else if (max->game_mode == HOFLOOP)
		ft_halloffamehook(max);
}
