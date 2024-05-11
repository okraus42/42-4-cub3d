/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_bonus_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:00:06 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 15:01:03 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_init_textures(t_max *max)
{
	ft_load_texture("./textures/map/brick32.png", &max->t.supermapwall);
	ft_load_texture("./textures/map/floor32.png", &max->t.supermapfloor);
	ft_load_texture("./textures/pool3.png", &max->t.menubg);
	ft_load_texture("./textures/menu/button_small.png", &max->t.button);
	ft_load_texture("./textures/menu/buttonplus.png", &max->t.buttonplus);
	ft_load_texture("./textures/menu/textfield.png", &max->t.textfield);
	ft_load_texture("./textures/menu/listfield.png", &max->t.listfield);
	ft_load_texture("./textures/fonts/asciitest.png", &max->t.font);
	ft_load_texture("./textures/woodenboard.png", &max->t.textbg);
	ft_load_texture("./textures/sprites/exit01t.png",
		&max->t.sprites[EXIT_GLOW]);
	ft_load_texture("./textures/sprites/flamingo_normal256.png",
		&max->t.sprites[FLAMINGO_TEXTURE]);
	ft_load_texture("./textures/sprites/flamingo_glow256.png",
		&max->t.sprites[FLAMINGO_GLOW]);
	ft_load_texture("./textures/sprites/dolphins512.png", &max->t.door);
	ft_load_texture("./textures/poolwallN.png", &max->t.nwall);
	ft_load_texture("./textures/poolwallW.png", &max->t.wwall);
	ft_load_texture("./textures/poolwallS.png", &max->t.swall);
	ft_load_texture("./textures/poolwallE.png", &max->t.ewall);
	ft_load_texture("./textures/pool3.png", &max->t.pool);
}

void	ft_add_pool(t_max *max)
{
	int		y;
	int		x;
	int		u;
	int		v;
	t_clr	c;

	y = 0;
	while (y < HEIGHT)
	{
		v = y * max->t.pool->width * 4LL * max->t.pool->height / HEIGHT;
		x = 0;
		while (x < WIDTH)
		{
			u = x * 4 * max->t.pool->width / WIDTH;
			c.r = max->t.pool->pixels[v + u + 0] / 2;
			c.g = max->t.pool->pixels[v + u + 1] / 2;
			c.b = max->t.pool->pixels[v + u + 2] / 2;
			c.a = 0xFF;
			mlx_put_pixel(max->i.hud, x, y, c.rgba);
			++x;
		}
		++y;
	}
	printf("%i %i\n", max->t.pool->height, HEIGHT);
}

void	ft_amaze_bonus(t_max *max)
{
	max->bonus = 1;
	if (FULLSCREEN)
		mlx_set_setting(MLX_FULLSCREEN, true);
	max->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!max->mlx)
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		ft_exit(max, 9);
	}
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
	mlx_key_hook(max->mlx, &ft_keyhook, max);
	mlx_loop_hook(max->mlx, ft_hook, max);
	mlx_loop(max->mlx);
	ft_exit(max, 0);
}
