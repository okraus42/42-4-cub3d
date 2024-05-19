/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameplay_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:27:14 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/10 13:27:56 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_gameplay_5(t_max *max)
{
	if (max->map.p.reveal && !(max->frame % 4))
	{
		ft_discover_map(&max->map);
		++max->map.p.reveal;
		if (max->map.p.reveal > 32)
			max->map.p.reveal = 0;
	}
	if (max->difficulty == MEDIUM)
	{
		if (!(max->frame % max->settings.tick))
			ft_revisit_map(&max->map);
	}
	else if (max->difficulty == HARD)
	{
		if (!(max->frame % 2))
			ft_revisit_map(&max->map);
	}
	ft_init_orays(max);
	ft_check_sprites(max);
	ft_draw_map(max);
	ft_draw_minimap(max);
	ft_draw_screen3d(max);
	ft_game_win(max);
	ft_game_lose(max);
	ft_check_doors(max);
}

void	ft_gameplay_6(t_max *max)
{
	if (max->keys[MLX_KEY_F])
	{
		printf("opening/closing door\n");
		ft_interact_door(max);
		max->keys[MLX_KEY_F] = 0;
	}
	if (max->keys[MLX_KEY_F1])
	{
		printf("fake quicksave\n");
		if (ft_savegame(max))
			ft_dprintf(2, "Game was not saved\n");
		max->keys[MLX_KEY_F1] = 0;
	}
	if (max->keys[MLX_KEY_F2])
	{
		printf("fake quickload\n");
		if (ft_loadgame(max))
			ft_dprintf(2, "Unable to load the game,\
				 make sure the safe file exists\n");
		max->keys[MLX_KEY_F2] = 0;
	}
}

void	ft_gameplay_7(t_max *max)
{
	if (max->keys[MLX_KEY_F9])
	{
		max->keys[MLX_KEY_F9] = 0;
		printf("quickload\n");
		if (ft_quickload(max))
			ft_dprintf(2, "Unable to load the game,\
				 make sure the safe file exists\n");
	}
	if (max->keys[MLX_KEY_M])
	{
		max->keys[MLX_KEY_M] = 0;
		max->i.maximap->enabled ^= 1;
	}
	if (max->keys[MLX_KEY_KP_3])
	{
		max->keys[MLX_KEY_KP_3] = 0;
		max->i.fogscreen->enabled ^= 1;
	}
	if (max->keys[MLX_KEY_KP_1])
	{
		max->keys[MLX_KEY_KP_1] = 0;
		max->i.spritescreen->enabled ^= 1;
	}
}

void	ft_gameplay_global_helper(t_max *max)
{
	ft_draw_strings(max);
	ft_gameplay_3(max);
	ft_gameplay_4(max);
	ft_gameplay_5(max);
	ft_gameplay_6(max);
	if (max->keys[MLX_KEY_F5])
	{
		max->keys[MLX_KEY_F5] = 0;
		printf("quicksave\n");
		if (ft_quicksave(max))
			ft_dprintf(2, "Game was not saved\n");
	}
	ft_gameplay_7(max);
	if (max->keys[MLX_KEY_KP_2])
	{
		max->keys[MLX_KEY_KP_2] = 0;
		max->i.overlay->enabled ^= 1;
	}
}

void	ft_gameplay(t_max *max)
{
	int	x;
	int	y;
	int	angle;

	ft_change_light_dist(max);
	ft_gameplay_2(max);
	mlx_get_mouse_pos(max->mlx, &x, &y);
	angle = (512 - x) * 4;
	max->map.p.orientation -= angle;
	if (max->map.p.orientation < 0)
		max->map.p.orientation += MAXDEGREE;
	if (max->map.p.orientation >= MAXDEGREE)
		max->map.p.orientation -= MAXDEGREE;
	mlx_set_mouse_pos(max->mlx, 512, 512);
	ft_gameplay_global_helper(max);
}
