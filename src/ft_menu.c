/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:34:14 by okraus            #+#    #+#             */
/*   Updated: 2024/03/20 13:40:51 by okraus           ###   ########.fr       */
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
	//ft_load_texture("./textures/menu/button_newgame_1_small.png", &max->menu.background);
	ft_load_texture("./textures/menu/button_newgame_1_small.png",  &max->menu.new_game_button_on);
	ft_load_texture("./textures/menu/button_newgame_2_small.png",  &max->menu.new_game_button_off);
	ft_load_texture("./textures/menu/button_quitgame_1_small.png",  &max->menu.quit_game_button_on);
	ft_load_texture("./textures/menu/button_quitgame_2_small.png",  &max->menu.quit_game_button_off);
}

void	ft_draw_button(t_max *max, mlx_texture_t *button, int x, int y)
{
	int				w;
	int				h;
	int				j;
	int				i;
	int				a;
	unsigned int	c;

	w = button->width;
	h = button->height;
	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			a = (j * w * 4) + (i * 4);
			if (i < w && j < h)
				c = (button->pixels[a]) << 24 | (button->pixels[a + 1]) << 16 | (button->pixels[a + 2]) << 8 | (button->pixels[a + 3]);
			else
				c = 0xFF00FFFF;
			if ((c & 0xFF) == 0xFF)
				mlx_put_pixel(max->menuscreen, i + x, j + y, c);
			++i;
		}
		++j;
	}
}

void	ft_draw_menu(t_max *max)
{
	int				w;
	int				h;
	int				y;
	int				x;
	int				a;
	unsigned int	c;

	w = max->menu.background->width;
	h = max->menu.background->height;
	y = 0;
	//draw background
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			a = (y * w * 4) + (x * 4);
			if (x < w && y < h)
				c = (max->menu.background->pixels[a]) << 24 | (max->menu.background->pixels[a + 1]) << 16 | (max->menu.background->pixels[a + 2]) << 8 | 0xFF;
			else
				c = 0xFF00FFFF;
			mlx_put_pixel(max->menuscreen, x, y, c);
			++x;
		}
		++y;
	}
	//draw button 1
	ft_draw_button(max, max->menu.new_game_button_off, WIDTH / 2 - max->menu.new_game_button_off->width / 2, 200);
	ft_draw_button(max, max->menu.quit_game_button_off, WIDTH / 2 - max->menu.quit_game_button_off->width / 2, 800);
}

void	ft_menu(t_max *max)
{
	ft_draw_menu(max);
	if (max->menu.current_button == NEWGAME)
	{
		ft_draw_button(max, max->menu.new_game_button_on, WIDTH / 2 - max->menu.new_game_button_on->width / 2, 200);
	}
	if (max->menu.current_button == QUITGAME)
	{
		ft_draw_button(max, max->menu.quit_game_button_on, WIDTH / 2 - max->menu.quit_game_button_on->width / 2, 800);
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
