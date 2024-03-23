/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:34:14 by okraus            #+#    #+#             */
/*   Updated: 2024/03/23 15:04:20 by okraus           ###   ########.fr       */
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
	ft_load_texture("./textures/menu/button_small.png", &max->menu.button);
	// ft_load_texture("./textures/menu/button_newgame_1_small.png",  &max->menu.new_game_button_on);
	// ft_load_texture("./textures/menu/button_newgame_2_small.png",  &max->menu.new_game_button_off);
	// ft_load_texture("./textures/menu/button_quitgame_1_small.png",  &max->menu.quit_game_button_on);
	// ft_load_texture("./textures/menu/button_quitgame_2_small.png",  &max->menu.quit_game_button_off);

	//fonts
	ft_load_texture("./textures/fonts/asciitest.png", &max->font.asciitest);
}

void	ft_draw_char(mlx_texture_t *font, mlx_image_t *image, int x, int y, int offset, unsigned int colour, int height)
{
	int				w;
	int				h;
	int				j;
	int				i;
	int				a;
	unsigned int	c;

	w = height / 2;
	h = height;
	j = 0;
	//draw letter
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			//720 length of png
			a = (j * (240 / height) * 11400 * 4) + ((i * (240 / height) + offset) * 4);
			c = (font->pixels[a]) << 24 | (font->pixels[a + 1]) << 16 | (font->pixels[a + 2]) << 8 | (font->pixels[a + 3]);
			if (c < 0x7FFFFFFF)
			{
				mlx_put_pixel(image, i + x, j + y, colour);
			}
			// (void)colour;
			// mlx_put_pixel(image, i + x, j + y, c);
			++i;
		}
		++j;
	}
}

//(120) for the width of the character in the font.png
void	ft_draw_text(mlx_texture_t *font, mlx_image_t *image, int x, int y, char *str, unsigned int colour, int height)
{
	int	i;
	int	startx;


	i = 0;
	startx = x;
	while (str[i])
	{
		if (ft_isprint(str[i]))
		{
			ft_draw_char(font, image, x, y, (str[i] - ' ') * (120), colour, height);
			x += height / 2;
		}
		else if (str[i] == '\t')
		{
			x += height * 2;
		}
		else if (str[i] == '\n')
		{
			y += height;
			x = startx;
		}
		++i;
	}
}

void	ft_draw_button(t_max *max, int x, int y, char *str, int state)
{
	int				w;
	int				h;
	int				j;
	int				i;
	int				a;
	unsigned int	c;

	w = max->menu.button->width;
	h = max->menu.button->height;
	j = 0;
	//draw button
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			a = (j * w * 4) + (i * 4);
			if (i < w && j < h)
				c = (max->menu.button->pixels[a]) << 24 | (max->menu.button->pixels[a + 1]) << 16 | (max->menu.button->pixels[a + 2]) << 8 | (max->menu.button->pixels[a + 3]);
			else
				c = 0xFF00FFFF;
			if (c & 0xFFFFFF00)
			{
				if (state & INACTIVE)
					mlx_put_pixel(max->menuscreen, i + x, j + y, 0X7F7F7FFF);
				else if (state & ACTIVE)
					mlx_put_pixel(max->menuscreen, i + x, j + y, 0X7F007FFF);
				else if (state & SELECTED)
					mlx_put_pixel(max->menuscreen, i + x, j + y, 0XFF00FFFF);
				else if (state & ACTIVATED)
					mlx_put_pixel(max->menuscreen, i + x, j + y, 0XFF7FFFFF);
			}
			else if ((c & 0xFF) == 0xFF)
				mlx_put_pixel(max->menuscreen, i + x, j + y, c);
			++i;
		}
		++j;
	}
	//draw text
	if (state & INACTIVE)
		ft_draw_text(max->font.asciitest, max->menuscreen, x + 40, y + 40, str, 0x666666FF, 60);
	else if (state & ACTIVE)
		ft_draw_text(max->font.asciitest, max->menuscreen, x + 40, y + 40, str, 0xFF, 60);
	else if (state & SELECTED)
		ft_draw_text(max->font.asciitest, max->menuscreen, x + 40, y + 40, str, 0xFF, 60);
	else if (state & ACTIVATED)
		ft_draw_text(max->font.asciitest, max->menuscreen, x + 40, y + 40, str, 0xFF, 60);
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
	ft_draw_button(max, 200, 200, S_NEWGAME, ACTIVE);
	ft_draw_button(max, 200, 400, S_SAVEGAME, INACTIVE);
	ft_draw_button(max, 200, 600, S_LOADGAME, INACTIVE);
	ft_draw_button(max, 200, 800, S_QUITGAME, ACTIVE);
}

void	ft_menu(t_max *max)
{
	ft_draw_menu(max);
	if (max->menu.current_button == NEWGAME)
	{
		ft_draw_button(max, 200, 200, S_NEWGAME, SELECTED);
	}
	if (max->menu.current_button == QUITGAME)
	{
		ft_draw_button(max, 200, 800, S_QUITGAME, SELECTED);
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
