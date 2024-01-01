/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:08:20 by okraus            #+#    #+#             */
/*   Updated: 2024/01/01 15:27:05 by okraus           ###   ########.fr       */
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

int	ft_is_inside2(t_max *max, unsigned int rad2, int y, int x)
{
	unsigned int	cx;
	unsigned int	cy;

	cx = x - (int)max->map->p.x + max->math->sin[max->map->p.orientation] / 1024;
	cy = y - (int)max->map->p.y + max->math->cos[max->map->p.orientation] / 1024;
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
					mlx_put_pixel(max->screen, x, y, max->map->c.rgba & TMASK);	//player has ceiling colour
				}
				else if (ft_is_inside2(max, 1024, (y << 8) / s, (x << 8) / s))
				{
					mlx_put_pixel(max->screen, x, y, 0x00ff00ff & TMASK);	//green circle for the direction visualisation
				}
				else if (max->map->m[(y / s) * max->map->w + (x / s)] & WALL)
					mlx_put_pixel(max->screen, x, y, 0x80); //walls are black for now
				else if (max->map->m[(y / s) * max->map->w + (x / s)] & FLOOR)
					mlx_put_pixel(max->screen, x, y, max->map->f.rgba & TMASK); //floor is the proper colour
			}
			++x;
		}
		++y;
	}
}


// do something about sharp corners
void	ft_move_player(t_map *map, int y, int x)
{
	map->p.y = y;
	map->p.x = x;
	if (map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
	{
		if (y < ((map->p.my << 8) | WALLDISTANCE))
			map->p.sy = WALLDISTANCE;
	}
	if (map->m[map->p.my * map->w + map->p.mx] & FLOORWNW
		&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
		&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWW))
	{
		if (y < ((map->p.my << 8) | WALLDISTANCE)
			&& x < ((map->p.mx << 8) | WALLDISTANCE))
		{
			map->p.sy = WALLDISTANCE;
			map->p.sx = WALLDISTANCE;
		}
	}
	if (map->m[map->p.my * map->w + map->p.mx] & FLOORWNE
		&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWN)
		&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWE))
	{
		if (y < ((map->p.my << 8) | WALLDISTANCE)
			&& x > ((map->p.mx << 8) | (256 - WALLDISTANCE)))
		{
			map->p.sy = WALLDISTANCE;
			map->p.sx = 256 - WALLDISTANCE;
		}
	}
	if (map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
	{
		if (y > ((map->p.my << 8) | (256 - WALLDISTANCE)))
			map->p.sy = 256 - WALLDISTANCE;
	}
	if (map->m[map->p.my * map->w + map->p.mx] & FLOORWSW
		&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
		&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWW))
	{
		if (y > ((map->p.my << 8) | (256 - WALLDISTANCE))
			&& x < ((map->p.mx << 8) | WALLDISTANCE))
		{
			map->p.sy = 256 - WALLDISTANCE;
			map->p.sx = WALLDISTANCE;
		}
	}
	if (map->m[map->p.my * map->w + map->p.mx] & FLOORWSE
		&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWS)
		&& !(map->m[map->p.my * map->w + map->p.mx] & FLOORWE))
	{
		if (y > ((map->p.my << 8) | (256 - WALLDISTANCE))
			&& x > ((map->p.mx << 8) | (256 - WALLDISTANCE)))
		{
			map->p.sy = 256 - WALLDISTANCE;
			map->p.sx = 256 - WALLDISTANCE;
		}
	}
	if (map->m[map->p.my * map->w + map->p.mx] & FLOORWW)
	{
		if (x < ((map->p.mx << 8) | WALLDISTANCE))
			map->p.sx = WALLDISTANCE;
	}
	if (map->m[map->p.my * map->w + map->p.mx] & FLOORWE)
	{
		if (x > ((map->p.mx << 8) | (256 - WALLDISTANCE)))
			map->p.sx = 256 - WALLDISTANCE;
	}
	//handle corners ??
}


//hook for moving player on the map
//create hook for moving map instead of player
void	ft_hook(void *param)
{
	t_max	*max;

	max = param;
	max->newms = ft_get_time_in_ms();
	max->framems = (unsigned int)(max->newms - max->oldms);
	//ft_printf("framems: %u\n", max->framems);
	max->map->p.turnspeed = max->framems * 64;
	max->map->p.speed = max->framems;
	max->map->p.xspeed = (max->map->p.speed * max->math->cos[max->map->p.orientation]) / 65536;
	max->map->p.yspeed = (max->map->p.speed * max->math->sin[max->map->p.orientation]) / 65536;
	++max->frame;
	max->oldms = max->newms;
	if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
	{
		ft_printf("You have quit the game by pressing ESC.\n");
		max->exit = 1;
		mlx_close_window(max->mlx);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_SPACE))	//sprinting, faster but slower turns LIMIT STAMINA
	{
		//ft_printf("You have pressed space.\n");
		max->map->p.xspeed *= 2;
		max->map->p.yspeed *= 2;
		max->map->p.turnspeed /= 2;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_LEFT_SHIFT))	//sprinting, faster but slower turns LIMIT STAMINA
	{
		//ft_printf("You have pressed space.\n");
		max->map->p.xspeed *= 2;
		max->map->p.yspeed *= 2;
		max->map->p.turnspeed /= 2;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_UP) || mlx_is_key_down(max->mlx, MLX_KEY_W))
	{
		//ft_printf("You have pressed up arrow.\n");
		//ft_printf("xspeed %i | yspeed %i | orientation %i.\n", max->map->p.xspeed, max->map->p.yspeed, max->map->p.orientation);
		ft_move_player(max->map, max->map->p.y - max->map->p.xspeed, max->map->p.x - max->map->p.yspeed);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_DOWN) || mlx_is_key_down(max->mlx, MLX_KEY_S))
	{
		//ft_printf("You have pressed down arrow.\n");
		ft_move_player(max->map, max->map->p.y + max->map->p.xspeed, max->map->p.x + max->map->p.yspeed);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_A))
	{
		//ft_printf("You have pressed A.\n");
		ft_move_player(max->map, max->map->p.y + max->map->p.yspeed, max->map->p.x - max->map->p.xspeed);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_D))
	{
		//ft_printf("You have pressed D.\n");
		ft_move_player(max->map, max->map->p.y - max->map->p.yspeed, max->map->p.x + max->map->p.xspeed);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_LEFT) || mlx_is_key_down(max->mlx, MLX_KEY_Q))
	{
		//ft_printf("You have pressed left arrow.\n");
		//ft_printf("xspeed %i | yspeed %i | orientation %i.\n", max->map->p.xspeed, max->map->p.yspeed, max->map->p.orientation);
		max->map->p.orientation += max->map->p.turnspeed;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(max->mlx, MLX_KEY_E))
	{
		//ft_printf("You have pressed right arrow.\n");
		max->map->p.orientation -= max->map->p.turnspeed;
	}
	ft_draw_map(max);
}