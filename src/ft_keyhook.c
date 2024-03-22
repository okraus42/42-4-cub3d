/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:34:36 by okraus            #+#    #+#             */
/*   Updated: 2024/03/22 12:48:03 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_max	*max;

	max = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		if (max->game_mode != MENU)
		{
			max->game_mode = MENU;
			max->menuscreen->enabled = 1;
		}
		else
		{
			max->game_mode = GAMEPLAY;
			max->menuscreen->enabled = 0;
		}
	}
}
