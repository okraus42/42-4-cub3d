/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:59:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/30 17:06:46 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_amaze_standard(t_max *max)
{
	mlx_t		*mlx;
	mlx_image_t	*screen;

	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mlx)
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(9);
	}
	screen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!screen || (mlx_image_to_window(mlx, screen, 0, 0) < 0))
	{
		ft_dprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno));
		//free everything
		exit(10);
	}
	max->mlx = mlx;
	max->screen = screen;
	mlx_loop_hook(mlx, ft_hook, max);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}