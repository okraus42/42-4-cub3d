/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:08:20 by okraus            #+#    #+#             */
/*   Updated: 2023/12/30 17:18:01 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_draw_map(t_max *max)
{
	int	y;
	int	x;
	int	s; //scaling factor

	s = 16;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < max->map->h * s && x < max->map->w * s)
			{
				if ((y / s) * max->map->w + (x / s) == max->map->p.pos)
					mlx_put_pixel(max->screen, x, y, max->map->c.rgba); //player has ceiling colour
				else if (max->map->m[(y / s) * max->map->w + (x / s)] & WALL)
					mlx_put_pixel(max->screen, x, y, 0xff); //walls are black for now
				else if (max->map->m[(y / s) * max->map->w + (x / s)] & FLOOR)
					mlx_put_pixel(max->screen, x, y, max->map->f.rgba); //floor is the proper colour
			}
			
			++x;
		}
		++y;
	}
}

void	ft_hook(void *param)
{
	t_max	*max;

	max = param;
	if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
	{
		ft_printf("You have quit the game by pressing ESC.\n");
		max->exit = 1;
		mlx_close_window(max->mlx);
	}
	ft_draw_map(max);
}