/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:08:20 by okraus            #+#    #+#             */
/*   Updated: 2024/03/31 10:53:36 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"




void	ft_menuhook(t_max *max)
{
	
	// if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
	// {
	// 	max->game_mode = GAMEPLAY;
	// 	max->menuscreen->enabled = 0;
	// 	// ft_printf("You have quit the game by pressing ESC.\n");
	// 	// mlx_close_window(max->mlx);
	// }
	ft_menu(max);
}

void	ft_gameplayhook(t_max *max)
{
	ft_gameplay(max);
}

void	ft_gamestarthook(t_max *max)
{
	ft_gamestart(max);
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
	else if (max->game_mode == GAMEPLAY)
		ft_gameplayhook(max);
}