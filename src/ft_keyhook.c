/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:34:36 by okraus            #+#    #+#             */
/*   Updated: 2024/03/24 16:53:03 by okraus           ###   ########.fr       */
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
			max->menu.current_button[0] = RESUME;
			max->menu.current_buttongroup = MAINBUTTONS;
			max->menuscreen->enabled = 1;
		}
		else if (max->game_in_progress)
		{
			max->game_mode = GAMEPLAY;
			max->menuscreen->enabled = 0;
		}
		else
		{
			mlx_close_window(max->mlx);
		}
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		max->key.up = 1;
	}
	else
	{
		max->key.up = 0;
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		max->key.down = 1;
	}
	else
	{
		max->key.down = 0;
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		max->key.right = 1;
	}
	else
	{
		max->key.right = 0;
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		max->key.left = 1;
	}
	else
	{
		max->key.left = 0;
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
	{
		max->key.enter = 1;
	}
	else
	{
		max->key.enter = 0;
	}
}
