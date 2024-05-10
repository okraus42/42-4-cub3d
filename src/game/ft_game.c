/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:59:42 by okraus            #+#    #+#             */
/*   Updated: 2024/05/10 11:38:24 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_amaze_standard_helper(t_max *max)
{
	ft_init_settings(max);
	ft_init_images(max);
	ft_init_textures(max);
	ft_add_pool(max);
	ft_initmenu(max);
	ft_initgamestart(max);
	ft_initgamewon(max);
	ft_initgamelost(max);
	ft_init_overlay(max);
	ft_init_sprites(max);
}

void	ft_amaze_standard_helper_2(t_max *max)
{
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
	ft_newgame(max);
	max->game_mode = GAMEPLAY;
}

void	ft_amaze_standard_helper_3(t_max *max)
{
	mlx_key_hook(max->mlx, &ft_keyhook, max);
	mlx_loop_hook(max->mlx, ft_hook, max);
	mlx_loop(max->mlx);
	if (max->t.nwall)
		mlx_delete_texture(max->t.nwall);
	if (max->t.ewall)
		mlx_delete_texture(max->t.ewall);
	if (max->t.swall)
		mlx_delete_texture(max->t.swall);
	if (max->t.wwall)
		mlx_delete_texture(max->t.wwall);
	mlx_terminate(max->mlx);
}

void	ft_amaze_standard_helper_4(t_max *max)
{
	if (FULLSCREEN)
		mlx_set_setting(MLX_FULLSCREEN, true);
	max->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!max->mlx)
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		ft_exit(max, 9);
	}
	ft_amaze_standard_helper(max);
	max->i.menuscreen->enabled = 0;
	printf("FILENAME %s\n", max->map.file);
}

void	ft_amaze_standard(t_max *max)
{
	printf("FILENAME %s\n", max->map.file);
	max->bonus = 0;
	ft_amaze_standard_helper_4(max);
	if (ft_process_file(max))
	{
		printf("gamestart loop starting...\n");
		max->settings.lightdist = max->settings.maxdist / 4;
		ft_amaze_standard_helper_2(max);
	}
	else
	{
		max->menu.current_button[NEWMAP] = CUSTOM;
		max->menu.lf_state = 1;
		ft_dprintf(2, "Invalid map %s\n", max->map.file);
		ft_exit(max, 1);
	}
	ft_amaze_standard_helper_3(max);
}
