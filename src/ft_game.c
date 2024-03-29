/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:59:42 by okraus            #+#    #+#             */
/*   Updated: 2024/03/29 11:48:43 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_amaze_standard(t_max *max)
{
	mlx_t		*mlx;
	mlx_image_t	*maximap;
	mlx_image_t	*minimap;
	mlx_image_t	*screen;

	if (FULLSCREEN)
		mlx_set_setting(MLX_FULLSCREEN, true);
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mlx)
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(9);
	}
	screen = mlx_new_image(mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!screen || (mlx_image_to_window(mlx, screen, (WIDTH - SCREENWIDTH) / 2, (HEIGHT - SCREENHEIGHT) / 2) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(10);
	}
	maximap = mlx_new_image(mlx, MAPWIDTH, MAPHEIGHT);
	if (!maximap || (mlx_image_to_window(mlx, maximap, (WIDTH - MAPWIDTH) / 2, (HEIGHT - MAPHEIGHT) / 2) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(10);
	}
	minimap = mlx_new_image(mlx, MINIWIDTH, MINIHEIGHT);
	if (!minimap || (mlx_image_to_window(mlx, minimap, WIDTH - MINIWIDTH, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(10);
	}
	max->menuscreen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!screen || (mlx_image_to_window(mlx, max->menuscreen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(10);
	}
	max->textscreen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!max->textscreen || (mlx_image_to_window(mlx, max->textscreen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(10);
	}
	max->mlx = mlx;
	max->maximap = maximap;
	max->minimap = minimap;
	max->screen = screen;
	max->str[0] = mlx_put_string(max->mlx, "", 10, 5);
	max->str[1] = mlx_put_string(max->mlx, "", 10, 25);
	ft_initmenu(max);
	ft_initgamestart(max);
	mlx_key_hook(mlx, &ft_keyhook, max);
	//mlx_mouse_hook(mlx, &mousehook, max);
	mlx_loop_hook(mlx, ft_hook, max);
	mlx_loop(mlx);
	if (max->t->nwall)
		mlx_delete_texture(max->t->nwall);
	if (max->t->ewall)
		mlx_delete_texture(max->t->ewall);
	if (max->t->swall)
		mlx_delete_texture(max->t->swall);
	if (max->t->wwall)
		mlx_delete_texture(max->t->wwall);
	mlx_terminate(mlx);
}

void	ft_amaze_bonus(t_max *max)
{
	mlx_t		*mlx;
	mlx_image_t	*maximap;
	mlx_image_t	*minimap;
	mlx_image_t	*screen;

	if (FULLSCREEN)
		mlx_set_setting(MLX_FULLSCREEN, true);
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mlx)
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(9);
	}
	screen = mlx_new_image(mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!screen || (mlx_image_to_window(mlx, screen, (WIDTH - SCREENWIDTH) / 2, (HEIGHT - SCREENHEIGHT) / 2) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(10);
	}
	maximap = mlx_new_image(mlx, MAPWIDTH, MAPHEIGHT);
	if (!maximap || (mlx_image_to_window(mlx, maximap, (WIDTH - MAPWIDTH) / 2, (HEIGHT - MAPHEIGHT) / 2) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(10);
	}
	minimap = mlx_new_image(mlx, MINIWIDTH, MINIHEIGHT);
	if (!minimap || (mlx_image_to_window(mlx, minimap, WIDTH - MINIWIDTH, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(10);
	}
	max->menuscreen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!max->menuscreen || (mlx_image_to_window(mlx, max->menuscreen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(10);
	}
	max->textscreen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!max->textscreen || (mlx_image_to_window(mlx, max->textscreen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(10);
	}
	max->mlx = mlx;
	max->maximap = maximap;
	max->minimap = minimap;
	max->screen = screen;
	max->str[0] = mlx_put_string(max->mlx, "", 10, 5);
	max->str[1] = mlx_put_string(max->mlx, "", 10, 25);
	ft_initmenu(max);
	ft_initgamestart(max);
	mlx_key_hook(mlx, &ft_keyhook, max);
	//mlx_mouse_hook(mlx, &mousehook, max);
	mlx_loop_hook(mlx, ft_hook, max);
	mlx_loop(mlx);
	if (max->t->nwall)
		mlx_delete_texture(max->t->nwall);
	if (max->t->ewall)
		mlx_delete_texture(max->t->ewall);
	if (max->t->swall)
		mlx_delete_texture(max->t->swall);
	if (max->t->wwall)
		mlx_delete_texture(max->t->wwall);
	mlx_terminate(mlx);
}