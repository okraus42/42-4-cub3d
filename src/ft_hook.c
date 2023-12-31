/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:08:20 by okraus            #+#    #+#             */
/*   Updated: 2023/12/31 13:55:09 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	ft_is_inside(t_map *map, unsigned int rad2, int y, int x)
{
	unsigned int	cx;
	unsigned int	cy;

	cx = x - (int)map->p.x;
	cy = y - (int)map->p.y;
	if (cx * cx + cy * cy <= rad2)
		return (1);
	return (0);
}

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
				if (ft_is_inside(max->map, 4096, (y << 8) / s, (x << 8) / s))
				{
					mlx_put_pixel(max->screen, x, y, max->map->c.rgba);	//player has ceiling colour
				}
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
	max->map->p.xspeed = (max->map->p.speed * max->math->cos[max->map->p.orientation]) / 65536;
	max->map->p.yspeed = (max->map->p.speed * max->math->sin[max->map->p.orientation]) / 65536;
	if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
	{
		ft_printf("You have quit the game by pressing ESC.\n");
		max->exit = 1;
		mlx_close_window(max->mlx);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_UP) || mlx_is_key_down(max->mlx, MLX_KEY_W))
	{
		ft_printf("You have pressed up arrow.\n");
		//ft_printf("xspeed %i | yspeed %i | orientation %i.\n", max->map->p.xspeed, max->map->p.yspeed, max->map->p.orientation);
		max->map->p.y -= max->map->p.xspeed;
		max->map->p.x -= max->map->p.yspeed;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_DOWN) || mlx_is_key_down(max->mlx, MLX_KEY_S))
	{
		ft_printf("You have pressed down arrow.\n");
		max->map->p.y += max->map->p.xspeed;
		max->map->p.x += max->map->p.yspeed;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_A))
	{
		ft_printf("You have pressed A.\n");
		max->map->p.x -= max->map->p.xspeed;
		max->map->p.y -= max->map->p.yspeed;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_D))
	{
		ft_printf("You have pressed D.\n");
		max->map->p.x += max->map->p.xspeed;
		max->map->p.y += max->map->p.yspeed;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_LEFT) || mlx_is_key_down(max->mlx, MLX_KEY_Q))
	{
		ft_printf("You have pressed left arrow.\n");
		//ft_printf("xspeed %i | yspeed %i | orientation %i.\n", max->map->p.xspeed, max->map->p.yspeed, max->map->p.orientation);
		max->map->p.orientation += max->map->p.turnspeed;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(max->mlx, MLX_KEY_E))
	{
		ft_printf("You have pressed right arrow.\n");
		max->map->p.orientation -= max->map->p.turnspeed;
	}
	ft_draw_map(max);
}