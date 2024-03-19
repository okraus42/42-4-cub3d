/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:34:14 by okraus            #+#    #+#             */
/*   Updated: 2024/03/19 16:40:02 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"


//maybe will need smaller function for initialising menu from the game?
//maybe define texture path in header
void	ft_initmenu(t_max *max)
{
	max->menu.enter = 0;
	max->menu.current_button = NEWGAME;
	ft_load_texture("./textures/menu/labyrinth.png", &max->menu.background);
	ft_load_texture("./textures/menu/button_newgame_1.png",  &max->menu.new_game_button_on);
	ft_load_texture("./textures/menu/button_newgame_2.png",  &max->menu.new_game_button_off);
	ft_load_texture("./textures/menu/button_quitgame_1.png",  &max->menu.quit_game_button_on);
	ft_load_texture("./textures/menu/button_quitgame_2.png",  &max->menu.quit_game_button_off);
}

void	ft_draw_menu(t_max *max)
{
	int				w;
	int				h;
	int				y;
	int				x;
	unsigned int	c;

	w = max->menu.background->width;
	h = max->menu.background->height;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if(x < w && y < h)
				c = (unsigned int)(max->menu.background->pixels[(y * w) + (x * 4)]) << 24 | (unsigned int)(max->menu.background->pixels[(y * w) + (x * 4) + 1]) << 16 | (unsigned int)(max->menu.background->pixels[(y * w) + (x * 4) + 2]) << 8 | 0xFF;
			else
				c = 0xFF00FFFF;
			//ft_printf("%i\n", y * WIDTH + x * 4);
			mlx_put_pixel(max->menuscreen, x, y, c);
			++x;
		}
		++y;
	}
}

void	ft_menu(t_max *max)
{
	ft_draw_menu(max);
	if (max->menu.current_button == NEWGAME)
	{
		//remove highlight from all buttons
		//highlight the new game button
	}
	if (max->menu.current_button == QUITGAME)
	{
		//remove highlight from all buttons
		//highlight the quit button
	}
	if (max->menu.enter)
	{
		if (max->menu.current_button == NEWGAME)
		{
			max->game_mode = GAMEPLAY;
			max->menuscreen->enabled = 0;
		}
		if (max->menu.current_button == QUITGAME)
		{
			mlx_close_window(max->mlx);
		}
		max->menu.enter = 0;
	}
}
