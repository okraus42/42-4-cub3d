/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:34:14 by okraus            #+#    #+#             */
/*   Updated: 2024/03/24 16:54:54 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"


//maybe will need smaller function for initialising menu from the game?
//maybe define texture path in header
void	ft_initmenu(t_max *max)
{
	max->menu.enter = 0;
	max->menu.current_button[0] = NEWGAME;
	ft_load_texture("./textures/menu/labyrinth.png", &max->menu.background);
	ft_load_texture("./textures/menu/button_small.png", &max->menu.button);
	// ft_load_texture("./textures/menu/button_newgame_1_small.png",  &max->menu.new_game_button_on);
	// ft_load_texture("./textures/menu/button_newgame_2_small.png",  &max->menu.new_game_button_off);
	// ft_load_texture("./textures/menu/button_quitgame_1_small.png",  &max->menu.quit_game_button_on);
	// ft_load_texture("./textures/menu/button_quitgame_2_small.png",  &max->menu.quit_game_button_off);

	//fonts
	ft_load_texture("./textures/fonts/asciitest.png", &max->font.asciitest);
	ft_initbuttons(max);
}

// typedef struct s_text
// {
// 	mlx_texture_t	*font;
// 	char			*text;
// 	unsigned int	c;
// 	unsigned int	cb;
// 	int				x;
// 	int				y;
// 	int				height;
// }	t_text;

// typedef struct s_button
// {
// 	mlx_texture_t	*button;
// 	t_text			text;
// 	unsigned int	c;
// 	int				x;
// 	int				y;
// 	int				w;
// 	int				h;
// 	int				state
// }	t_button;

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
	//draw main buttons
	if (max->game_in_progress)
		ft_draw_button(&max->menu.mainbuttons[RESUME], ACTIVE);
	else
		ft_draw_button(&max->menu.mainbuttons[RESUME], INACTIVE);
	ft_draw_button(&max->menu.mainbuttons[NEWGAME], ACTIVE);
	ft_draw_button(&max->menu.mainbuttons[SAVEGAME], INACTIVE);
	ft_draw_button(&max->menu.mainbuttons[LOADGAME], INACTIVE);
	ft_draw_button(&max->menu.mainbuttons[SETTINGS], INACTIVE);
	ft_draw_button(&max->menu.mainbuttons[HALLOFFAME], INACTIVE);
	ft_draw_button(&max->menu.mainbuttons[QUITGAME], ACTIVE);
	//draw difficulty buttons
	if (max->menu.current_buttongroup == NEWDIFFICULTY)
	{
		if (max->difficulty == EASY)
			ft_draw_button(&max->menu.gamedifficultybuttons[EASY], ACTIVATED);
		else
			ft_draw_button(&max->menu.gamedifficultybuttons[EASY], ACTIVE);
		if (max->difficulty == MEDIUM)
			ft_draw_button(&max->menu.gamedifficultybuttons[MEDIUM], ACTIVATED);
		else
			ft_draw_button(&max->menu.gamedifficultybuttons[MEDIUM], ACTIVE);
		if (max->difficulty == HARD)
			ft_draw_button(&max->menu.gamedifficultybuttons[HARD], ACTIVATED);
		else
			ft_draw_button(&max->menu.gamedifficultybuttons[HARD], ACTIVE);
		ft_draw_button(&max->menu.gamedifficultybuttons[GDBACK], ACTIVE);
		ft_draw_button(&max->menu.gamedifficultybuttons[GDCONTINUE], ACTIVE);
	}
}

void	ft_selectbuttonmainmenu(t_max *max)
{
	int	newbutton;

	newbutton = max->menu.current_button[MAINBUTTONS];
	if (max->key.up)
	{
		while (newbutton > 0)
		{
			--newbutton;
			if (max->menu.mainbuttons[newbutton].state == ACTIVE)
			{
				max->menu.current_button[MAINBUTTONS] = newbutton;
				break ;
			}
		}
		max->key.up = 0;
	}
	if (max->key.down)
	{
		while (newbutton < MAINBUTTONSCOUNT - 1)
		{
			++newbutton;
			if (max->menu.mainbuttons[newbutton].state == ACTIVE)
			{
				max->menu.current_button[MAINBUTTONS] = newbutton;
				break ;
			}
		}
		max->key.down = 0;
	}
}

void	ft_selectbuttonnewdifficulty(t_max *max)
{
	int	newbutton;

	newbutton = max->menu.current_button[NEWDIFFICULTY];
	if (max->key.up)
	{
		while (newbutton > 0)
		{
			--newbutton;
			if (max->menu.gamedifficultybuttons[newbutton].state == ACTIVE)
			{
				max->menu.current_button[NEWDIFFICULTY] = newbutton;
				break ;
			}
		}
		max->key.up = 0;
	}
	if (max->key.down)
	{
		while (newbutton < DIFFICULTYBUTTONCOUNT - 1)
		{
			++newbutton;
			if (max->menu.gamedifficultybuttons[newbutton].state == ACTIVE)
			{
				max->menu.current_button[NEWDIFFICULTY] = newbutton;
				break ;
			}
		}
		max->key.down = 0;
	}
}

void	ft_selectbutton(t_max *max)
{
	if (max->key.enter)
	{
		max->menu.enter = 1;
		max->key.enter = 0;
	}
	if (max->menu.current_buttongroup == MAINBUTTONS)
	{
		ft_selectbuttonmainmenu(max);
	}
	if (max->menu.current_buttongroup == NEWDIFFICULTY)
	{
		ft_selectbuttonnewdifficulty(max);
	}
}

void	ft_draw_mainmenubuttons(t_max *max)
{
	if (max->menu.current_button[MAINBUTTONS] == RESUME)
	{
		ft_draw_button(&max->menu.mainbuttons[RESUME], SELECTED);
	}
	if (max->menu.current_button[MAINBUTTONS] == NEWGAME)
	{
		if (max->menu.current_buttongroup == MAINBUTTONS)
			ft_draw_button(&max->menu.mainbuttons[NEWGAME], SELECTED);
		else
			ft_draw_button(&max->menu.mainbuttons[NEWGAME], ACTIVATED);
	}
	if (max->menu.current_button[MAINBUTTONS] == QUITGAME)
	{
		ft_draw_button(&max->menu.mainbuttons[QUITGAME], SELECTED);
	}
}

void	ft_draw_gamedifficultybuttons(t_max *max)
{
	if (max->menu.current_button[NEWDIFFICULTY] == EASY)
	{
		ft_draw_button(&max->menu.gamedifficultybuttons[EASY], SELECTED);
	}
	else if (max->menu.current_button[NEWDIFFICULTY] == MEDIUM)
	{
		ft_draw_button(&max->menu.gamedifficultybuttons[MEDIUM], SELECTED);
	}
	else if (max->menu.current_button[NEWDIFFICULTY] == HARD)
	{
		ft_draw_button(&max->menu.gamedifficultybuttons[HARD], SELECTED);
	}
	else if (max->menu.current_button[NEWDIFFICULTY] == GDBACK)
	{
		ft_draw_button(&max->menu.gamedifficultybuttons[GDBACK], SELECTED);
	}
	else if (max->menu.current_button[NEWDIFFICULTY] == GDCONTINUE)
	{
		ft_draw_button(&max->menu.gamedifficultybuttons[GDCONTINUE], SELECTED);
	}
}
void	ft_menu(t_max *max)
{
	ft_selectbutton(max);
	ft_draw_menu(max);
	ft_draw_mainmenubuttons(max);
	if (max->menu.current_buttongroup == NEWDIFFICULTY)
		ft_draw_gamedifficultybuttons(max);
	//printf("%i\n", max->menu.current_buttongroup);
	
	if (max->menu.enter)
	{
		printf("enter\n");
		max->menu.enter = 0;
		if (max->menu.current_button[MAINBUTTONS] == RESUME)
		{
			max->game_mode = GAMEPLAY;
			max->menuscreen->enabled = 0;
		}
		if (max->menu.current_button[MAINBUTTONS] == NEWGAME)
		{
			if (max->menu.current_buttongroup == MAINBUTTONS)
			{
				max->menu.current_buttongroup = NEWDIFFICULTY;
			}
			else if (max->menu.current_buttongroup == NEWDIFFICULTY)
			{
				if (max->menu.current_button[NEWDIFFICULTY] == EASY)
				{
					max->difficulty = EASY;
				}
				else if (max->menu.current_button[NEWDIFFICULTY] == MEDIUM)
				{
					max->difficulty = MEDIUM;
				}
				else if (max->menu.current_button[NEWDIFFICULTY] == HARD)
				{
					max->difficulty = HARD;
				}
				else if (max->menu.current_button[NEWDIFFICULTY] == GDBACK)
				{
					max->menu.current_buttongroup = MAINBUTTONS;
				}
				else if (max->menu.current_button[NEWDIFFICULTY] == GDCONTINUE)
				{
					max->menu.current_button[NEWDIFFICULTY] = max->difficulty;
					max->map->file = "maps/validmap4.cub";
					if (ft_process_file(max))
					{
						max->game_mode = GAMEPLAY;
						max->menu.current_button[MAINBUTTONS] = RESUME;
						max->menu.current_buttongroup = MAINBUTTONS;
						max->game_in_progress = 1;
						max->menuscreen->enabled = 0;
					}
					else
					{
						ft_dprintf(2, "Invalid map\n");
					}
				}
			}
		}
		if (max->menu.current_button[MAINBUTTONS] == QUITGAME)
		{
			mlx_close_window(max->mlx);
		}
	}
}
