/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:34:14 by okraus            #+#    #+#             */
/*   Updated: 2024/05/01 11:19:24 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"


//maybe will need smaller function for initialising menu from the game?
//maybe define texture path in header
void	ft_initrandommapvalues(t_randommap *rm)
{
	rm->seed = time(0);
	srand(rm->seed);
	rm->width.min = 5;
	rm->width.max = 120;
	rm->width.value = (rand() % 8 + 2) * (rand() % 8 + 2) + 1;
	rm->height.min = 5;
	rm->height.max = 120;
	rm->height.value = (rand() % 8 + 2) * (rand() % 8 + 2) + 1;
	rm->ratiode.min = 0;
	rm->ratiode.max = 4096;
	rm->ratiode.value = (rand() % 64) * (rand() % 8 + 1) * (rand() % 8 + 1);
	rm->ratiolo.min = 0;
	rm->ratiolo.max = 4096;
	rm->ratiolo.value = (rand() % 16) * (rand() % 8 + 1) * (rand() % 4 + 1);
	rm->ratioti.min = 0;
	rm->ratioti.max = 4096;
	rm->ratioti.value = (rand() % 8) * (rand() % 8 + 1);
	rm->ratioxi.min = 0;
	rm->ratioxi.max = 4096;
	rm->ratioxi.value = (rand() % 2) * (rand() % 8 + 1);
	rm->rnorooms.min = 0;
	rm->rnorooms.max = 4096;
	rm->rnorooms.value = (rm->width.value * rm->height.value / 64 + 1) * (rand() % ((rm->width.value + rm->height.value) / 16)) * (rand() % 8 + 1);
	rm->rorooms.min = 1;
	rm->rorooms.max = 4096;
	rm->rorooms.value = (rm->width.value * rm->height.value / 64 + 1) * (rand() % ((rm->width.value + rm->height.value) / 16)) * (rand() % 8 + 1);
	rm->rdoors.min = 0;
	rm->rdoors.max = 4096;
	rm->rdoors.value = (rand() % 8) * (rand() % 8) * (rand() % 8);
	rm->rdeadends.min = 0;
	rm->rdeadends.max = 4096;
	rm->rdeadends.value = (rand() % 12288);
	if (rm->rdeadends.value > 8192)
		rm->rdeadends.value = 0;
	if (rm->rdeadends.value > 4096)
		rm->rdeadends.value = 1;
	rm->flamingos.min = 0;
	rm->flamingos.max = 64;
	rm->flamingos.value = (rand() % 64);
}

void	ft_resume(t_max *max)
{
	max->game_mode = GAMEPLAY;
	max->i.menuscreen->enabled = 0;
	max->i.textscreen->enabled = 0;
	max->i.overlay->enabled = 1;
	mlx_set_mouse_pos(max->mlx, 512, 512);
}

void	ft_newgame(t_max *max)
{
	max->game_mode = GAMESTART;
	max->menu.current_button[MAINBUTTONS] = RESUME;
	max->menu.current_buttongroup = MAINBUTTONS;
	max->game_in_progress = 0;
	max->i.menuscreen->enabled = 0;
	max->i.textscreen->enabled = 1;
	max->gamems = 0;
	if (max->difficulty == EASY)
		max->score = 1000000;
	else if (max->difficulty == MEDIUM)
		max->score = 1500000;
	else if (max->difficulty == HARD)
		max->score = 2000000;
	mlx_set_mouse_pos(max->mlx, 512, 512);
	//level for campaign and timetrial???
	// max->i.overlay->enabled = 1;
}

void	ft_initmenu(t_max *max)
{
	max->menu.current_button[MAINBUTTONS] = NEWGAME;
	max->menu.background = max->t.menubg;
	max->menu.button = max->t.button;
	max->menu.buttonplus = max->t.buttonplus;
	max->menu.textfield = max->t.textfield;
	max->menu.listfield = max->t.listfield;
	max->font.asciitest = max->t.font;
	ft_initrandommapvalues(&max->menu.rm);
	ft_initbuttons(max);
	ft_inittextfields(max);
	ft_initlistfields(max);
	max->game_type = ONEMAP;
	max->menu.newmap = -1;
	max->menu.current_button[NEWSELECTION] = ONEMAP;
	max->menu.current_button[NEWLEVEL] = CUSTOM;
	max->difficulty = -1;
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
			mlx_put_pixel(max->i.menuscreen, x, y, c);
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
	if (max->game_in_progress)
		ft_draw_button(&max->menu.mainbuttons[SAVEGAME], ACTIVE);
	else
		ft_draw_button(&max->menu.mainbuttons[SAVEGAME], INACTIVE);
	if (max->menu.loads.files[0])
		ft_draw_button(&max->menu.mainbuttons[LOADGAME], ACTIVE);
	else
		ft_draw_button(&max->menu.mainbuttons[LOADGAME], INACTIVE);
	ft_draw_button(&max->menu.mainbuttons[SETTINGS], INACTIVE);
	ft_draw_button(&max->menu.mainbuttons[HALLOFFAME], ACTIVE);
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
		// ft_draw_button(&max->menu.newwritingbuttons[NWBACK], ACTIVE);
		ft_draw_button(&max->menu.newwritingbuttons[NWCONFIRM], ACTIVE);
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
	}
	//draw selection buttons
	if (max->menu.current_buttongroup == NEWSELECTION)
	{
		ft_draw_button(&max->menu.gametypebuttons[CAMPAIGN], ACTIVE);
		ft_draw_button(&max->menu.gametypebuttons[TIMETRIAL], ACTIVE);
		//maybe if else not needd
		ft_draw_button(&max->menu.gametypebuttons[ONEMAP], ACTIVE);
	}
	//draw level
	if (max->menu.current_buttongroup == NEWLEVEL)
	{
		//maybe if else not needed
		ft_draw_button(&max->menu.maptypebuttons[CUSTOM], ACTIVE);
		ft_draw_button(&max->menu.maptypebuttons[RANDOM], ACTIVE);
	}
		//draw newmap buttons
	if (max->menu.current_buttongroup == NEWMAP)
	{
		ft_draw_button(&max->menu.mapselectionbuttons[CHOOSELEVEL], ACTIVE);
		ft_draw_button(&max->menu.mapselectionbuttons[MSPLAY], ACTIVE);
	}
	//draw newmap listfield
	if (max->menu.current_buttongroup == NEWMAP)
	{
		//change if later
		ft_draw_listfield(&max->menu.custommap, ACTIVE);
	}
	if (max->menu.current_buttongroup == NEWRANDOM)
	{
		ft_draw_button(&max->menu.randomselectionbuttons[RSPLAY], ACTIVE);
		ft_draw_button(&max->menu.randomselectionbuttons[RSADVANCED], ACTIVE);
	}
	if (max->menu.current_buttongroup == NEWRANDOMADVANCED)
	{
		ft_draw_button(&max->menu.randomadvancedbuttons[RWIDTH], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RHEIGHT], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RRATIODE], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOLO], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOTI], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOXI], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RNOROOMS], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[ROROOMS], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RDOORS], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RDEADENDS], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RRANDOMIZE], ACTIVE);
		ft_draw_button(&max->menu.randomadvancedbuttons[RPLAY], ACTIVE);
	}
	if (max->menu.current_buttongroup == SAVEGROUP)
	{
		ft_draw_button(&max->menu.savegamebuttons[CHOOSESAVE], ACTIVE);
		ft_draw_button(&max->menu.savegamebuttons[DELETE], ACTIVE);
		ft_draw_button(&max->menu.savegamebuttons[SAVE], ACTIVE);
	}
	//draw newmap listfield
	if (max->menu.current_buttongroup == SAVEGROUP)
	{
		//change if later
		ft_draw_listfield(&max->menu.saves, ACTIVE);
	}
	if (max->menu.current_buttongroup == LOADGROUP)
	{
		ft_draw_button(&max->menu.loadgamebuttons[CHOOSELOAD], ACTIVE);
		ft_draw_button(&max->menu.loadgamebuttons[DELETE], ACTIVE);
		ft_draw_button(&max->menu.loadgamebuttons[LOAD], ACTIVE);
	}
	//draw newmap listfield
	if (max->menu.current_buttongroup == LOADGROUP)
	{
		//change if later
		ft_draw_listfield(&max->menu.loads, ACTIVE);
	}
	if (max->menu.current_buttongroup == HALLOFFAMEGROUP)
	{
		ft_draw_button(&max->menu.halloffamebuttons[HOFBACK], ACTIVE);
	}
	//draw optionbuttons
}

void	ft_selectnewbutton(t_max *max, t_button *button)
{
	if (max->keys[MLX_KEY_UP])
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
		max->keys[MLX_KEY_UP] = 0;
	}
	if (max->keys[MLX_KEY_DOWN])
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
		max->keys[MLX_KEY_DOWN] = 0;
	}
	if (max->keys[MLX_KEY_LEFT])
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
		max->keys[MLX_KEY_LEFT] = 0;
	}
	if (max->keys[MLX_KEY_RIGHT])
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
		max->keys[MLX_KEY_RIGHT] = 0;
	}
}

void	ft_selectbutton(t_max *max)
{
	if (max->menu.current_buttongroup == MAINBUTTONS)
	{
		ft_selectnewbutton(max, &max->menu.mainbuttons[max->menu.current_button[MAINBUTTONS]]);
	}
	else if (max->menu.current_buttongroup == NEWWRITING)
	{
		ft_selectnewbutton(max, &max->menu.newwritingbuttons[max->menu.current_button[NEWWRITING]]);
		// if (max->menu.newwriting == NAME)
		// {
		// 	ft_write_in_textfield(max, &max->menu.newwritingfields[NAME]);
		// }
		// else if (max->menu.newwriting == COALITION)
		// {
		// 	ft_write_in_textfield(max, &max->menu.newwritingfields[COALITION]);
		// }
		// else if (max->menu.newwriting == CAMPUS)
		// {
		// 	ft_write_in_textfield(max, &max->menu.newwritingfields[CAMPUS]);
		// }
		if (max->menu.current_button[NEWWRITING] == NAME)
		{
			ft_write_in_textfield(max, &max->menu.newwritingfields[NAME]);
			max->menu.newwriting = NAME;
			if (max->menu.newwritingfields[COALITION].text.highlight >= 0)
			{
				max->menu.newwritingfields[COALITION].text.text[max->menu.newwritingfields[COALITION].text.highlight] = '\0';
				max->menu.newwritingfields[COALITION].text.highlight = -1;
			}
			if (max->menu.newwritingfields[CAMPUS].text.highlight >= 0)
			{
				max->menu.newwritingfields[CAMPUS].text.text[max->menu.newwritingfields[CAMPUS].text.highlight] = '\0';
				max->menu.newwritingfields[CAMPUS].text.highlight = -1;
			}
		}
		else if (max->menu.current_button[NEWWRITING]  == COALITION)
		{
			ft_write_in_textfield(max, &max->menu.newwritingfields[COALITION]);
			max->menu.newwriting = COALITION;
			if (max->menu.newwritingfields[NAME].text.highlight >= 0)
			{
				max->menu.newwritingfields[NAME].text.text[max->menu.newwritingfields[NAME].text.highlight] = '\0';
				max->menu.newwritingfields[NAME].text.highlight = -1;
			}
			if (max->menu.newwritingfields[CAMPUS].text.highlight >= 0)
			{
				max->menu.newwritingfields[CAMPUS].text.text[max->menu.newwritingfields[CAMPUS].text.highlight] = '\0';
				max->menu.newwritingfields[CAMPUS].text.highlight = -1;
			}
		}
		else if (max->menu.current_button[NEWWRITING]  == CAMPUS)
		{
			ft_write_in_textfield(max, &max->menu.newwritingfields[CAMPUS]);
			max->menu.newwriting = CAMPUS;
			if (max->menu.newwritingfields[NAME].text.highlight >= 0)
			{
				max->menu.newwritingfields[NAME].text.text[max->menu.newwritingfields[NAME].text.highlight] = '\0';
				max->menu.newwritingfields[NAME].text.highlight = -1;
			}
			if (max->menu.newwritingfields[COALITION].text.highlight >= 0)
			{
				max->menu.newwritingfields[COALITION].text.text[max->menu.newwritingfields[COALITION].text.highlight] = '\0';
				max->menu.newwritingfields[COALITION].text.highlight = -1;
			}
		}
		else
		{
			{
				max->menu.newwritingfields[NAME].text.text[max->menu.newwritingfields[NAME].text.highlight] = '\0';
				max->menu.newwritingfields[NAME].text.highlight = -1;
			}
			if (max->menu.newwritingfields[COALITION].text.highlight >= 0)
			{
				max->menu.newwritingfields[COALITION].text.text[max->menu.newwritingfields[COALITION].text.highlight] = '\0';
				max->menu.newwritingfields[COALITION].text.highlight = -1;
			}
			if (max->menu.newwritingfields[CAMPUS].text.highlight >= 0)
			{
				max->menu.newwritingfields[CAMPUS].text.text[max->menu.newwritingfields[CAMPUS].text.highlight] = '\0';
				max->menu.newwritingfields[CAMPUS].text.highlight = -1;
			}
			max->menu.newwriting = -1;
		}
		
	}
	else if (max->menu.current_buttongroup == NEWDIFFICULTY)
	{
		ft_selectnewbutton(max, &max->menu.gamedifficultybuttons[max->menu.current_button[NEWDIFFICULTY]]);
	}
	else if (max->menu.current_buttongroup == NEWSELECTION)
	{
		ft_selectnewbutton(max, &max->menu.gametypebuttons[max->menu.current_button[NEWSELECTION]]);
	}
	else if (max->menu.current_buttongroup == NEWLEVEL)
	{
		ft_selectnewbutton(max, &max->menu.maptypebuttons[max->menu.current_button[NEWLEVEL]]);
	}
	else if (max->menu.current_buttongroup == NEWMAP)
	{
		if (max->menu.lf_state)
		{
			ft_choose_in_listfield(max, &max->menu.custommap);
			return ;
		}
		ft_selectnewbutton(max, &max->menu.mapselectionbuttons[max->menu.current_button[NEWMAP]]);
	}
	else if (max->menu.current_buttongroup == NEWRANDOM)
	{
		ft_selectnewbutton(max, &max->menu.randomselectionbuttons[max->menu.current_button[NEWRANDOM]]);
	}
	else if (max->menu.current_buttongroup == NEWRANDOMADVANCED)
	{
		if (max->menu.random_state[RWIDTH])
		{
			ft_choose_in_button(max, &max->menu.randomadvancedbuttons[RWIDTH]);
			return ;
		}
		else if (max->menu.random_state[RHEIGHT])
		{
			ft_choose_in_button(max, &max->menu.randomadvancedbuttons[RHEIGHT]);
			return ;
		}
		else if (max->menu.random_state[RRATIODE])
		{
			ft_choose_in_button(max, &max->menu.randomadvancedbuttons[RRATIODE]);
			return ;
		}
		else if (max->menu.random_state[RRATIOLO])
		{
			ft_choose_in_button(max, &max->menu.randomadvancedbuttons[RRATIOLO]);
			return ;
		}
		else if (max->menu.random_state[RRATIOTI])
		{
			ft_choose_in_button(max, &max->menu.randomadvancedbuttons[RRATIOTI]);
			return ;
		}
		else if (max->menu.random_state[RRATIOXI])
		{
			ft_choose_in_button(max, &max->menu.randomadvancedbuttons[RRATIOXI]);
			return ;
		}
		else if (max->menu.random_state[RNOROOMS])
		{
			ft_choose_in_button(max, &max->menu.randomadvancedbuttons[RNOROOMS]);
			return ;
		}
		else if (max->menu.random_state[ROROOMS])
		{
			ft_choose_in_button(max, &max->menu.randomadvancedbuttons[ROROOMS]);
			return ;
		}
		else if (max->menu.random_state[RDOORS])
		{
			ft_choose_in_button(max, &max->menu.randomadvancedbuttons[RDOORS]);
			return ;
		}
		else if (max->menu.random_state[RDEADENDS])
		{
			ft_choose_in_button(max, &max->menu.randomadvancedbuttons[RDEADENDS]);
			return ;
		}
		ft_selectnewbutton(max, &max->menu.randomadvancedbuttons[max->menu.current_button[NEWRANDOMADVANCED]]);
	}
	else if (max->menu.current_buttongroup == SAVEGROUP)
	{
		if (max->menu.lf_state)
		{
			ft_choose_in_listfield(max, &max->menu.saves);
			return ;
		}
		ft_selectnewbutton(max, &max->menu.savegamebuttons[max->menu.current_button[SAVEGROUP]]);
	}
	else if (max->menu.current_buttongroup == LOADGROUP)
	{
		if (max->menu.lf_state)
		{
			ft_choose_in_listfield(max, &max->menu.loads);
			return ;
		}
		ft_selectnewbutton(max, &max->menu.loadgamebuttons[max->menu.current_button[LOADGROUP]]);
	}
	else if (max->menu.current_buttongroup == HALLOFFAMEGROUP)
	{
		ft_selectnewbutton(max, &max->menu.halloffamebuttons[max->menu.current_button[HALLOFFAME]]);
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
	if (max->menu.current_button[MAINBUTTONS] == SAVEGAME)
	{
		if (max->menu.current_buttongroup == MAINBUTTONS)
			ft_draw_button(&max->menu.mainbuttons[SAVEGAME], SELECTED);
		else
			ft_draw_button(&max->menu.mainbuttons[SAVEGAME], ACTIVATED);
	}
	if (max->menu.current_button[MAINBUTTONS] == LOADGAME)
	{
		if (max->menu.current_buttongroup == MAINBUTTONS)
			ft_draw_button(&max->menu.mainbuttons[LOADGAME], SELECTED);
		else
			ft_draw_button(&max->menu.mainbuttons[LOADGAME], ACTIVATED);
	}
	if (max->menu.current_button[MAINBUTTONS] == HALLOFFAME)
	{
		if (max->menu.current_buttongroup == MAINBUTTONS)
			ft_draw_button(&max->menu.mainbuttons[HALLOFFAME], SELECTED);
		else
			ft_draw_button(&max->menu.mainbuttons[HALLOFFAME], ACTIVATED);
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
	else if (max->menu.current_button[NEWWRITING] == NWCONFIRM)
	{
		ft_draw_button(&max->menu.newwritingbuttons[NWCONFIRM], SELECTED);
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
}

void	ft_draw_newmapbuttons(t_max *max)
{
	if (max->menu.current_button[NEWMAP] == CHOOSELEVEL)
	{
		if (max->menu.lf_state)
			ft_draw_button(&max->menu.mapselectionbuttons[CHOOSELEVEL], ACTIVATED);
		else
			ft_draw_button(&max->menu.mapselectionbuttons[CHOOSELEVEL], SELECTED);
	}
	else if (max->menu.current_button[NEWMAP] == MSPLAY)
	{
		ft_draw_button(&max->menu.mapselectionbuttons[MSPLAY], SELECTED);
	}
}

void	ft_draw_newmaplistfields(t_max *max)
{
	if (max->menu.lf_state)
		ft_draw_listfield(&max->menu.custommap, ACTIVATED);
	else
		ft_draw_listfield(&max->menu.custommap, SELECTED);
}

void	ft_draw_newrandombuttons(t_max *max)
{
	if (max->menu.current_button[NEWRANDOM] == RSPLAY)
	{
		ft_draw_button(&max->menu.randomselectionbuttons[RSPLAY], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOM] == RSADVANCED)
	{
		ft_draw_button(&max->menu.randomselectionbuttons[RSADVANCED], SELECTED);
	}
}



void	ft_updatenewrandomadvancedbuttons(t_max	*max)
{
	t_button	*but;

	but = &max->menu.randomadvancedbuttons[RWIDTH];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RHEIGHT];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RRATIODE];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RRATIOLO];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RRATIOTI];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RRATIOXI];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RNOROOMS];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[ROROOMS];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RDOORS];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
	but = &max->menu.randomadvancedbuttons[RDEADENDS];
	ft_snprintf(but->text.str, 19, "%s: %i", but->str, but->val->value);
}

void	ft_draw_newrandomadvancedbuttons(t_max *max)
{
	ft_updatenewrandomadvancedbuttons(max);
	if (max->menu.current_button[NEWRANDOMADVANCED] == RWIDTH)
	{
		if (max->menu.random_state[RWIDTH])
			ft_draw_button(&max->menu.randomadvancedbuttons[RWIDTH], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RWIDTH], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RHEIGHT)
	{
		if (max->menu.random_state[RHEIGHT])
			ft_draw_button(&max->menu.randomadvancedbuttons[RHEIGHT], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RHEIGHT], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIODE)
	{
		if (max->menu.random_state[RRATIODE])
			ft_draw_button(&max->menu.randomadvancedbuttons[RRATIODE], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RRATIODE], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIOLO)
	{
		if (max->menu.random_state[RRATIOLO])
			ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOLO], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOLO], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIOTI)
	{
		if (max->menu.random_state[RRATIOTI])
			ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOTI], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOTI], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIOXI)
	{
		if (max->menu.random_state[RRATIOXI])
			ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOXI], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RRATIOXI], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RNOROOMS)
	{
		if (max->menu.random_state[RNOROOMS])
			ft_draw_button(&max->menu.randomadvancedbuttons[RNOROOMS], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RNOROOMS], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == ROROOMS)
	{
		if (max->menu.random_state[ROROOMS])
			ft_draw_button(&max->menu.randomadvancedbuttons[ROROOMS], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[ROROOMS], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RDOORS)
	{
		if (max->menu.random_state[RDOORS])
			ft_draw_button(&max->menu.randomadvancedbuttons[RDOORS], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RDOORS], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RDEADENDS)
	{
		if (max->menu.random_state[RDEADENDS])
			ft_draw_button(&max->menu.randomadvancedbuttons[RDEADENDS], ACTIVATED);
		else
			ft_draw_button(&max->menu.randomadvancedbuttons[RDEADENDS], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RRANDOMIZE)
	{
		ft_draw_button(&max->menu.randomadvancedbuttons[RRANDOMIZE], SELECTED);
	}
	else if (max->menu.current_button[NEWRANDOMADVANCED] == RPLAY)
	{
		ft_draw_button(&max->menu.randomadvancedbuttons[RPLAY], SELECTED);
	}
}

void	ft_draw_savebuttons(t_max *max)
{
	if (max->menu.current_button[SAVEGROUP] == CHOOSESAVE)
	{
		if (max->menu.lf_state)
			ft_draw_button(&max->menu.savegamebuttons[CHOOSESAVE], ACTIVATED);
		else
			ft_draw_button(&max->menu.savegamebuttons[CHOOSESAVE], SELECTED);
	}
	else if (max->menu.current_button[SAVEGROUP] == DELETE)
	{
		ft_draw_button(&max->menu.savegamebuttons[DELETE], SELECTED);
	}
	else if (max->menu.current_button[SAVEGROUP] == SAVE)
	{
		ft_draw_button(&max->menu.savegamebuttons[SAVE], SELECTED);
	}
}

void	ft_draw_savelistfields(t_max *max)
{
	if (max->menu.lf_state)
		ft_draw_listfield(&max->menu.saves, ACTIVATED);
	else
		ft_draw_listfield(&max->menu.saves, SELECTED);
}

void	ft_draw_loadbuttons(t_max *max)
{
	if (max->menu.current_button[LOADGROUP] == CHOOSELOAD)
	{
		if (max->menu.lf_state)
			ft_draw_button(&max->menu.loadgamebuttons[CHOOSELOAD], ACTIVATED);
		else
			ft_draw_button(&max->menu.loadgamebuttons[CHOOSELOAD], SELECTED);
	}
	else if (max->menu.current_button[LOADGROUP] == DELETE)
	{
		ft_draw_button(&max->menu.loadgamebuttons[DELETE], SELECTED);
	}
	else if (max->menu.current_button[LOADGROUP] == LOAD)
	{
		ft_draw_button(&max->menu.loadgamebuttons[LOAD], SELECTED);
	}
}

void	ft_draw_loadlistfields(t_max *max)
{
	if (max->menu.lf_state)
		ft_draw_listfield(&max->menu.loads, ACTIVATED);
	else
		ft_draw_listfield(&max->menu.loads, SELECTED);
}

void	ft_draw_halloffamebuttons(t_max *max)
{
	//ft_draw_halloffame(max);
	if (max->menu.current_button[HALLOFFAMEGROUP] == HOFBACK)
	{
		ft_draw_button(&max->menu.halloffamebuttons[HOFBACK], SELECTED);
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
	}
	if (max->menu.current_buttongroup == NEWRANDOMADVANCED)
	{
		ft_draw_newrandomadvancedbuttons(max);
	}
	if (max->menu.current_buttongroup == SAVEGROUP)
	{
		ft_draw_savebuttons(max);
		ft_draw_savelistfields(max);
	}
	if (max->menu.current_buttongroup == LOADGROUP)
	{
		ft_draw_loadbuttons(max);
		ft_draw_loadlistfields(max);
	}
	if (max->menu.current_buttongroup == HALLOFFAMEGROUP)
	{
		ft_draw_halloffamebuttons(max);
	}
	if (max->keys[MLX_KEY_BACKSPACE])
	{
		if (max->menu.current_buttongroup)
			--max->menu.current_buttongroup;
		max->keys[MLX_KEY_BACKSPACE] = 0;
	}
	if (max->keys[MLX_KEY_ENTER])
	{
		max->keys[MLX_KEY_ENTER] = 0;
		if (max->menu.current_button[MAINBUTTONS] == RESUME)
		{
			ft_resume(max);
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
						max->menu.newwriting = COALITION;
						max->menu.newwritingfields[NAME].text.text[max->menu.newwritingfields[NAME].text.highlight] = '\0';
						max->menu.newwritingfields[NAME].text.highlight = -1;
						max->menu.current_button[NEWWRITING] = COALITION;
					}
					else
						max->menu.newwriting = NAME;
				}
				else if (max->menu.current_button[NEWWRITING] == COALITION)
				{
					if (max->menu.newwriting == COALITION)
					{
						max->menu.newwriting = CAMPUS;
						max->menu.newwritingfields[COALITION].text.text[max->menu.newwritingfields[COALITION].text.highlight] = '\0';
						max->menu.newwritingfields[COALITION].text.highlight = -1;
						max->menu.current_button[NEWWRITING] = CAMPUS;
					}
					else
						max->menu.newwriting = COALITION;
				}
				else if (max->menu.current_button[NEWWRITING] == CAMPUS)
				{
					if (max->menu.newwriting == CAMPUS)
					{
						max->menu.newwriting = -1;
						max->menu.newwritingfields[CAMPUS].text.text[max->menu.newwritingfields[CAMPUS].text.highlight] = '\0';
						max->menu.newwritingfields[CAMPUS].text.highlight = -1;
						max->menu.current_button[NEWWRITING] = NWCONFIRM;
					}
					else
						max->menu.newwriting = CAMPUS;
				}
				else if (max->menu.current_button[NEWWRITING] == NWCONFIRM)
				{
					max->menu.current_buttongroup = NEWDIFFICULTY;
					printf("%s\n%s\n%s\n", max->name, max->coalition, max->campus);
				}
			}
			else if (max->menu.current_buttongroup == NEWDIFFICULTY)
			{
				if (max->menu.current_button[NEWDIFFICULTY] == EASY)
				{
					max->difficulty = EASY;
					max->menu.current_buttongroup = NEWSELECTION;
				}
				else if (max->menu.current_button[NEWDIFFICULTY] == MEDIUM)
				{
					max->difficulty = MEDIUM;
					max->menu.current_buttongroup = NEWSELECTION;
				}
				else if (max->menu.current_button[NEWDIFFICULTY] == HARD)
				{
					max->difficulty = HARD;
					max->menu.current_buttongroup = NEWSELECTION;
				}
			}
			else if (max->menu.current_buttongroup == NEWSELECTION)
			{
				if (max->menu.current_button[NEWSELECTION] == CAMPAIGN)
				{
					max->game_type = CAMPAIGN;
					max->level = 1;
					max->gamems = 0;
					ft_sprintf(max->campaignmap, "./campaign/map%i.cub", max->level);
					ft_snprintf(max->map.file, 4095, max->campaignmap);
					if (ft_process_file(max))
					{
						printf("gamestart loop starting...\n");
						ft_newgame(max);
					}
					else
					{
						ft_dprintf(2, "Invalid map\n");
					}
				}
				else if (max->menu.current_button[NEWSELECTION] == TIMETRIAL)
				{
					max->game_type = TIMETRIAL;
					max->level = 1;
					max->gamems = 0;
					max->timetriallimitms = 120000;
					ft_inittimetrialmap(&max->menu.rm, max->level);
					ft_snprintf(max->map.file, 4095, "RANDOM");
					if (ft_process_random(max))
					{
						printf("gamestart loop starting...\n");
						ft_newgame(max);
					}
					else
					{
						ft_dprintf(2, "Invalid map\n");
					}
				}
				else if (max->menu.current_button[NEWSELECTION] == ONEMAP)
				{
					max->game_type = ONEMAP;
					max->menu.current_buttongroup = NEWLEVEL;
				}
			}
			else if (max->menu.current_buttongroup == NEWLEVEL)
			{
				if (max->menu.current_button[NEWLEVEL] == CUSTOM)
				{
					max->menu.current_buttongroup = NEWMAP;
					ft_bigreinitlistfield(max);
					max->menu.current_button[NEWMAP] = CUSTOM;
					max->menu.lf_state = 1;
				}
				else if (max->menu.current_button[NEWLEVEL] == RANDOM)
				{
					max->menu.current_buttongroup = NEWRANDOM;
				}
			}
			else if (max->menu.current_buttongroup == NEWMAP)
			{
				if (max->menu.current_button[NEWMAP] == CUSTOM)
				{
					if (max->menu.lf_state)
					{
						max->menu.lf_state = 0;
						max->menu.current_button[NEWMAP] = MSPLAY;
					}
					else
					{
						max->menu.lf_state = 1;
					}
				}
				else if (max->menu.current_button[NEWMAP] == MSPLAY)
				{
					//simplify?
					ft_snprintf(max->map.file, 4095, "%s%s", max->menu.custommap.dir, max->menu.custommap.text[max->menu.custommap.highlight].text);
					if (ft_process_file(max))
					{
						printf("gamestart loop starting...\n");
						ft_newgame(max);
					}
					else
					{
						max->menu.current_button[NEWMAP] = CUSTOM;
						max->menu.lf_state = 1;
						ft_dprintf(2, "Invalid map %s\n", max->map.file);
					}
				}
			}
			//
			// THIS NEEDS UPDATES to check which button is pressed and change its state
			//
			else if (max->menu.current_buttongroup == NEWRANDOM)
			{
				if (max->menu.current_button[NEWRANDOM] == RSPLAY)
				{
					ft_snprintf(max->map.file, 4095, "RANDOM");
					ft_initrandommapvalues(&max->menu.rm);
					if (ft_process_random(max))
					{
						printf("gamestart loop starting...\n");
						ft_newgame(max);
					}
					else
					{
						ft_dprintf(2, "Invalid map\n");
					}
				}
				else if (max->menu.current_button[NEWRANDOM] == RSADVANCED)
				{
					max->menu.current_buttongroup = NEWRANDOMADVANCED;
				}
			}
			else if (max->menu.current_buttongroup == NEWRANDOMADVANCED)
			{
				if (max->menu.current_button[NEWRANDOMADVANCED] == RWIDTH)
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
				else if (max->menu.current_button[NEWRANDOMADVANCED] == RHEIGHT)
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
				else if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIODE)
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
				else if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIOLO)
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
				else if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIOTI)
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
				else if (max->menu.current_button[NEWRANDOMADVANCED] == RRATIOXI)
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
				else if (max->menu.current_button[NEWRANDOMADVANCED] == RNOROOMS)
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
				else if (max->menu.current_button[NEWRANDOMADVANCED] == ROROOMS)
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
				else if (max->menu.current_button[NEWRANDOMADVANCED] == RDOORS)
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
				else if (max->menu.current_button[NEWRANDOMADVANCED] == RDEADENDS)
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
				else if (max->menu.current_button[NEWRANDOMADVANCED] == RRANDOMIZE)
				{
					ft_initrandommapvalues(&max->menu.rm);
				}
				else if (max->menu.current_button[NEWRANDOMADVANCED] == RPLAY)
				{
					//max->menu.current_button[NEWLEVEL] = max->menu.newmap;
					ft_snprintf(max->map.file, 4095, "RANDOM");
					if (ft_process_random(max))
					{
						printf("gamestart loop starting...\n");
						ft_newgame(max);
					}
					else
					{
						ft_dprintf(2, "Invalid map\n");
					}
				}
			}
		}
		if (max->menu.current_button[MAINBUTTONS] == SAVEGAME)
		{
			if (max->menu.current_buttongroup == MAINBUTTONS)
			{
				max->menu.current_buttongroup = SAVEGROUP;
				ft_bigreinitlistfield(max);
				max->menu.lf_state = 1;
				max->menu.current_button[SAVEGROUP] = CHOOSESAVE;
			}
			else if (max->menu.current_buttongroup == SAVEGROUP)
			{
				if (max->menu.current_button[SAVEGROUP] == CHOOSESAVE)
				{
					if (max->menu.lf_state)
					{
						max->menu.lf_state = 0;
						max->menu.current_button[SAVEGROUP] = SAVE;
					}
					else
					{
						max->menu.lf_state = 1;
					}
				}
				else if (max->menu.current_button[SAVEGROUP] == SAVE)
				{
					//save game
					if (max->menu.saves.text[max->menu.saves.highlight].text[0] == 'N')
						ft_snprintf(max->map.file, 4095, "%s%s%03i.ft", max->menu.saves.dir, "save", max->menu.saves.highlight + max->menu.saves.topfile + 1);
					else
						ft_snprintf(max->map.file, 4095, "%s%s", max->menu.saves.dir, max->menu.saves.text[max->menu.saves.highlight].text);
					if (ft_save(max, max->map.file))
						ft_dprintf(2, "Unable to save the game, make sure the safe file has proper permissions\n");
					max->menu.current_buttongroup = MAINBUTTONS;
					ft_bigreinitlistfield(max);
				}
				else if (max->menu.current_button[SAVEGROUP] == DELETE)
				{
					//delete game
				}
			}
			
		}
		if (max->menu.current_button[MAINBUTTONS] == LOADGAME)
		{
			if (max->menu.current_buttongroup == MAINBUTTONS)
			{
				max->menu.current_buttongroup = LOADGROUP;
				ft_bigreinitlistfield(max);
				max->menu.lf_state = 1;
				max->menu.current_button[LOADGROUP] = CHOOSELOAD;
			}
			else if (max->menu.current_buttongroup == LOADGROUP)
			{
				if (max->menu.current_button[LOADGROUP] == CHOOSELOAD)
				{
					if (max->menu.lf_state)
					{
						max->menu.lf_state = 0;
						max->menu.current_button[LOADGROUP] = LOAD;
					}
					else
					{
						max->menu.lf_state = 1;
					}
				}
				else if (max->menu.current_button[LOADGROUP] == LOAD)
				{
					//load game
					//ft_snprintf(max->map.file, 4095, "%s%s", max->menu.custommap.dir, max->menu.custommap.text[max->menu.custommap.highlight].text);
					ft_snprintf(max->map.file, 4095, "%s%s", max->menu.loads.dir, max->menu.loads.text[max->menu.loads.highlight].text);
					if (ft_load(max, max->map.file))
					{
						ft_dprintf(2, "Unable to load the game, make sure the safe file exists\n");
						max->menu.current_buttongroup = MAINBUTTONS;
					}
					else
					{
						max->menu.current_buttongroup = MAINBUTTONS;
						max->game_in_progress = 1;
						max->i.menuscreen->enabled = 0;
						max->i.textscreen->enabled = 0;
						max->game_mode = GAMEPLAY;
						max->i.overlay->enabled = 1;
						max->game_in_progress = 1;
						max->oldms = ft_get_time_in_ms();
					}
				}
				else if (max->menu.current_button[LOADGROUP] == DELETE)
				{
					//delete game
				}
			}
			
		}
		if (max->menu.current_button[MAINBUTTONS] == HALLOFFAME)
		{
			//delete the HOF BUTTON and HALLOFFAMEBUTTONGROUP? and related drawing functions
			
			if (!ft_readscore(max))
			{
				max->game_mode = HOFLOOP;
				max->i.textscreen->enabled = 1;
			}
			else
			{
				ft_dprintf(2, "Error\nFailed to open halloffame.txt\n");
			}
			// if (max->menu.current_buttongroup == HALLOFFAMEGROUP)
			// {
			// 	if (max->menu.current_button[HALLOFFAMEGROUP] == HOFBACK)
			// 	{
			// 		max->menu.current_buttongroup = MAINBUTTONS;
			// 	}
			// }
			// else
			// {
			// 	max->menu.current_buttongroup = HALLOFFAMEGROUP;
			// }
		}
		if (max->menu.current_button[MAINBUTTONS] == QUITGAME)
		{
			mlx_close_window(max->mlx);
		}
	}
}
