/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:59:42 by okraus            #+#    #+#             */
/*   Updated: 2024/01/07 14:45:28 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_amaze_standard(t_max *max)
{
	mlx_t		*mlx;
	mlx_image_t	*maximap;
	mlx_image_t	*minimap;
	mlx_image_t	*screen;

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
	max->mlx = mlx;
	max->maximap = maximap;
	max->minimap = minimap;
	max->screen = screen;
	mlx_loop_hook(mlx, ft_hook, max);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}