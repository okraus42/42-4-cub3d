/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:34:14 by okraus            #+#    #+#             */
/*   Updated: 2024/03/28 16:52:17 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"


//maybe will need smaller function for initialising menu from the game?
//maybe define texture path in header
void	ft_initrandommapvalues(t_randommap *rm)
{
	rm->width.min = 5;
	rm->width.max = 120;
	rm->width.value = 32;
	rm->height.min = 5;
	rm->height.max = 120;
	rm->height.value = 16;
	rm->ratiode.min = 0;
	rm->ratiode.max = 4096;
	rm->ratiode.value = 64;
	rm->ratiolo.min = 0;
	rm->ratiolo.max = 4096;
	rm->ratiolo.value = 16;
	rm->ratioti.min = 0;
	rm->ratioti.max = 4096;
	rm->ratioti.value = 4;
	rm->ratioxi.min = 0;
	rm->ratioxi.max = 4096;
	rm->ratioxi.value = 1;
	rm->rnorooms.min = 0;
	rm->rnorooms.max = 4096;
	rm->rnorooms.value = 36;
	rm->rorooms.min = 1;
	rm->rorooms.max = 4096;
	rm->rorooms.value = 36;
	rm->rdoors.min = 0;
	rm->rdoors.max = 4096;
	rm->rdoors.value = 64;
	rm->rdeadends.min = 0;
	rm->rdeadends.max = 4096;
	rm->rdeadends.value = 1;
}

void	ft_initmenu(t_max *max)
{
	max->menu.enter = 0;
	max->menu.current_button[MAINBUTTONS] = NEWGAME;
	ft_load_texture("./textures/menu/labyrinth.png", &max->menu.background);
	ft_load_texture("./textures/menu/button_small.png", &max->menu.button);
	ft_load_texture("./textures/menu/buttonplus.png", &max->menu.buttonplus);
	ft_load_texture("./textures/menu/textfield.png", &max->menu.textfield);
	ft_load_texture("./textures/menu/listfield.png", &max->menu.listfield);
	// ft_load_texture("./textures/menu/button_newgame_1_small.png",  &max->menu.new_game_button_on);
	// ft_load_texture("./textures/menu/button_newgame_2_small.png",  &max->menu.new_game_button_off);
	// ft_load_texture("./textures/menu/button_quitgame_1_small.png",  &max->menu.quit_game_button_on);
	// ft_load_texture("./textures/menu/button_quitgame_2_small.png",  &max->menu.quit_game_button_off);

	//fonts
	ft_load_texture("./textures/fonts/asciitest.png", &max->font.asciitest);
	ft_initrandommapvalues(&max->menu.rm);
	ft_initbuttons(max);
	ft_inittextfields(max);
	ft_initlistfields(max);
	max->menu.selection = ONEMAP;
	max->menu.newmap = -1;
	max->menu.current_button[NEWSELECTION] = GTCONTINUE;
	max->menu.current_button[NEWLEVEL] = CUSTOM;
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
	//draw newwriting buttons
	if (max->menu.current_buttongroup == NEWWRITING)
	{
		if (max->menu.newwriting == NAME)
			ft_draw_button(&max->menu.newwritingbuttons[NAME], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[NAME], ACTIVE);
		if (max->menu.newwriting == COALITION)
			ft_draw_button(&max->menu.newwritingbuttons[COALITION], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[COALITION], ACTIVE);
		if (max->menu.newwriting == CAMPUS)
			ft_draw_button(&max->menu.newwritingbuttons[CAMPUS], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[CAMPUS], ACTIVE);
		ft_draw_button(&max->menu.newwritingbuttons[NWBACK], ACTIVE);
		ft_draw_button(&max->menu.newwritingbuttons[NWCONTINUE], ACTIVE);
	}
	//draw newwriting textfields
	if (max->menu.current_buttongroup == NEWWRITING)
	{
		if (max->menu.newwriting == NAME)
			ft_draw_textfield(&max->menu.newwritingfields[NAME], ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[NAME], ACTIVE);
		if (max->menu.newwriting == COALITION)
			ft_draw_textfield(&max->menu.newwritingfields[COALITION], ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[COALITION], ACTIVE);
		if (max->menu.newwriting == CAMPUS)
			ft_draw_textfield(&max->menu.newwritingfields[CAMPUS], ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[CAMPUS], ACTIVE);
	}
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
	//draw selection buttons
	if (max->menu.current_buttongroup == NEWSELECTION)
	{
		// if (max->menu.selection == CAMPAIGN)
		// 	ft_draw_button(&max->menu.gametypebuttons[CAMPAIGN], ACTIVATED);
		// else
		// 	ft_draw_button(&max->menu.gametypebuttons[CAMPAIGN], ACTIVE);
		// if (max->menu.selection == TIMETRIAL)
		// 	ft_draw_button(&max->menu.gametypebuttons[TIMETRIAL], ACTIVATED);
		// else
		// 	ft_draw_button(&max->menu.gametypebuttons[TIMETRIAL], ACTIVE);
		ft_draw_button(&max->menu.gametypebuttons[CAMPAIGN], INACTIVE);
		ft_draw_button(&max->menu.gametypebuttons[TIMETRIAL], INACTIVE);
		//maybe if else not needd
		if (max->menu.selection == ONEMAP)
			ft_draw_button(&max->menu.gametypebuttons[ONEMAP], ACTIVATED);
		else
			ft_draw_button(&max->menu.gametypebuttons[ONEMAP], ACTIVE);
		ft_draw_button(&max->menu.gametypebuttons[GTBACK], ACTIVE);
		ft_draw_button(&max->menu.gametypebuttons[GTCONTINUE], ACTIVE);
	}
	//draw level
	if (max->menu.current_buttongroup == NEWLEVEL)
	{
		//maybe if else not needed
		ft_draw_button(&max->menu.maptypebuttons[CUSTOM], ACTIVE);
		ft_draw_button(&max->menu.maptypebuttons[RANDOM], ACTIVE);
		ft_draw_button(&max->menu.maptypebuttons[MTBACK], ACTIVE);
	}
		//draw newmap buttons
	if (max->menu.current_buttongroup == NEWMAP)
	{
		ft_draw_button(&max->menu.mapselectionbuttons[CUSTOM], ACTIVATED);
		ft_draw_button(&max->menu.mapselectionbuttons[RANDOM], ACTIVE);
		ft_draw_button(&max->menu.mapselectionbuttons[MSBACK], ACTIVE);
		ft_draw_button(&max->menu.mapselectionbuttons[MSCONTINUE], ACTIVE);
	}
	//draw newmap listfield
	if (max->menu.current_buttongroup == NEWMAP)
	{
		//change if later
		ft_draw_listfield(&max->menu.custommap, ACTIVE);
	}
	if (max->menu.current_buttongroup == NEWRANDOM)
	{
		ft_draw_button(&max->menu.randomselectionbuttons[RWIDTH], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RHEIGHT], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RRATIODE], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RRATIOLO], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RRATIOTI], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RRATIOXI], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RNOROOMS], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[ROROOMS], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RDOORS], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RDEADENDS], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RBACK], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RCONTINUE], ACTIVE);
	}
	//draw optionbuttons
}

void	ft_selectnewbutton(t_max *max, t_button *button)
{
	if (max->key.up)
	{
		while (button->up)
		{
			button = button->up;
			if (button->state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[button->group] = button->id;
				break ;
			}
		}
		max->key.up = 0;
	}
	if (max->key.down)
	{
		while (button->down)
		{
			button = button->down;
			if (button->state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[button->group] = button->id;
				break ;
			}
		}
		max->key.down = 0;
	}
	if (max->key.left)
	{
		while (button->left)
		{
			button = button->left;
			if (button->state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[button->group] = button->id;
				break ;
			}
		}
		max->key.left = 0;
	}
	if (max->key.right)
	{
		while (button->right)
		{
			button = button->right;
			if (button->state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[button->group] = button->id;
				break ;
			}
		}
		max->key.right = 0;
	}
}

// void	ft_selectbuttonmainmenu(t_max *max)
// {
// 	int	newbutton;

// 	newbutton = max->menu.current_button[MAINBUTTONS];
// 	if (max->key.up)
// 	{
// 		while (newbutton > 0)
// 		{
// 			--newbutton;
// 			if (max->menu.mainbuttons[newbutton].state & (ACTIVE | ACTIVATED))
// 			{
// 				max->menu.current_button[MAINBUTTONS] = newbutton;
// 				break ;
// 			}
// 		}
// 		max->key.up = 0;
// 	}
// 	if (max->key.down)
// 	{
// 		while (newbutton < MAINBUTTONSCOUNT - 1)
// 		{
// 			++newbutton;
// 			if (max->menu.mainbuttons[newbutton].state & (ACTIVE | ACTIVATED))
// 			{
// 				max->menu.current_button[MAINBUTTONS] = newbutton;
// 				break ;
// 			}
// 		}
// 		max->key.down = 0;
// 	}
// }

// void	ft_selectbuttonnewwriting(t_max *max)
// {
// 	int	newbutton;

// 	if (max->menu.newwriting == NAME)
// 	{
// 		ft_write_in_textfield(max, &max->menu.newwritingfields[NAME]);
// 		return ;
// 	}
// 	if (max->menu.newwriting == COALITION)
// 	{
// 		ft_write_in_textfield(max, &max->menu.newwritingfields[COALITION]);
// 		return ;
// 	}
// 	if (max->menu.newwriting == CAMPUS)
// 	{
// 		ft_write_in_textfield(max, &max->menu.newwritingfields[CAMPUS]);
// 		return ;
// 	}
// 	newbutton = max->menu.current_button[NEWWRITING];
// 	if (max->key.up)
// 	{
// 		while (newbutton > 0)
// 		{
// 			--newbutton;
// 			if (max->menu.newwritingbuttons[newbutton].state & (ACTIVE | ACTIVATED))
// 			{
// 				max->menu.current_button[NEWWRITING] = newbutton;
// 				break ;
// 			}
// 		}
// 		max->key.up = 0;
// 	}
// 	if (max->key.down)
// 	{
// 		while (newbutton < DIFFICULTYBUTTONCOUNT - 1)
// 		{
// 			++newbutton;
// 			if (max->menu.newwritingbuttons[newbutton].state & (ACTIVE | ACTIVATED))
// 			{
// 				max->menu.current_button[NEWWRITING] = newbutton;
// 				break ;
// 			}
// 		}
// 		max->key.down = 0;
// 	}
// }

// void	ft_selectbuttonnewdifficulty(t_max *max)
// {
// 	int	newbutton;

// 	newbutton = max->menu.current_button[NEWDIFFICULTY];
// 	if (max->key.up)
// 	{
// 		while (newbutton > 0)
// 		{
// 			--newbutton;
// 			if (max->menu.gamedifficultybuttons[newbutton].state & (ACTIVE | ACTIVATED))
// 			{
// 				max->menu.current_button[NEWDIFFICULTY] = newbutton;
// 				break ;
// 			}
// 		}
// 		max->key.up = 0;
// 	}
// 	if (max->key.down)
// 	{
// 		while (newbutton < DIFFICULTYBUTTONCOUNT - 1)
// 		{
// 			++newbutton;
// 			if (max->menu.gamedifficultybuttons[newbutton].state & (ACTIVE | ACTIVATED))
// 			{
// 				max->menu.current_button[NEWDIFFICULTY] = newbutton;
// 				break ;
// 			}
// 		}
// 		max->key.down = 0;
// 	}
// }

// void	ft_selectbuttonnewselection(t_max *max)
// {
// 	int	newbutton;

// 	newbutton = max->menu.current_button[NEWSELECTION];
// 	if (max->key.up)
// 	{
// 		while (newbutton > 0)
// 		{
// 			--newbutton;
// 			if (max->menu.gametypebuttons[newbutton].state & (ACTIVE | ACTIVATED))
// 			{
// 				max->menu.current_button[NEWSELECTION] = newbutton;
// 				break ;
// 			}
// 		}
// 		max->key.up = 0;
// 	}
// 	if (max->key.down)
// 	{
// 		while (newbutton < GAMETYPEBUTTONCOUNT - 1)
// 		{
// 			++newbutton;
// 			if (max->menu.gametypebuttons[newbutton].state & (ACTIVE | ACTIVATED))
// 			{
// 				max->menu.current_button[NEWSELECTION] = newbutton;
// 				break ;
// 			}
// 		}
// 		max->key.down = 0;
// 	}
// }

// void	ft_selectbuttonnewlevel(t_max *max)
// {
// 	int	newbutton;

// 	newbutton = max->menu.current_button[NEWLEVEL];
// 	if (max->key.up)
// 	{
// 		while (newbutton > 0)
// 		{
// 			--newbutton;
// 			if (max->menu.maptypebuttons[newbutton].state & (ACTIVE | ACTIVATED))
// 			{
// 				max->menu.current_button[NEWLEVEL] = newbutton;
// 				break ;
// 			}
// 		}
// 		max->key.up = 0;
// 	}
// 	if (max->key.down)
// 	{
// 		while (newbutton < MAPTYPEBUTTONCOUNT - 1)
// 		{
// 			++newbutton;
// 			if (max->menu.maptypebuttons[newbutton].state & (ACTIVE | ACTIVATED))
// 			{
// 				max->menu.current_button[NEWLEVEL] = newbutton;
// 				break ;
// 			}
// 		}
// 		max->key.down = 0;
// 	}
// }

void	ft_selectbuttonnewmap(t_max *max)
{
	int	newbutton;

	if (max->menu.cm_state)
	{
		ft_choose_in_listfield(max, &max->menu.custommap);
		return ;
	}
	newbutton = max->menu.current_button[NEWMAP];
	if (max->key.up)
	{
		while (newbutton > 0)
		{
			--newbutton;
			if (max->menu.mapselectionbuttons[newbutton].state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[NEWMAP] = newbutton;
				break ;
			}
		}
		max->key.up = 0;
	}
	if (max->key.down)
	{
		while (newbutton < MAPSELECTIONBUTTONCOUNT - 1)
		{
			++newbutton;
			if (max->menu.mapselectionbuttons[newbutton].state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[NEWMAP] = newbutton;
				break ;
			}
		}
		max->key.down = 0;
	}
}

void	ft_selectbuttonnewrandom(t_max *max)
{
	int	newbutton;

	if (max->menu.random_state[RWIDTH])
	{
		ft_choose_in_button(max, &max->menu.randomselectionbuttons[RWIDTH]);
		return ;
	}
	if (max->menu.random_state[RHEIGHT])
	{
		ft_choose_in_button(max, &max->menu.randomselectionbuttons[RHEIGHT]);
		return ;
	}
	if (max->menu.random_state[RRATIODE])
	{
		ft_choose_in_button(max, &max->menu.randomselectionbuttons[RRATIODE]);
		return ;
	}
	if (max->menu.random_state[RRATIOLO])
	{
		ft_choose_in_button(max, &max->menu.randomselectionbuttons[RRATIOLO]);
		return ;
	}
	if (max->menu.random_state[RRATIOTI])
	{
		ft_choose_in_button(max, &max->menu.randomselectionbuttons[RRATIOTI]);
		return ;
	}
	if (max->menu.random_state[RRATIOXI])
	{
		ft_choose_in_button(max, &max->menu.randomselectionbuttons[RRATIOXI]);
		return ;
	}
	if (max->menu.random_state[RNOROOMS])
	{
		ft_choose_in_button(max, &max->menu.randomselectionbuttons[RNOROOMS]);
		return ;
	}
	if (max->menu.random_state[ROROOMS])
	{
		ft_choose_in_button(max, &max->menu.randomselectionbuttons[ROROOMS]);
		return ;
	}
	if (max->menu.random_state[RDOORS])
	{
		ft_choose_in_button(max, &max->menu.randomselectionbuttons[RDOORS]);
		return ;
	}
	if (max->menu.random_state[RDEADENDS])
	{
		ft_choose_in_button(max, &max->menu.randomselectionbuttons[RDEADENDS]);
		return ;
	}
	newbutton = max->menu.current_button[NEWRANDOM];
	
	if (max->key.up)
	{
		while (newbutton > 0)
		{
			--newbutton;
			if (max->menu.randomselectionbuttons[newbutton].state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[NEWRANDOM] = newbutton;
				break ;
			}
		}
		max->key.up = 0;
	}
	if (max->key.down)
	{
		while (newbutton < RANDOMBUTTONCOUNT - 1)
		{
			++newbutton;
			if (max->menu.randomselectionbuttons[newbutton].state & (ACTIVE | ACTIVATED))
			{
				max->menu.current_button[NEWRANDOM] = newbutton;
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
		//ft_selectbuttonmainmenu(max);
		ft_selectnewbutton(max, &max->menu.mainbuttons[max->menu.current_button[MAINBUTTONS]]);
	}
	if (max->menu.current_buttongroup == NEWWRITING)
	{
		if (max->menu.newwriting == NAME)
		{
			ft_write_in_textfield(max, &max->menu.newwritingfields[NAME]);
			return ;
		}
		if (max->menu.newwriting == COALITION)
		{
			ft_write_in_textfield(max, &max->menu.newwritingfields[COALITION]);
			return ;
		}
		if (max->menu.newwriting == CAMPUS)
		{
			ft_write_in_textfield(max, &max->menu.newwritingfields[CAMPUS]);
			return ;
		}
		ft_selectnewbutton(max, &max->menu.newwritingbuttons[max->menu.current_button[NEWWRITING]]);
		//ft_selectbuttonnewwriting(max);
	}
	if (max->menu.current_buttongroup == NEWDIFFICULTY)
	{
		//ft_selectbuttonnewdifficulty(max);
		ft_selectnewbutton(max, &max->menu.gamedifficultybuttons[max->menu.current_button[NEWDIFFICULTY]]);
	}
	if (max->menu.current_buttongroup == NEWSELECTION)
	{
		//ft_selectbuttonnewselection(max);
		ft_selectnewbutton(max, &max->menu.gametypebuttons[max->menu.current_button[NEWSELECTION]]);
	}
	if (max->menu.current_buttongroup == NEWLEVEL)
	{
		//ft_selectbuttonnewlevel(max);
		ft_selectnewbutton(max, &max->menu.maptypebuttons[max->menu.current_button[NEWLEVEL]]);
	}
	if (max->menu.current_buttongroup == NEWMAP)
	{
		ft_selectbuttonnewmap(max);
	}
	if (max->menu.current_buttongroup == NEWRANDOM)
	{
		ft_selectbuttonnewrandom(max);
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

void	ft_draw_newwritingbuttons(t_max *max)
{
	if (max->menu.current_button[NEWWRITING] == NAME)
	{
		if (max->menu.newwriting == NAME)
			ft_draw_button(&max->menu.newwritingbuttons[NAME], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[NAME], SELECTED);
	}
	else if (max->menu.current_button[NEWWRITING] == COALITION)
	{
		if (max->menu.newwriting == COALITION)
			ft_draw_button(&max->menu.newwritingbuttons[COALITION], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[COALITION], SELECTED);
	}
	else if (max->menu.current_button[NEWWRITING] == CAMPUS)
	{
		if (max->menu.newwriting == CAMPUS)
			ft_draw_button(&max->menu.newwritingbuttons[CAMPUS], ACTIVATED);
		else
			ft_draw_button(&max->menu.newwritingbuttons[CAMPUS], SELECTED);
	}
	else if (max->menu.current_button[NEWWRITING] == NWBACK)
	{
		ft_draw_button(&max->menu.newwritingbuttons[NWBACK], SELECTED);
	}
	else if (max->menu.current_button[NEWWRITING] == NWCONTINUE)
	{
		ft_draw_button(&max->menu.newwritingbuttons[NWCONTINUE], SELECTED);
	}
}

void	ft_draw_newwritingtextfields(t_max *max)
{
	if (max->menu.current_button[NEWWRITING] == NAME)
	{
		if (max->menu.newwriting == NAME)
			ft_draw_textfield(&max->menu.newwritingfields[NAME], ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[NAME], SELECTED);
	}
	else if (max->menu.current_button[NEWWRITING] == COALITION)
	{
		if (max->menu.newwriting == COALITION)
			ft_draw_textfield(&max->menu.newwritingfields[COALITION], ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[COALITION], SELECTED);
	}
	else if (max->menu.current_button[NEWWRITING] == CAMPUS)
	{
		if (max->menu.newwriting == CAMPUS)
			ft_draw_textfield(&max->menu.newwritingfields[CAMPUS], ACTIVATED);
		else
			ft_draw_textfield(&max->menu.newwritingfields[CAMPUS], SELECTED);
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

void	ft_draw_gametypebuttons(t_max *max)
{
	if (max->menu.current_button[NEWSELECTION] == CAMPAIGN)
	{
		ft_draw_button(&max->menu.gametypebuttons[CAMPAIGN], SELECTED);
	}
	else if (max->menu.current_button[NEWSELECTION] == TIMETRIAL)
	{
		ft_draw_button(&max->menu.gametypebuttons[TIMETRIAL], SELECTED);
	}
	else if (max->menu.current_button[NEWSELECTION] == ONEMAP)
	{
		ft_draw_button(&max->menu.gametypebuttons[ONEMAP], SELECTED);
	}
	else if (max->menu.current_button[NEWSELECTION] == GTBACK)
	{
		ft_draw_button(&max->menu.gametypebuttons[GTBACK], SELECTED);
	}
	else if (max->menu.current_button[NEWSELECTION] == GTCONTINUE)
	{
		ft_draw_button(&max->menu.gametypebuttons[GTCONTINUE], SELECTED);
	}
}

void	ft_draw_maptypebuttons(t_max *max)
{
	if (max->menu.current_button[NEWLEVEL] == CUSTOM)
	{
		ft_draw_button(&max->menu.maptypebuttons[CUSTOM], SELECTED);
	}
	else if (max->menu.current_button[NEWLEVEL] == RANDOM)
	{
		ft_draw_button(&max->menu.maptypebuttons[RANDOM], SELECTED);
	}
	else if (max->menu.current_button[NEWLEVEL] == MTBACK)
	{
		ft_draw_button(&max->menu.maptypebuttons[MTBACK], SELECTED);
	}
}

void	ft_draw_newmapbuttons(t_max *max)
{
	if (max->menu.current_button[NEWMAP] == CUSTOM)
	{
		if (max->menu.cm_state)
			ft_draw_button(&max->menu.mapselectionbuttons[CUSTOM], ACTIVATED);
		else
			ft_draw_button(&max->menu.mapselectionbuttons[CUSTOM], SELECTED);
	}
	else if (max->menu.current_button[NEWMAP] == RANDOM)
	{
		ft_draw_button(&max->menu.mapselectionbuttons[RANDOM], SELECTED);
	}
	else if (max->menu.current_button[NEWMAP] == MSBACK)
	{
		ft_draw_button(&max->menu.mapselectionbuttons[MSBACK], SELECTED);
	}
	else if (max->menu.current_button[NEWMAP] == MSCONTINUE)
	{
		ft_draw_button(&max->menu.mapselectionbuttons[MSCONTINUE], SELECTED);
	}
}

void	ft_draw_newmaplistfields(t_max *max)
{
	if (max->menu.cm_state)
		ft_draw_listfield(&max->menu.custommap, ACTIVATED);
	else
		ft_draw_listfield(&max->menu.custommap, SELECTED);
}

void	ft_draw_newrandombuttons(t_max *max)
{
	if (max->menu.current_button[NEWRANDOM] == RWIDTH)
	{
		if (max->menu.random_state[RWIDTH])
			ft_draw_button(&max->menu.randomselectionbuttons[RWIDTH], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomselectionbuttons[RWIDTH], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RHEIGHT)
	{
		if (max->menu.random_state[RHEIGHT])
			ft_draw_button(&max->menu.randomselectionbuttons[RHEIGHT], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomselectionbuttons[RHEIGHT], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RRATIODE)
	{
		if (max->menu.random_state[RRATIODE])
			ft_draw_button(&max->menu.randomselectionbuttons[RRATIODE], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomselectionbuttons[RRATIODE], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RRATIOLO)
	{
		if (max->menu.random_state[RRATIOLO])
			ft_draw_button(&max->menu.randomselectionbuttons[RRATIOLO], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomselectionbuttons[RRATIOLO], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RRATIOTI)
	{
		if (max->menu.random_state[RRATIOTI])
			ft_draw_button(&max->menu.randomselectionbuttons[RRATIOTI], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomselectionbuttons[RRATIOTI], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RRATIOXI)
	{
		if (max->menu.random_state[RRATIOXI])
			ft_draw_button(&max->menu.randomselectionbuttons[RRATIOXI], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomselectionbuttons[RRATIOXI], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RNOROOMS)
	{
		if (max->menu.random_state[RNOROOMS])
			ft_draw_button(&max->menu.randomselectionbuttons[RNOROOMS], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomselectionbuttons[RNOROOMS], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == ROROOMS)
	{
		if (max->menu.random_state[ROROOMS])
			ft_draw_button(&max->menu.randomselectionbuttons[ROROOMS], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomselectionbuttons[ROROOMS], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RDOORS)
	{
		if (max->menu.random_state[RDOORS])
			ft_draw_button(&max->menu.randomselectionbuttons[RDOORS], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomselectionbuttons[RDOORS], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RDEADENDS)
	{
		if (max->menu.random_state[RDEADENDS])
			ft_draw_button(&max->menu.randomselectionbuttons[RDEADENDS], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomselectionbuttons[RDEADENDS], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RBACK)
	{
		ft_draw_button(&max->menu.randomselectionbuttons[RBACK], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RCONTINUE)
	{
		ft_draw_button(&max->menu.randomselectionbuttons[RCONTINUE], SELECTED);
	}
}

void	ft_menu(t_max *max)
{
	ft_selectbutton(max);
	ft_draw_menu(max);
	ft_draw_mainmenubuttons(max);
	if (max->menu.current_buttongroup == NEWWRITING)
	{
		ft_draw_newwritingbuttons(max);
		ft_draw_newwritingtextfields(max);
	}
	if (max->menu.current_buttongroup == NEWDIFFICULTY)
		ft_draw_gamedifficultybuttons(max);
	if (max->menu.current_buttongroup == NEWSELECTION)
		ft_draw_gametypebuttons(max);
	if (max->menu.current_buttongroup == NEWLEVEL)
		ft_draw_maptypebuttons(max);
	if (max->menu.current_buttongroup == NEWMAP)
	{
		ft_draw_newmapbuttons(max);
		ft_draw_newmaplistfields(max);
	}
	if (max->menu.current_buttongroup == NEWRANDOM)
	{
		ft_draw_newrandombuttons(max);
		//draw game options buttons
	}
	//printf("%i\n", max->menu.current_buttongroup);
	
	if (max->menu.enter)
	{
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
				max->menu.current_buttongroup = NEWWRITING;
			}
			else if (max->menu.current_buttongroup == NEWWRITING)
			{
				if (max->menu.current_button[NEWWRITING] == NAME)
				{
					if (max->menu.newwriting == NAME)
					{
						max->menu.newwriting = -1;
						max->menu.newwritingfields[NAME].text.highlight = -1;
					}
					else
						max->menu.newwriting = NAME;
				}
				else if (max->menu.current_button[NEWWRITING] == COALITION)
				{
					if (max->menu.newwriting == COALITION)
					{
						max->menu.newwriting = -1;
						max->menu.newwritingfields[COALITION].text.highlight = -1;
					}
					else
						max->menu.newwriting = COALITION;
				}
				else if (max->menu.current_button[NEWWRITING] == CAMPUS)
				{
					if (max->menu.newwriting == CAMPUS)
					{
						max->menu.newwriting = -1;
						max->menu.newwritingfields[CAMPUS].text.highlight = -1;
					}
					else
						max->menu.newwriting = CAMPUS;
				}
				else if (max->menu.current_button[NEWWRITING] == NWBACK)
				{
					max->menu.current_buttongroup = MAINBUTTONS;
				}
				else if (max->menu.current_button[NEWWRITING] == NWCONTINUE)
				{
					//max->menu.current_button[NEWDIFFICULTY] = max->difficulty;
					max->menu.current_buttongroup = NEWDIFFICULTY;
				}
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
					max->menu.current_buttongroup = NEWWRITING;
				}
				else if (max->menu.current_button[NEWDIFFICULTY] == GDCONTINUE)
				{
					//max->menu.current_button[NEWDIFFICULTY] = max->difficulty;
					max->menu.current_buttongroup = NEWSELECTION;
				}
			}
			else if (max->menu.current_buttongroup == NEWSELECTION)
			{
				if (max->menu.current_button[NEWSELECTION] == CAMPAIGN)
				{
					max->menu.selection = CAMPAIGN;
				}
				else if (max->menu.current_button[NEWSELECTION] == TIMETRIAL)
				{
					max->menu.selection = TIMETRIAL;
				}
				else if (max->menu.current_button[NEWSELECTION] == ONEMAP)
				{
					max->menu.selection = ONEMAP;
				}
				else if (max->menu.current_button[NEWSELECTION] == GTBACK)
				{
					max->menu.current_buttongroup = NEWDIFFICULTY;
				}
				else if (max->menu.current_button[NEWSELECTION] == GTCONTINUE)
				{
					//max->menu.current_button[NEWSELECTION] = max->menu.selection;
					max->menu.current_buttongroup = NEWLEVEL;
				}
			}
			else if (max->menu.current_buttongroup == NEWLEVEL)
			{
				if (max->menu.current_button[NEWLEVEL] == CUSTOM)
				{
					max->menu.current_buttongroup = NEWMAP;
					max->menu.current_button[NEWMAP] = CUSTOM;
					max->menu.cm_state = 1;
				}
				else if (max->menu.current_button[NEWLEVEL] == RANDOM)
				{
					max->menu.current_buttongroup = NEWRANDOM;
				}
				else if (max->menu.current_button[NEWLEVEL] == MTBACK)
				{
					max->menu.current_buttongroup = NEWSELECTION;
				}
			}
			else if (max->menu.current_buttongroup == NEWMAP)
			{
				if (max->menu.current_button[NEWMAP] == CUSTOM)
				{
					if (max->menu.cm_state)
					{
						max->menu.cm_state = 0;
						max->menu.current_button[NEWMAP] = MSCONTINUE;
					}
					else
					{
						max->menu.cm_state = 1;
					}
				}
				else if (max->menu.current_button[NEWMAP] == RANDOM)
				{
					max->menu.current_buttongroup = NEWRANDOM;
				}
				else if (max->menu.current_button[NEWMAP] == MSBACK)
				{
					max->menu.current_buttongroup = NEWLEVEL;
				}
				else if (max->menu.current_button[NEWMAP] == MSCONTINUE)
				{
					//max->menu.current_button[NEWLEVEL] = max->menu.newmap;
					max->map->file = max->menu.custommap.text[max->menu.custommap.highlight].text;
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
			//
			// THIS NEEDS UPDATES to check which button is pressed and change its state
			//
			else if (max->menu.current_buttongroup == NEWRANDOM)
			{
				if (max->menu.current_button[NEWRANDOM] == RWIDTH)
				{
					if (max->menu.random_state[RWIDTH])
					{
						max->menu.random_state[RWIDTH] = 0;
					}
					else
					{
						max->menu.random_state[RWIDTH] = 1;
					}
				}
				else if (max->menu.current_button[NEWRANDOM] == RHEIGHT)
				{
					if (max->menu.random_state[RHEIGHT])
					{
						max->menu.random_state[RHEIGHT] = 0;
					}
					else
					{
						max->menu.random_state[RHEIGHT] = 1;
					}
				}
				else if (max->menu.current_button[NEWRANDOM] == RRATIODE)
				{
					if (max->menu.random_state[RRATIODE])
					{
						max->menu.random_state[RRATIODE] = 0;
					}
					else
					{
						max->menu.random_state[RRATIODE] = 1;
					}
				}
				else if (max->menu.current_button[NEWRANDOM] == RRATIOLO)
				{
					if (max->menu.random_state[RRATIOLO])
					{
						max->menu.random_state[RRATIOLO] = 0;
					}
					else
					{
						max->menu.random_state[RRATIOLO] = 1;
					}
				}
				else if (max->menu.current_button[NEWRANDOM] == RRATIOTI)
				{
					if (max->menu.random_state[RRATIOTI])
					{
						max->menu.random_state[RRATIOTI] = 0;
					}
					else
					{
						max->menu.random_state[RRATIOTI] = 1;
					}
				}
				else if (max->menu.current_button[NEWRANDOM] == RRATIOXI)
				{
					if (max->menu.random_state[RRATIOXI])
					{
						max->menu.random_state[RRATIOXI] = 0;
					}
					else
					{
						max->menu.random_state[RRATIOXI] = 1;
					}
				}
				else if (max->menu.current_button[NEWRANDOM] == RNOROOMS)
				{
					if (max->menu.random_state[RNOROOMS])
					{
						max->menu.random_state[RNOROOMS] = 0;
					}
					else
					{
						max->menu.random_state[RNOROOMS] = 1;
					}
				}
				else if (max->menu.current_button[NEWRANDOM] == ROROOMS)
				{
					if (max->menu.random_state[ROROOMS])
					{
						max->menu.random_state[ROROOMS] = 0;
					}
					else
					{
						max->menu.random_state[ROROOMS] = 1;
					}
				}
				else if (max->menu.current_button[NEWRANDOM] == RDOORS)
				{
					if (max->menu.random_state[RDOORS])
					{
						max->menu.random_state[RDOORS] = 0;
					}
					else
					{
						max->menu.random_state[RDOORS] = 1;
					}
				}
				else if (max->menu.current_button[NEWRANDOM] == RDEADENDS)
				{
					if (max->menu.random_state[RDEADENDS])
					{
						max->menu.random_state[RDEADENDS] = 0;
					}
					else
					{
						max->menu.random_state[RDEADENDS] = 1;
					}
				}
				else if (max->menu.current_button[NEWRANDOM] == RBACK)
				{
					max->menu.current_buttongroup = NEWLEVEL;
				}
				else if (max->menu.current_button[NEWRANDOM] == RCONTINUE)
				{
					//max->menu.current_button[NEWLEVEL] = max->menu.newmap;
					max->map->file = "RANDOM";
					if (ft_process_random(max))
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
				// ft_printf("to be built");
				// //temp
				// max->map->file = "maps/validmap4.cub";
				// if (ft_process_file(max))
				// {
				// 	max->game_mode = GAMEPLAY;
				// 	max->menu.current_button[MAINBUTTONS] = RESUME;
				// 	max->menu.current_buttongroup = MAINBUTTONS;
				// 	max->game_in_progress = 1;
				// 	max->menuscreen->enabled = 0;
				// }
				// else
				// {
				// 	ft_dprintf(2, "Invalid map\n");
				// }
			}
		}
		if (max->menu.current_button[MAINBUTTONS] == QUITGAME)
		{
			mlx_close_window(max->mlx);
		}
	}
}
