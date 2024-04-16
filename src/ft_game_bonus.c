/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:36:00 by okraus            #+#    #+#             */
/*   Updated: 2024/04/16 13:11:18 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_init_images(t_max *max)
{
	max->i.screen = mlx_new_image(max->mlx, SCREENWIDTH, SCREENHEIGHT);
	//if (!max->screen || (mlx_image_to_window(max->mlx, max->screen, (WIDTH - SCREENWIDTH) / 2, (HEIGHT - SCREENHEIGHT) / 2) < 0))
	if (!max->i.screen || (mlx_image_to_window(max->mlx, max->i.screen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	max->i.spritescreen = mlx_new_image(max->mlx, SCREENWIDTH, SCREENHEIGHT);
	//if (!max->spritescreen || (mlx_image_to_window(max->mlx, max->spritescreen, (WIDTH - SCREENWIDTH) / 2, (HEIGHT - SCREENHEIGHT) / 2) < 0))
	if (!max->i.spritescreen || (mlx_image_to_window(max->mlx, max->i.spritescreen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	max->i.maximap = mlx_new_image(max->mlx, MAPWIDTH, MAPHEIGHT);
	if (!max->i.maximap || (mlx_image_to_window(max->mlx, max->i.maximap, (WIDTH - MAPWIDTH) / 2, (HEIGHT - MAPHEIGHT) / 2) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	max->i.supermap = mlx_new_image(max->mlx, SUPERMAPWIDTH, SUPERMAPHEIGHT);
	if (!max->i.supermap || (mlx_image_to_window(max->mlx, max->i.supermap, 0, HEIGHT - SUPERMAPHEIGHT) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	max->i.minimap = mlx_new_image(max->mlx, MINIWIDTH, MINIHEIGHT);
	if (!max->i.minimap || (mlx_image_to_window(max->mlx, max->i.minimap, WIDTH - MINIWIDTH, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	max->i.menuscreen = mlx_new_image(max->mlx, WIDTH, HEIGHT);
	if (!max->i.menuscreen || (mlx_image_to_window(max->mlx, max->i.menuscreen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	max->i.textscreen = mlx_new_image(max->mlx, WIDTH, HEIGHT);
	if (!max->i.textscreen || (mlx_image_to_window(max->mlx, max->i.textscreen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	max->i.overlay = mlx_new_image(max->mlx, WIDTH, HEIGHT);
	if (!max->i.overlay || (mlx_image_to_window(max->mlx, max->i.overlay, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
}

void	ft_init_textures(t_max *max)
{
	ft_load_texture("./textures/map/brick32.png", &max->t.supermapwall);
	ft_load_texture("./textures/map/floor32.png", &max->t.supermapfloor);
	ft_load_texture("./textures/menu/labyrinth.png", &max->t.menubg);
	ft_load_texture("./textures/menu/button_small.png", &max->t.button);
	ft_load_texture("./textures/menu/buttonplus.png", &max->t.buttonplus);
	ft_load_texture("./textures/menu/textfield.png", &max->t.textfield);
	ft_load_texture("./textures/menu/listfield.png", &max->t.listfield);

	//fonts
	ft_load_texture("./textures/fonts/asciitest.png", &max->t.font);

	//gametext
	ft_load_texture("./textures/woodenboard.png", &max->t.textbg);

	//sprites
	ft_load_texture("./textures/sprites/exit01t.png", &max->t.sprites[SPRITE_EXIT]);
}

void	ft_amaze_bonus(t_max *max)
{
	// mlx_t		*mlx;
	// mlx_image_t	*maximap;
	// mlx_image_t	*minimap;
	// mlx_image_t	*screen;

	if (FULLSCREEN)
		mlx_set_setting(MLX_FULLSCREEN, true);
	max->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!max->mlx)
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 9);
	}
	ft_init_settings(max);
	ft_init_images(max);
	ft_init_textures(max);
	ft_initmenu(max);
	ft_initgamestart(max);
	ft_initgamewon(max);
	ft_initgamelost(max);
	ft_init_overlay(max);
	mlx_key_hook(max->mlx, &ft_keyhook, max);
	//mlx_mouse_hook(mlx, &ft_mousehook, max);
	mlx_loop_hook(max->mlx, ft_hook, max);
	mlx_loop(max->mlx);
	/*                         */
	/* MOVE OR COPY TO FT EXIT */
	/* vvvvvvvvvvvvvvvvvvvvvvv */
	if (max->t.nwall)
		mlx_delete_texture(max->t.nwall);
	if (max->t.ewall)
		mlx_delete_texture(max->t.ewall);
	if (max->t.swall)
		mlx_delete_texture(max->t.swall);
	if (max->t.wwall)
		mlx_delete_texture(max->t.wwall);
	mlx_terminate(max->mlx);
	/* ^^^^^^^^^^^^^^^^^^^^^^^ */
	/* MOVE OR COPY TO FT EXIT */
	/*                         */
}
