/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:36:00 by okraus            #+#    #+#             */
/*   Updated: 2024/03/31 14:36:37 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

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
	max->screen = mlx_new_image(max->mlx, SCREENWIDTH, SCREENHEIGHT);
	//if (!max->screen || (mlx_image_to_window(max->mlx, max->screen, (WIDTH - SCREENWIDTH) / 2, (HEIGHT - SCREENHEIGHT) / 2) < 0))
	if (!max->screen || (mlx_image_to_window(max->mlx, max->screen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	max->maximap = mlx_new_image(max->mlx, MAPWIDTH, MAPHEIGHT);
	if (!max->maximap || (mlx_image_to_window(max->mlx, max->maximap, (WIDTH - MAPWIDTH) / 2, (HEIGHT - MAPHEIGHT) / 2) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	max->minimap = mlx_new_image(max->mlx, MINIWIDTH, MINIHEIGHT);
	if (!max->minimap || (mlx_image_to_window(max->mlx, max->minimap, WIDTH - MINIWIDTH, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	max->menuscreen = mlx_new_image(max->mlx, WIDTH, HEIGHT);
	if (!max->menuscreen || (mlx_image_to_window(max->mlx, max->menuscreen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	max->textscreen = mlx_new_image(max->mlx, WIDTH, HEIGHT);
	if (!max->textscreen || (mlx_image_to_window(max->mlx, max->textscreen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		ft_exit(max, 10);
	}
	// max->mlx = mlx;
	// max->maximap = maximap;
	// max->minimap = minimap;
	// max->screen = screen;
	max->str[0] = mlx_put_string(max->mlx, "", 10, 5);
	max->str[1] = mlx_put_string(max->mlx, "", 10, 25);
	ft_initmenu(max);
	ft_initgamestart(max);
	mlx_key_hook(max->mlx, &ft_keyhook, max);
	//mlx_mouse_hook(mlx, &ft_mousehook, max);
	mlx_loop_hook(max->mlx, ft_hook, max);
	mlx_loop(max->mlx);
	/*                         */
	/* MOVE OR COPY TO FT EXIT */
	/* vvvvvvvvvvvvvvvvvvvvvvv */
	if (max->t->nwall)
		mlx_delete_texture(max->t->nwall);
	if (max->t->ewall)
		mlx_delete_texture(max->t->ewall);
	if (max->t->swall)
		mlx_delete_texture(max->t->swall);
	if (max->t->wwall)
		mlx_delete_texture(max->t->wwall);
	mlx_terminate(max->mlx);
	/* ^^^^^^^^^^^^^^^^^^^^^^^ */
	/* MOVE OR COPY TO FT EXIT */
	/*                         */
}
