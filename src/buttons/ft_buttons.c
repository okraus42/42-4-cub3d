/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:42:26 by okraus            #+#    #+#             */
/*   Updated: 2024/05/09 14:44:42 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

t_text	ft_inittext_helper(t_max *max)
{
	t_text		text;

	ft_bzero(&text, sizeof(text));
	text.font = max->font.asciitest;
	text.image = max->i.menuscreen;
	text.text = "VOID";
	text.c = 0XFF;
	text.cb = 0;
	text.sx = 0;
	text.sy = 0;
	text.x = 0;
	text.y = 0;
	text.height = 60;
	text.highlight = -1;
	text.i = 0;
	text.offset = 0;
	return (text);
}

t_button	ft_initbutton_helper(t_max *max)
{
	t_button	button;

	ft_bzero(&button, sizeof(button));
	button.button = max->menu.button;
	button.image = max->i.menuscreen;
	button.text = ft_inittext_helper(max);
	button.c = C_INACTIVE;
	button.x = 200;
	button.y = 0;
	button.w = 350;
	button.h = 150;
	button.state = INACTIVE;
	return (button);
}

void	ft_initbutton_resume(t_max *max)
{
	max->menu.mainbuttons[RESUME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[RESUME].id = RESUME;
	max->menu.mainbuttons[RESUME].group = MAINBUTTONS;
	max->menu.mainbuttons[RESUME].down = &max->menu.mainbuttons[NEWGAME];
	max->menu.mainbuttons[RESUME].y = 20;
	max->menu.mainbuttons[RESUME].text.text = S_RESUME;
	max->menu.mainbuttons[RESUME].text.sx = max->menu
		.mainbuttons[RESUME].x + 40;
	max->menu.mainbuttons[RESUME].text.sy = max->menu
		.mainbuttons[RESUME].y + 40;
}

void	ft_initbutton_newgame(t_max *max)
{
	max->menu.mainbuttons[NEWGAME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[NEWGAME].id = NEWGAME;
	max->menu.mainbuttons[NEWGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[NEWGAME].up = &max->menu.mainbuttons[RESUME];
	max->menu.mainbuttons[NEWGAME].down = &max->menu.mainbuttons[SAVEGAME];
	max->menu.mainbuttons[NEWGAME].state = SELECTED;
	max->menu.mainbuttons[NEWGAME].y = 160;
	max->menu.mainbuttons[NEWGAME].text.text = S_NEWGAME;
	max->menu.mainbuttons[NEWGAME].text.sx = max->menu
		.mainbuttons[NEWGAME].x + 40;
	max->menu.mainbuttons[NEWGAME].text.sy = max->menu
		.mainbuttons[NEWGAME].y + 40;
}

void	ft_initbutton_savegame(t_max *max)
{
	max->menu.mainbuttons[SAVEGAME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[SAVEGAME].id = SAVEGAME;
	max->menu.mainbuttons[SAVEGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[SAVEGAME].up = &max->menu.mainbuttons[NEWGAME];
	max->menu.mainbuttons[SAVEGAME].down = &max->menu.mainbuttons[LOADGAME];
	max->menu.mainbuttons[SAVEGAME].y = 300;
	max->menu.mainbuttons[SAVEGAME].text.text = S_SAVEGAME;
	max->menu.mainbuttons[SAVEGAME].text.sx = max->menu
		.mainbuttons[SAVEGAME].x + 40;
	max->menu.mainbuttons[SAVEGAME].text.sy = max->menu
		.mainbuttons[SAVEGAME].y + 40;
}

void	ft_initbutton_loadgame(t_max *max)
{
	max->menu.mainbuttons[LOADGAME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[LOADGAME].id = LOADGAME;
	max->menu.mainbuttons[LOADGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[LOADGAME].up = &max->menu.mainbuttons[SAVEGAME];
	max->menu.mainbuttons[LOADGAME].down = &max->menu.mainbuttons[SETTINGS];
	max->menu.mainbuttons[LOADGAME].y = 440;
	max->menu.mainbuttons[LOADGAME].text.text = S_LOADGAME;
	max->menu.mainbuttons[LOADGAME].text.sx = max->menu
		.mainbuttons[LOADGAME].x + 40;
	max->menu.mainbuttons[LOADGAME].text.sy = max->menu
		.mainbuttons[LOADGAME].y + 40;
}

void	ft_initbutton_settings(t_max *max)
{
	max->menu.mainbuttons[SETTINGS] = ft_initbutton_helper(max);
	max->menu.mainbuttons[SETTINGS].id = SETTINGS;
	max->menu.mainbuttons[SETTINGS].group = MAINBUTTONS;
	max->menu.mainbuttons[SETTINGS].up = &max->menu.mainbuttons[LOADGAME];
	max->menu.mainbuttons[SETTINGS].down = &max->menu.mainbuttons[HALLOFFAME];
	max->menu.mainbuttons[SETTINGS].y = 580;
	max->menu.mainbuttons[SETTINGS].text.text = S_SETTINGS;
	max->menu.mainbuttons[SETTINGS].text.sx = max->menu
		.mainbuttons[SETTINGS].x + 40;
	max->menu.mainbuttons[SETTINGS].text.sy = max->menu
		.mainbuttons[SETTINGS].y + 40;
}

void	ft_initbutton_halloffame(t_max *max)
{
	max->menu.mainbuttons[HALLOFFAME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[HALLOFFAME].id = HALLOFFAME;
	max->menu.mainbuttons[HALLOFFAME].group = MAINBUTTONS;
	max->menu.mainbuttons[HALLOFFAME].up = &max->menu.mainbuttons[SETTINGS];
	max->menu.mainbuttons[HALLOFFAME].down = &max->menu.mainbuttons[QUITGAME];
	max->menu.mainbuttons[HALLOFFAME].state = ACTIVE;
	max->menu.mainbuttons[HALLOFFAME].y = 720;
	max->menu.mainbuttons[HALLOFFAME].text.text = S_HALLOFFAME;
	max->menu.mainbuttons[HALLOFFAME].text.sx = max->menu
		.mainbuttons[HALLOFFAME].x + 40;
	max->menu.mainbuttons[HALLOFFAME].text.sy = max->menu
		.mainbuttons[HALLOFFAME].y + 40;
	max->menu.mainbuttons[HALLOFFAME].text.height = 40;
}

void	ft_initbutton_quitgame(t_max *max)
{
	max->menu.mainbuttons[QUITGAME] = ft_initbutton_helper(max);
	max->menu.mainbuttons[QUITGAME].id = QUITGAME;
	max->menu.mainbuttons[QUITGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[QUITGAME].up = &max->menu.mainbuttons[HALLOFFAME];
	max->menu.mainbuttons[QUITGAME].state = ACTIVE;
	max->menu.mainbuttons[QUITGAME].y = 860;
	max->menu.mainbuttons[QUITGAME].text.text = S_QUITGAME;
	max->menu.mainbuttons[QUITGAME].text.sx = max->menu
		.mainbuttons[QUITGAME].x + 40;
	max->menu.mainbuttons[QUITGAME].text.sy = max->menu
		.mainbuttons[QUITGAME].y + 40;
}

void	ft_initbutton_name(t_max *max)
{
	max->menu.newwritingbuttons[NAME] = ft_initbutton_helper(max);
	max->menu.newwritingbuttons[NAME].id = NAME;
	max->menu.newwritingbuttons[NAME].group = NEWWRITING;
	max->menu.newwritingbuttons[NAME].down = &max->menu
		.newwritingbuttons[COALITION];
	max->menu.newwritingbuttons[NAME].state = ACTIVE;
	max->menu.newwritingbuttons[NAME].x = 600;
	max->menu.newwritingbuttons[NAME].y = 20;
	max->menu.newwritingbuttons[NAME].text.text = S_NAME;
	max->menu.newwritingbuttons[NAME].text.sx = max->menu
		.newwritingbuttons[NAME].x + 40;
	max->menu.newwritingbuttons[NAME].text.sy = max->menu
		.newwritingbuttons[NAME].y + 40;
}

void	ft_initbutton_coalition(t_max *max)
{
	max->menu.newwritingbuttons[COALITION] = ft_initbutton_helper(max);
	max->menu.newwritingbuttons[COALITION].id = COALITION;
	max->menu.newwritingbuttons[COALITION].group = NEWWRITING;
	max->menu.newwritingbuttons[COALITION].up = &max->menu
		.newwritingbuttons[NAME];
	max->menu.newwritingbuttons[COALITION].down = &max->menu
		.newwritingbuttons[CAMPUS];
	max->menu.newwritingbuttons[COALITION].state = ACTIVE;
	max->menu.newwritingbuttons[COALITION].x = 600;
	max->menu.newwritingbuttons[COALITION].y = 300;
	max->menu.newwritingbuttons[COALITION].text.text = S_COALITION;
	max->menu.newwritingbuttons[COALITION].text.sx = max->menu
		.newwritingbuttons[COALITION].x + 40;
	max->menu.newwritingbuttons[COALITION].text.sy = max->menu
		.newwritingbuttons[COALITION].y + 40;
}

void	ft_initbutton_campus(t_max *max)
{
	max->menu.newwritingbuttons[CAMPUS] = ft_initbutton_helper(max);
	max->menu.newwritingbuttons[CAMPUS].id = CAMPUS;
	max->menu.newwritingbuttons[CAMPUS].group = NEWWRITING;
	max->menu.newwritingbuttons[CAMPUS].up = &max->menu
		.newwritingbuttons[COALITION];
	max->menu.newwritingbuttons[CAMPUS].down = &max->menu
		.newwritingbuttons[NWCONFIRM];
	max->menu.newwritingbuttons[CAMPUS].state = ACTIVE;
	max->menu.newwritingbuttons[CAMPUS].x = 600;
	max->menu.newwritingbuttons[CAMPUS].y = 580;
	max->menu.newwritingbuttons[CAMPUS].text.text = S_CAMPUS;
	max->menu.newwritingbuttons[CAMPUS].text.sx = max->menu
		.newwritingbuttons[CAMPUS].x + 40;
	max->menu.newwritingbuttons[CAMPUS].text.sy = max->menu
		.newwritingbuttons[CAMPUS].y + 40;
}

void	ft_initbutton_nwconfirm(t_max *max)
{
	max->menu.newwritingbuttons[NWCONFIRM] = ft_initbutton_helper(max);
	max->menu.newwritingbuttons[NWCONFIRM].id = NWCONFIRM;
	max->menu.newwritingbuttons[NWCONFIRM].group = NEWWRITING;
	max->menu.newwritingbuttons[NWCONFIRM].up = &max->menu
		.newwritingbuttons[CAMPUS];
	max->menu.newwritingbuttons[NWCONFIRM].state = ACTIVE;
	max->menu.newwritingbuttons[NWCONFIRM].x = 1200;
	max->menu.newwritingbuttons[NWCONFIRM].y = 860;
	max->menu.newwritingbuttons[NWCONFIRM].text.text = S_CONFIRM;
	max->menu.newwritingbuttons[NWCONFIRM].text.sx = max->menu
		.newwritingbuttons[NWCONFIRM].x + 40;
	max->menu.newwritingbuttons[NWCONFIRM].text.sy = max->menu
		.newwritingbuttons[NWCONFIRM].y + 40;
}

void	ft_initbutton_easylvl(t_max *max)
{
	max->menu.gamedifficultybuttons[EASY] = ft_initbutton_helper(max);
	max->menu.gamedifficultybuttons[EASY].id = EASY;
	max->menu.gamedifficultybuttons[EASY].group = NEWDIFFICULTY;
	max->menu.gamedifficultybuttons[EASY].down = &max->menu
		.gamedifficultybuttons[MEDIUM];
	max->menu.gamedifficultybuttons[EASY].state = ACTIVE;
	max->menu.gamedifficultybuttons[EASY].x = 1000;
	max->menu.gamedifficultybuttons[EASY].y = 200;
	max->menu.gamedifficultybuttons[EASY].text.text = S_EASY;
	max->menu.gamedifficultybuttons[EASY].text.sx = max->menu
		.gamedifficultybuttons[EASY].x + 40;
	max->menu.gamedifficultybuttons[EASY].text.sy = max->menu
		.gamedifficultybuttons[EASY].y + 40;
}

void	ft_initbutton_mediumlvl(t_max *max)
{
	max->menu.gamedifficultybuttons[MEDIUM] = ft_initbutton_helper(max);
	max->menu.gamedifficultybuttons[MEDIUM].id = MEDIUM;
	max->menu.gamedifficultybuttons[MEDIUM].group = NEWDIFFICULTY;
	max->menu.gamedifficultybuttons[MEDIUM].up = &max->menu
		.gamedifficultybuttons[EASY];
	max->menu.gamedifficultybuttons[MEDIUM].down = &max->menu
		.gamedifficultybuttons[HARD];
	max->menu.gamedifficultybuttons[MEDIUM].state = ACTIVE;
	max->menu.gamedifficultybuttons[MEDIUM].x = 1000;
	max->menu.gamedifficultybuttons[MEDIUM].y = 400;
	max->menu.gamedifficultybuttons[MEDIUM].text.text = S_MEDIUM;
	max->menu.gamedifficultybuttons[MEDIUM].text.sx = max->menu
		.gamedifficultybuttons[MEDIUM].x + 40;
	max->menu.gamedifficultybuttons[MEDIUM].text.sy = max->menu
		.gamedifficultybuttons[MEDIUM].y + 40;
}

void	ft_initbutton_hardlvl(t_max *max)
{
	max->menu.gamedifficultybuttons[HARD] = ft_initbutton_helper(max);
	max->menu.gamedifficultybuttons[HARD].id = HARD;
	max->menu.gamedifficultybuttons[HARD].group = NEWDIFFICULTY;
	max->menu.gamedifficultybuttons[HARD].up = &max->menu
		.gamedifficultybuttons[MEDIUM];
	max->menu.gamedifficultybuttons[HARD].state = ACTIVE;
	max->menu.gamedifficultybuttons[HARD].x = 1000;
	max->menu.gamedifficultybuttons[HARD].y = 600;
	max->menu.gamedifficultybuttons[HARD].text.text = S_HARD;
	max->menu.gamedifficultybuttons[HARD].text.sx = max->menu
		.gamedifficultybuttons[HARD].x + 40;
	max->menu.gamedifficultybuttons[HARD].text.sy = max->menu
		.gamedifficultybuttons[HARD].y + 40;
}

void	ft_initbutton_campaign(t_max *max)
{
	max->menu.gametypebuttons[CAMPAIGN] = ft_initbutton_helper(max);
	max->menu.gametypebuttons[CAMPAIGN].id = CAMPAIGN;
	max->menu.gametypebuttons[CAMPAIGN].group = NEWSELECTION;
	max->menu.gametypebuttons[CAMPAIGN].down = &max->menu
		.gametypebuttons[TIMETRIAL];
	max->menu.gametypebuttons[CAMPAIGN].state = ACTIVE;
	max->menu.gametypebuttons[CAMPAIGN].x = 1000;
	max->menu.gametypebuttons[CAMPAIGN].y = 200;
	max->menu.gametypebuttons[CAMPAIGN].text.text = S_CAMPAIGN;
	max->menu.gametypebuttons[CAMPAIGN].text.sx = max->menu
		.gametypebuttons[CAMPAIGN].x + 40;
	max->menu.gametypebuttons[CAMPAIGN].text.sy = max->menu
		.gametypebuttons[CAMPAIGN].y + 40;
}

void	ft_initbutton_timetrial(t_max *max)
{
	max->menu.gametypebuttons[TIMETRIAL] = ft_initbutton_helper(max);
	max->menu.gametypebuttons[TIMETRIAL].id = TIMETRIAL;
	max->menu.gametypebuttons[TIMETRIAL].group = NEWSELECTION;
	max->menu.gametypebuttons[TIMETRIAL].up = &max->menu
		.gametypebuttons[CAMPAIGN];
	max->menu.gametypebuttons[TIMETRIAL].down = &max->menu
		.gametypebuttons[ONEMAP];
	max->menu.gametypebuttons[TIMETRIAL].state = ACTIVE;
	max->menu.gametypebuttons[TIMETRIAL].x = 1000;
	max->menu.gametypebuttons[TIMETRIAL].y = 400;
	max->menu.gametypebuttons[TIMETRIAL].text.text = S_TIMETRIAL;
	max->menu.gametypebuttons[TIMETRIAL].text.sx = max->menu
		.gametypebuttons[TIMETRIAL].x + 40;
	max->menu.gametypebuttons[TIMETRIAL].text.sy = max->menu
		.gametypebuttons[TIMETRIAL].y + 40;
}

void	ft_initbutton_onemap(t_max *max)
{
	max->menu.gametypebuttons[ONEMAP] = ft_initbutton_helper(max);
	max->menu.gametypebuttons[ONEMAP].id = ONEMAP;
	max->menu.gametypebuttons[ONEMAP].group = NEWSELECTION;
	max->menu.gametypebuttons[ONEMAP].up = &max->menu
		.gametypebuttons[TIMETRIAL];
	max->menu.gametypebuttons[ONEMAP].state = ACTIVE;
	max->menu.gametypebuttons[ONEMAP].x = 1000;
	max->menu.gametypebuttons[ONEMAP].y = 600;
	max->menu.gametypebuttons[ONEMAP].text.text = S_ONEMAP;
	max->menu.gametypebuttons[ONEMAP].text.sx = max->menu
		.gametypebuttons[ONEMAP].x + 40;
	max->menu.gametypebuttons[ONEMAP].text.sy = max->menu
		.gametypebuttons[ONEMAP].y + 40;
}

void	ft_initbutton_custom(t_max *max)
{
	max->menu.maptypebuttons[CUSTOM] = ft_initbutton_helper(max);
	max->menu.maptypebuttons[CUSTOM].id = CUSTOM;
	max->menu.maptypebuttons[CUSTOM].group = NEWLEVEL;
	max->menu.maptypebuttons[CUSTOM].down = &max->menu.maptypebuttons[RANDOM];
	max->menu.maptypebuttons[CUSTOM].state = ACTIVE;
	max->menu.maptypebuttons[CUSTOM].x = 1000;
	max->menu.maptypebuttons[CUSTOM].y = 300;
	max->menu.maptypebuttons[CUSTOM].text.text = S_CUSTOM;
	max->menu.maptypebuttons[CUSTOM].text.sx = max->menu
		.maptypebuttons[CUSTOM].x + 40;
	max->menu.maptypebuttons[CUSTOM].text.sy = max->menu
		.maptypebuttons[CUSTOM].y + 40;
}

void	ft_initbutton_random(t_max *max)
{
	max->menu.maptypebuttons[RANDOM] = ft_initbutton_helper(max);
	max->menu.maptypebuttons[RANDOM].id = RANDOM;
	max->menu.maptypebuttons[RANDOM].group = NEWLEVEL;
	max->menu.maptypebuttons[RANDOM].up = &max->menu.maptypebuttons[CUSTOM];
	max->menu.maptypebuttons[RANDOM].state = ACTIVE;
	max->menu.maptypebuttons[RANDOM].x = 1000;
	max->menu.maptypebuttons[RANDOM].y = 600;
	max->menu.maptypebuttons[RANDOM].text.text = S_RANDOM;
	max->menu.maptypebuttons[RANDOM].text.sx = max->menu
		.maptypebuttons[RANDOM].x + 40;
	max->menu.maptypebuttons[RANDOM].text.sy = max->menu
		.maptypebuttons[RANDOM].y + 40;
}

void	ft_initbutton_chooselvl(t_max *max)
{
	max->menu.mapselectionbuttons[CHOOSELEVEL] = ft_initbutton_helper(max);
	max->menu.mapselectionbuttons[CHOOSELEVEL].id = CUSTOM;
	max->menu.mapselectionbuttons[CHOOSELEVEL].group = NEWMAP;
	max->menu.mapselectionbuttons[CHOOSELEVEL].down = &max->menu
		.mapselectionbuttons[MSPLAY];
	max->menu.mapselectionbuttons[CHOOSELEVEL].state = ACTIVE;
	max->menu.mapselectionbuttons[CHOOSELEVEL].x = 800;
	max->menu.mapselectionbuttons[CHOOSELEVEL].y = 20;
	max->menu.mapselectionbuttons[CHOOSELEVEL].text.text = S_CHOOSELEVEL;
	max->menu.mapselectionbuttons[CHOOSELEVEL].text.height = 40;
	max->menu.mapselectionbuttons[CHOOSELEVEL].text.sx = max->menu
		.mapselectionbuttons[CHOOSELEVEL].x + 40;
	max->menu.mapselectionbuttons[CHOOSELEVEL].text.sy = max->menu
		.mapselectionbuttons[CHOOSELEVEL].y + 40;
}

void	ft_initbutton_msplay(t_max *max)
{
	max->menu.mapselectionbuttons[MSPLAY] = ft_initbutton_helper(max);
	max->menu.mapselectionbuttons[MSPLAY].id = MSPLAY;
	max->menu.mapselectionbuttons[MSPLAY].group = NEWMAP;
	max->menu.mapselectionbuttons[MSPLAY].up = &max->menu
		.mapselectionbuttons[CHOOSELEVEL];
	max->menu.mapselectionbuttons[MSPLAY].state = INACTIVE;
	max->menu.mapselectionbuttons[MSPLAY].x = 1200;
	max->menu.mapselectionbuttons[MSPLAY].y = 860;
	max->menu.mapselectionbuttons[MSPLAY].text.text = S_PLAY;
	max->menu.mapselectionbuttons[MSPLAY].text.sx = max->menu
		.mapselectionbuttons[MSPLAY].x + 40;
	max->menu.mapselectionbuttons[MSPLAY].text.sy = max->menu
		.mapselectionbuttons[MSPLAY].y + 40;
}

void	ft_initbutton_rsplay(t_max *max)
{
	max->menu.randomselectionbuttons[RSPLAY] = ft_initbutton_helper(max);
	max->menu.randomselectionbuttons[RSPLAY].id = RSPLAY;
	max->menu.randomselectionbuttons[RSPLAY].group = NEWRANDOM;
	max->menu.randomselectionbuttons[RSPLAY].down = &max->menu
		.randomselectionbuttons[RSADVANCED];
	max->menu.randomselectionbuttons[RSPLAY].state = ACTIVE;
	max->menu.randomselectionbuttons[RSPLAY].x = 1000;
	max->menu.randomselectionbuttons[RSPLAY].y = 300;
	max->menu.randomselectionbuttons[RSPLAY].text.text = S_PLAY;
	max->menu.randomselectionbuttons[RSPLAY].text.sx = max->menu
		.randomselectionbuttons[RSPLAY].x + 40;
	max->menu.randomselectionbuttons[RSPLAY].text.sy = max->menu
		.randomselectionbuttons[RSPLAY].y + 40;
}

void	ft_initbutton_rsadvanced(t_max *max)
{
	max->menu.randomselectionbuttons[RSADVANCED] = ft_initbutton_helper(max);
	max->menu.randomselectionbuttons[RSADVANCED].id = RSADVANCED;
	max->menu.randomselectionbuttons[RSADVANCED].group = NEWRANDOM;
	max->menu.randomselectionbuttons[RSADVANCED].up = &max->menu
		.randomselectionbuttons[RSPLAY];
	max->menu.randomselectionbuttons[RSADVANCED].state = ACTIVE;
	max->menu.randomselectionbuttons[RSADVANCED].x = 1000;
	max->menu.randomselectionbuttons[RSADVANCED].y = 600;
	max->menu.randomselectionbuttons[RSADVANCED].text.text = S_ADVANCED;
	max->menu.randomselectionbuttons[RSADVANCED].text.sx = max->menu
		.randomselectionbuttons[RSADVANCED].x + 40;
	max->menu.randomselectionbuttons[RSADVANCED].text.sy = max->menu
		.randomselectionbuttons[RSADVANCED].y + 40;
}

void	ft_initbuttons_global_helper(t_max *max)
{
	ft_initbutton_resume(max);
	ft_initbutton_newgame(max);
	ft_initbutton_savegame(max);
	ft_initbutton_loadgame(max);
	ft_initbutton_settings(max);
	ft_initbutton_halloffame(max);
	ft_initbutton_quitgame(max);
	ft_initbutton_name(max);
	ft_initbutton_coalition(max);
	ft_initbutton_campus(max);
	ft_initbutton_nwconfirm(max);
	ft_initbutton_easylvl(max);
	ft_initbutton_mediumlvl(max);
	ft_initbutton_hardlvl(max);
	ft_initbutton_campaign(max);
	ft_initbutton_timetrial(max);
	ft_initbutton_onemap(max);
	ft_initbutton_custom(max);
	ft_initbutton_random(max);
	ft_initbutton_chooselvl(max);
	ft_initbutton_msplay(max);
	ft_initbutton_rsplay(max);
	ft_initbutton_rsadvanced(max);
}

void	ft_initbutton_rwidth(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RWIDTH] = button;
	max->menu.randomadvancedbuttons[RWIDTH].id = RWIDTH;
	max->menu.randomadvancedbuttons[RWIDTH].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RWIDTH].down = &max->menu
		.randomadvancedbuttons[RRATIODE];
	max->menu.randomadvancedbuttons[RWIDTH].right = &max->menu
		.randomadvancedbuttons[RHEIGHT];
	max->menu.randomadvancedbuttons[RWIDTH].state = ACTIVE;
	max->menu.randomadvancedbuttons[RWIDTH].x = 700;
	max->menu.randomadvancedbuttons[RWIDTH].y = 20;
	max->menu.randomadvancedbuttons[RWIDTH].str = S_RWIDTH;
	max->menu.randomadvancedbuttons[RWIDTH].val = &max->menu.rm.width;
	ft_snprintf(max->menu.randomadvancedbuttons[RWIDTH].text.str,
		19, "%s: %i", S_RWIDTH, max->menu
		.randomadvancedbuttons[RWIDTH].val->value);
	max->menu.randomadvancedbuttons[RWIDTH].text.text = max->menu
		.randomadvancedbuttons[RWIDTH].text.str;
	max->menu.randomadvancedbuttons[RWIDTH].text.sx = max->menu
		.randomadvancedbuttons[RWIDTH].x + 110;
	max->menu.randomadvancedbuttons[RWIDTH].text.sy = max->menu
		.randomadvancedbuttons[RWIDTH].y + 50;
}

void	ft_initbutton_rheight(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RHEIGHT] = button;
	max->menu.randomadvancedbuttons[RHEIGHT].id = RHEIGHT;
	max->menu.randomadvancedbuttons[RHEIGHT].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RHEIGHT].down = &max->menu
		.randomadvancedbuttons[RRATIOLO];
	max->menu.randomadvancedbuttons[RHEIGHT].left = &max->menu
		.randomadvancedbuttons[RWIDTH];
	max->menu.randomadvancedbuttons[RHEIGHT].state = ACTIVE;
	max->menu.randomadvancedbuttons[RHEIGHT].x = 1250;
	max->menu.randomadvancedbuttons[RHEIGHT].y = 20;
	max->menu.randomadvancedbuttons[RHEIGHT].str = S_RHEIGHT;
	max->menu.randomadvancedbuttons[RHEIGHT].val = &max->menu.rm.height;
	ft_snprintf(max->menu.randomadvancedbuttons[RHEIGHT].text.str,
		19, "%s: %i", S_RHEIGHT, max->menu
		.randomadvancedbuttons[RHEIGHT].val->value);
	max->menu.randomadvancedbuttons[RHEIGHT].text.text = max->menu
		.randomadvancedbuttons[RHEIGHT].text.str;
	max->menu.randomadvancedbuttons[RHEIGHT].text.sx = max->menu
		.randomadvancedbuttons[RHEIGHT].x + 110;
	max->menu.randomadvancedbuttons[RHEIGHT].text.sy = max->menu
		.randomadvancedbuttons[RHEIGHT].y + 50;
}

void	ft_initbutton_rratiode(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RRATIODE] = button;
	max->menu.randomadvancedbuttons[RRATIODE].id = RRATIODE;
	max->menu.randomadvancedbuttons[RRATIODE].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIODE].up = &max->menu
		.randomadvancedbuttons[RWIDTH];
	max->menu.randomadvancedbuttons[RRATIODE].down = &max->menu
		.randomadvancedbuttons[RRATIOTI];
	max->menu.randomadvancedbuttons[RRATIODE].right = &max->menu
		.randomadvancedbuttons[RRATIOLO];
	max->menu.randomadvancedbuttons[RRATIODE].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIODE].x = 700;
	max->menu.randomadvancedbuttons[RRATIODE].y = 160;
	max->menu.randomadvancedbuttons[RRATIODE].str = S_RRATIODE;
	max->menu.randomadvancedbuttons[RRATIODE].val = &max->menu.rm.ratiode;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIODE].text.str,
		19, "%s: %i", S_RRATIODE, max->menu
		.randomadvancedbuttons[RRATIODE].val->value);
	max->menu.randomadvancedbuttons[RRATIODE].text.text = max->menu
		.randomadvancedbuttons[RRATIODE].text.str;
	max->menu.randomadvancedbuttons[RRATIODE].text.sx = max->menu
		.randomadvancedbuttons[RRATIODE].x + 110;
	max->menu.randomadvancedbuttons[RRATIODE].text.sy = max->menu
		.randomadvancedbuttons[RRATIODE].y + 50;
}

void	ft_initbutton_rratiolo(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RRATIOLO] = button;
	max->menu.randomadvancedbuttons[RRATIOLO].id = RRATIOLO;
	max->menu.randomadvancedbuttons[RRATIOLO].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIOLO].up = &max->menu
		.randomadvancedbuttons[RHEIGHT];
	max->menu.randomadvancedbuttons[RRATIOLO].down = &max->menu
		.randomadvancedbuttons[RRATIOXI];
	max->menu.randomadvancedbuttons[RRATIOLO].left = &max->menu
		.randomadvancedbuttons[RRATIODE];
	max->menu.randomadvancedbuttons[RRATIOLO].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIOLO].x = 1250;
	max->menu.randomadvancedbuttons[RRATIOLO].y = 160;
	max->menu.randomadvancedbuttons[RRATIOLO].str = S_RRATIOLO;
	max->menu.randomadvancedbuttons[RRATIOLO].val = &max->menu.rm.ratiolo;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIOLO].text.str,
		19, "%s: %i", S_RRATIOLO, max->menu
		.randomadvancedbuttons[RRATIOLO].val->value);
	max->menu.randomadvancedbuttons[RRATIOLO].text.text = max->menu
		.randomadvancedbuttons[RRATIOLO].text.str;
	max->menu.randomadvancedbuttons[RRATIOLO].text.sx = max->menu
		.randomadvancedbuttons[RRATIOLO].x + 110;
	max->menu.randomadvancedbuttons[RRATIOLO].text.sy = max->menu
		.randomadvancedbuttons[RRATIOLO].y + 50;
}

void	ft_initbutton_rratioti(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RRATIOTI] = button;
	max->menu.randomadvancedbuttons[RRATIOTI].id = RRATIOTI;
	max->menu.randomadvancedbuttons[RRATIOTI].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIOTI].up = &max->menu
		.randomadvancedbuttons[RRATIODE];
	max->menu.randomadvancedbuttons[RRATIOTI].down = &max->menu
		.randomadvancedbuttons[RNOROOMS];
	max->menu.randomadvancedbuttons[RRATIOTI].right = &max->menu
		.randomadvancedbuttons[RRATIOXI];
	max->menu.randomadvancedbuttons[RRATIOTI].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIOTI].x = 700;
	max->menu.randomadvancedbuttons[RRATIOTI].y = 300;
	max->menu.randomadvancedbuttons[RRATIOTI].str = S_RRATIOTI;
	max->menu.randomadvancedbuttons[RRATIOTI].val = &max->menu.rm.ratioti;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIOTI].text.str,
		19, "%s: %i", S_RRATIOTI, max->menu
		.randomadvancedbuttons[RRATIOTI].val->value);
	max->menu.randomadvancedbuttons[RRATIOTI].text.text = max->menu
		.randomadvancedbuttons[RRATIOTI].text.str;
	max->menu.randomadvancedbuttons[RRATIOTI].text.sx = max->menu
		.randomadvancedbuttons[RRATIOTI].x + 110;
	max->menu.randomadvancedbuttons[RRATIOTI].text.sy = max->menu
		.randomadvancedbuttons[RRATIOTI].y + 50;
}

void	ft_initbutton_rratioxi(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RRATIOXI] = button;
	max->menu.randomadvancedbuttons[RRATIOXI].id = RRATIOXI;
	max->menu.randomadvancedbuttons[RRATIOXI].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIOXI].up = &max->menu
		.randomadvancedbuttons[RRATIOLO];
	max->menu.randomadvancedbuttons[RRATIOXI].down = &max->menu
		.randomadvancedbuttons[ROROOMS];
	max->menu.randomadvancedbuttons[RRATIOXI].left = &max->menu
		.randomadvancedbuttons[RRATIOTI];
	max->menu.randomadvancedbuttons[RRATIOXI].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIOXI].x = 1250;
	max->menu.randomadvancedbuttons[RRATIOXI].y = 300;
	max->menu.randomadvancedbuttons[RRATIOXI].str = S_RRATIOXI;
	max->menu.randomadvancedbuttons[RRATIOXI].val = &max->menu.rm.ratioxi;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIOXI].text.str,
		19, "%s: %i", S_RRATIOXI, max->menu
		.randomadvancedbuttons[RRATIOXI].val->value);
	max->menu.randomadvancedbuttons[RRATIOXI].text.text = max->menu
		.randomadvancedbuttons[RRATIOXI].text.str;
	max->menu.randomadvancedbuttons[RRATIOXI].text.sx = max->menu
		.randomadvancedbuttons[RRATIOXI].x + 110;
	max->menu.randomadvancedbuttons[RRATIOXI].text.sy = max->menu
		.randomadvancedbuttons[RRATIOXI].y + 50;
}

void	ft_initbutton_rnorooms(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RNOROOMS] = button;
	max->menu.randomadvancedbuttons[RNOROOMS].id = RNOROOMS;
	max->menu.randomadvancedbuttons[RNOROOMS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RNOROOMS].up = &max->menu
		.randomadvancedbuttons[RRATIOTI];
	max->menu.randomadvancedbuttons[RNOROOMS].down = &max->menu
		.randomadvancedbuttons[RDOORS];
	max->menu.randomadvancedbuttons[RNOROOMS].right = &max->menu
		.randomadvancedbuttons[ROROOMS];
	max->menu.randomadvancedbuttons[RNOROOMS].state = ACTIVE;
	max->menu.randomadvancedbuttons[RNOROOMS].x = 700;
	max->menu.randomadvancedbuttons[RNOROOMS].y = 440;
	max->menu.randomadvancedbuttons[RNOROOMS].str = S_RNOROOMS;
	max->menu.randomadvancedbuttons[RNOROOMS].val = &max->menu.rm.rnorooms;
	ft_snprintf(max->menu.randomadvancedbuttons[RNOROOMS].text.str,
		19, "%s: %i", S_RNOROOMS, max->menu
		.randomadvancedbuttons[RNOROOMS].val->value);
	max->menu.randomadvancedbuttons[RNOROOMS].text.text = max->menu
		.randomadvancedbuttons[RNOROOMS].text.str;
	max->menu.randomadvancedbuttons[RNOROOMS].text.sx = max->menu
		.randomadvancedbuttons[RNOROOMS].x + 110;
	max->menu.randomadvancedbuttons[RNOROOMS].text.sy = max->menu
		.randomadvancedbuttons[RNOROOMS].y + 50;
}

void	ft_initbutton_rorooms(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[ROROOMS] = button;
	max->menu.randomadvancedbuttons[ROROOMS].id = ROROOMS;
	max->menu.randomadvancedbuttons[ROROOMS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[ROROOMS].up = &max->menu
		.randomadvancedbuttons[RRATIOXI];
	max->menu.randomadvancedbuttons[ROROOMS].down = &max->menu
		.randomadvancedbuttons[RDEADENDS];
	max->menu.randomadvancedbuttons[ROROOMS].left = &max->menu
		.randomadvancedbuttons[RNOROOMS];
	max->menu.randomadvancedbuttons[ROROOMS].state = ACTIVE;
	max->menu.randomadvancedbuttons[ROROOMS].x = 1250;
	max->menu.randomadvancedbuttons[ROROOMS].y = 440;
	max->menu.randomadvancedbuttons[ROROOMS].str = S_ROROOMS;
	max->menu.randomadvancedbuttons[ROROOMS].val = &max->menu.rm.rorooms;
	ft_snprintf(max->menu.randomadvancedbuttons[ROROOMS].text.str,
		19, "%s: %i", S_ROROOMS, max->menu
		.randomadvancedbuttons[ROROOMS].val->value);
	max->menu.randomadvancedbuttons[ROROOMS].text.text = max->menu
		.randomadvancedbuttons[ROROOMS].text.str;
	max->menu.randomadvancedbuttons[ROROOMS].text.sx = max->menu
		.randomadvancedbuttons[ROROOMS].x + 110;
	max->menu.randomadvancedbuttons[ROROOMS].text.sy = max->menu
		.randomadvancedbuttons[ROROOMS].y + 50;
}

void	ft_initbutton_rdoors(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RDOORS] = button;
	max->menu.randomadvancedbuttons[RDOORS].id = RDOORS;
	max->menu.randomadvancedbuttons[RDOORS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RDOORS].up = &max->menu
		.randomadvancedbuttons[RNOROOMS];
	max->menu.randomadvancedbuttons[RDOORS].down = &max->menu
		.randomadvancedbuttons[RPLAY];
	max->menu.randomadvancedbuttons[RDOORS].right = &max->menu
		.randomadvancedbuttons[RDEADENDS];
	max->menu.randomadvancedbuttons[RDOORS].state = ACTIVE;
	max->menu.randomadvancedbuttons[RDOORS].x = 700;
	max->menu.randomadvancedbuttons[RDOORS].y = 580;
	max->menu.randomadvancedbuttons[RDOORS].str = S_RDOORS;
	max->menu.randomadvancedbuttons[RDOORS].val = &max->menu.rm.rdoors;
	ft_snprintf(max->menu.randomadvancedbuttons[RDOORS].text.str,
		19, "%s: %i", S_RDOORS, max->menu
		.randomadvancedbuttons[RDOORS].val->value);
	max->menu.randomadvancedbuttons[RDOORS].text.text = max->menu
		.randomadvancedbuttons[RDOORS].text.str;
	max->menu.randomadvancedbuttons[RDOORS].text.sx = max->menu
		.randomadvancedbuttons[RDOORS].x + 110;
	max->menu.randomadvancedbuttons[RDOORS].text.sy = max->menu
		.randomadvancedbuttons[RDOORS].y + 50;
}

void	ft_initbutton_rdeadends(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RDEADENDS] = button;
	max->menu.randomadvancedbuttons[RDEADENDS].id = RDEADENDS;
	max->menu.randomadvancedbuttons[RDEADENDS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RDEADENDS].up = &max->menu
		.randomadvancedbuttons[ROROOMS];
	max->menu.randomadvancedbuttons[RDEADENDS].down = &max->menu
		.randomadvancedbuttons[RPLAY];
	max->menu.randomadvancedbuttons[RDEADENDS].left = &max->menu
		.randomadvancedbuttons[RDOORS];
	max->menu.randomadvancedbuttons[RDEADENDS].state = ACTIVE;
	max->menu.randomadvancedbuttons[RDEADENDS].x = 1250;
	max->menu.randomadvancedbuttons[RDEADENDS].y = 580;
	max->menu.randomadvancedbuttons[RDEADENDS].str = S_RDEADENDS;
	max->menu.randomadvancedbuttons[RDEADENDS].val = &max->menu.rm.rdeadends;
	ft_snprintf(max->menu.randomadvancedbuttons[RDEADENDS].text.str,
		19, "%s: %i", S_RDEADENDS, max->menu
		.randomadvancedbuttons[RDEADENDS].val->value);
	max->menu.randomadvancedbuttons[RDEADENDS].text.text = max->menu
		.randomadvancedbuttons[RDEADENDS].text.str;
	max->menu.randomadvancedbuttons[RDEADENDS].text.sx = max->menu
		.randomadvancedbuttons[RDEADENDS].x + 110;
	max->menu.randomadvancedbuttons[RDEADENDS].text.sy = max->menu
		.randomadvancedbuttons[RDEADENDS].y + 50;
}

void	ft_initbutton_rrandomize(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RRANDOMIZE] = button;
	max->menu.randomadvancedbuttons[RRANDOMIZE].id = RRANDOMIZE;
	max->menu.randomadvancedbuttons[RRANDOMIZE].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRANDOMIZE].up = &max->menu
		.randomadvancedbuttons[RDOORS];
	max->menu.randomadvancedbuttons[RRANDOMIZE].right = &max->menu
		.randomadvancedbuttons[RPLAY];
	max->menu.randomadvancedbuttons[RRANDOMIZE].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRANDOMIZE].x = 850;
	max->menu.randomadvancedbuttons[RRANDOMIZE].y = 860;
	max->menu.randomadvancedbuttons[RRANDOMIZE].text.text = S_RANDOMIZE;
	max->menu.randomadvancedbuttons[RRANDOMIZE].text.sx = max->menu
		.randomadvancedbuttons[RRANDOMIZE].x + 40;
	max->menu.randomadvancedbuttons[RRANDOMIZE].text.sy = max->menu
		.randomadvancedbuttons[RRANDOMIZE].y + 40;
}

void	ft_initbutton_rplay(t_max *max, t_button button)
{
	max->menu.randomadvancedbuttons[RPLAY] = button;
	max->menu.randomadvancedbuttons[RPLAY].id = RPLAY;
	max->menu.randomadvancedbuttons[RPLAY].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RPLAY].up = &max->menu
		.randomadvancedbuttons[RDEADENDS];
	max->menu.randomadvancedbuttons[RPLAY].left = &max->menu
		.randomadvancedbuttons[RRANDOMIZE];
	max->menu.randomadvancedbuttons[RPLAY].state = ACTIVE;
	max->menu.randomadvancedbuttons[RPLAY].x = 1250;
	max->menu.randomadvancedbuttons[RPLAY].y = 860;
	max->menu.randomadvancedbuttons[RPLAY].text.text = S_PLAY;
	max->menu.randomadvancedbuttons[RPLAY].text.sx = max->menu
		.randomadvancedbuttons[RPLAY].x + 40;
	max->menu.randomadvancedbuttons[RPLAY].text.sy = max->menu
		.randomadvancedbuttons[RPLAY].y + 40;
}

void	ft_initbutton_choosesave(t_max *max, t_button button)
{
	max->menu.savegamebuttons[CHOOSESAVE] = button;
	max->menu.savegamebuttons[CHOOSESAVE].id = CHOOSESAVE;
	max->menu.savegamebuttons[CHOOSESAVE].group = SAVEGROUP;
	max->menu.savegamebuttons[CHOOSESAVE].down = &max->menu
		.savegamebuttons[SAVE];
	max->menu.savegamebuttons[CHOOSESAVE].state = ACTIVE;
	max->menu.savegamebuttons[CHOOSESAVE].x = 800;
	max->menu.savegamebuttons[CHOOSESAVE].y = 20;
	max->menu.savegamebuttons[CHOOSESAVE].text.text = S_CHOOSESAVE;
	max->menu.savegamebuttons[CHOOSESAVE].text.height = 40;
	max->menu.savegamebuttons[CHOOSESAVE].text.sx = max->menu
		.savegamebuttons[CHOOSESAVE].x + 40;
	max->menu.savegamebuttons[CHOOSESAVE].text.sy = max->menu
		.savegamebuttons[CHOOSESAVE].y + 40;
}

void	ft_initbutton_delete(t_max *max, t_button button)
{
	max->menu.savegamebuttons[DELETE] = button;
	max->menu.savegamebuttons[DELETE].id = DELETE;
	max->menu.savegamebuttons[DELETE].group = SAVEGROUP;
	max->menu.savegamebuttons[DELETE].up = &max->menu
		.savegamebuttons[CHOOSELEVEL];
	max->menu.savegamebuttons[DELETE].right = &max->menu
		.savegamebuttons[SAVE];
	max->menu.savegamebuttons[DELETE].state = ACTIVE;
	max->menu.savegamebuttons[DELETE].x = 800;
	max->menu.savegamebuttons[DELETE].y = 860;
	max->menu.savegamebuttons[DELETE].text.text = S_DELETE;
	max->menu.savegamebuttons[DELETE].text.sx = max->menu
		.savegamebuttons[DELETE].x + 40;
	max->menu.savegamebuttons[DELETE].text.sy = max->menu
		.savegamebuttons[DELETE].y + 40;
}

void	ft_initbuttons(t_max *max)
{
	t_button	button;
	t_text		text;

	button = ft_initbutton_helper(max);
	text = ft_inittext_helper(max);
	ft_initbuttons_global_helper(max);
	button.button = max->menu.buttonplus;
	button.text.height = 40;
	ft_initbutton_rwidth(max, button);
	ft_initbutton_rheight(max, button);
	ft_initbutton_rratiode(max, button);
	ft_initbutton_rratiolo(max, button);
	ft_initbutton_rratioti(max, button);
	ft_initbutton_rratioxi(max, button);
	ft_initbutton_rnorooms(max, button);
	ft_initbutton_rorooms(max, button);
	ft_initbutton_rdoors(max, button);
	ft_initbutton_rdeadends(max, button);
	button.text.height = 60;
	button.button = max->menu.button;
	ft_initbutton_rrandomize(max, button);
	ft_initbutton_rplay(max, button);
	ft_initbutton_choosesave(max, button);
	ft_initbutton_delete(max, button);
	max->menu.savegamebuttons[SAVE] = button;
	max->menu.savegamebuttons[SAVE].id = SAVE;
	max->menu.savegamebuttons[SAVE].group = SAVEGROUP;
	max->menu.savegamebuttons[SAVE].up = &max->menu
		.savegamebuttons[CHOOSELEVEL];
	max->menu.savegamebuttons[SAVE].left = &max->menu.savegamebuttons[DELETE];
	max->menu.savegamebuttons[SAVE].state = ACTIVE;
	max->menu.savegamebuttons[SAVE].x = 1200;
	max->menu.savegamebuttons[SAVE].y = 860;
	max->menu.savegamebuttons[SAVE].text.text = S_SAVE;
	max->menu.savegamebuttons[SAVE].text.sx = max->menu
		.savegamebuttons[SAVE].x + 40;
	max->menu.savegamebuttons[SAVE].text.sy = max->menu
		.savegamebuttons[SAVE].y + 40;
	max->menu.loadgamebuttons[CHOOSELOAD] = button;
	max->menu.loadgamebuttons[CHOOSELOAD].id = CHOOSELOAD;
	max->menu.loadgamebuttons[CHOOSELOAD].group = LOADGROUP;
	max->menu.loadgamebuttons[CHOOSELOAD].down = &max->menu
		.loadgamebuttons[LOAD];
	max->menu.loadgamebuttons[CHOOSELOAD].state = ACTIVE;
	max->menu.loadgamebuttons[CHOOSELOAD].x = 800;
	max->menu.loadgamebuttons[CHOOSELOAD].y = 20;
	max->menu.loadgamebuttons[CHOOSELOAD].text.text = S_CHOOSELOAD;
	max->menu.loadgamebuttons[CHOOSELOAD].text.height = 40;
	max->menu.loadgamebuttons[CHOOSELOAD].text.sx = max->menu
		.loadgamebuttons[CHOOSELOAD].x + 40;
	max->menu.loadgamebuttons[CHOOSELOAD].text.sy = max->menu
		.loadgamebuttons[CHOOSELOAD].y + 40;
	max->menu.loadgamebuttons[DELETE] = button;
	max->menu.loadgamebuttons[DELETE].id = DELETE;
	max->menu.loadgamebuttons[DELETE].group = LOADGROUP;
	max->menu.loadgamebuttons[DELETE].up = &max->menu
		.loadgamebuttons[CHOOSELEVEL];
	max->menu.loadgamebuttons[DELETE].right = &max->menu.loadgamebuttons[LOAD];
	max->menu.loadgamebuttons[DELETE].state = ACTIVE;
	max->menu.loadgamebuttons[DELETE].x = 800;
	max->menu.loadgamebuttons[DELETE].y = 860;
	max->menu.loadgamebuttons[DELETE].text.text = S_DELETE;
	max->menu.loadgamebuttons[DELETE].text.sx = max->menu
		.loadgamebuttons[DELETE].x + 40;
	max->menu.loadgamebuttons[DELETE].text.sy = max->menu
		.loadgamebuttons[DELETE].y + 40;
	max->menu.loadgamebuttons[LOAD] = button;
	max->menu.loadgamebuttons[LOAD].id = LOAD;
	max->menu.loadgamebuttons[LOAD].group = LOADGROUP;
	max->menu.loadgamebuttons[LOAD].up = &max->menu
		.loadgamebuttons[CHOOSELEVEL];
	max->menu.loadgamebuttons[LOAD].left = &max->menu.loadgamebuttons[DELETE];
	max->menu.loadgamebuttons[LOAD].state = ACTIVE;
	max->menu.loadgamebuttons[LOAD].x = 1200;
	max->menu.loadgamebuttons[LOAD].y = 860;
	max->menu.loadgamebuttons[LOAD].text.text = S_LOAD;
	max->menu.loadgamebuttons[LOAD].text.sx = max->menu
		.loadgamebuttons[LOAD].x + 40;
	max->menu.loadgamebuttons[LOAD].text.sy = max->menu
		.loadgamebuttons[LOAD].y + 40;
	max->menu.halloffamebuttons[HOFBACK] = button;
	max->menu.halloffamebuttons[HOFBACK].id = HOFBACK;
	max->menu.halloffamebuttons[HOFBACK].group = HALLOFFAMEGROUP;
	max->menu.halloffamebuttons[HOFBACK].state = ACTIVE;
	max->menu.halloffamebuttons[HOFBACK].x = 1250;
	max->menu.halloffamebuttons[HOFBACK].y = 860;
	max->menu.halloffamebuttons[HOFBACK].text.text = S_BACK;
	max->menu.halloffamebuttons[HOFBACK].text.sx = max->menu
		.halloffamebuttons[HOFBACK].x + 40;
	max->menu.halloffamebuttons[HOFBACK].text.sy = max->menu
		.halloffamebuttons[HOFBACK].y + 40;
}

void	ft_draw_button(t_button *b, int state)
{
	t_db	db;

	b->state = state;
	db.w = b->button->width;
	db.h = b->button->height;
	db.j = 0;
	while (db.j < db.h)
	{
		db.i = 0;
		while (db.i < db.w)
		{
			db.a = (db.j * db.w * 4) + (db.i * 4);
			if (db.i < db.w && db.j < db.h)
				db.c = (b->button->pixels[db.a]) << 24
					| (b->button->pixels[db.a + 1]) << 16
					| (b->button->pixels[db.a + 2])
					<< 8 | (b->button->pixels[db.a + 3]);
			else
				db.c = 0xFF00FFFF;
			if (db.c & 0xFFFFFF00)
			{
				if (state & INACTIVE)
					mlx_put_pixel(b->image, db.i + b->x,
						db.j + b->y, C_INACTIVE);
				else if (state & ACTIVE)
					mlx_put_pixel(b->image, db.i + b->x,
						db.j + b->y, C_ACTIVE);
				else if (state & SELECTED)
					mlx_put_pixel(b->image, db.i + b->x,
						db.j + b->y, C_SELECTED);
				else if (state & ACTIVATED)
					mlx_put_pixel(b->image, db.i + b->x,
						db.j + b->y, C_ACTIVATED);
			}
			else if ((db.c & 0xFF) == 0xFF)
				mlx_put_pixel(b->image, db.i + b->x, db.j + b->y, db.c);
			++db.i;
		}
		++db.j;
	}
	ft_draw_text(&b->text, state);
}

void	ft_choose_in_button(t_max *max, t_button *button)
{
	int	i;

	i = button->val->value;
	if (max->keys[MLX_KEY_KP_ADD] || max->keys[MLX_KEY_RIGHT])
	{
		++i;
		max->keys[MLX_KEY_KP_ADD] = 0;
		max->keys[MLX_KEY_UP] = 0;
		max->keys[MLX_KEY_RIGHT] = 0;
	}
	if (max->keys[MLX_KEY_KP_SUBTRACT] || max->keys[MLX_KEY_LEFT])
	{
		--i;
		max->keys[MLX_KEY_KP_SUBTRACT] = 0;
		max->keys[MLX_KEY_DOWN] = 0;
		max->keys[MLX_KEY_LEFT] = 0;
	}
	if (max->keys[MLX_KEY_KP_MULTIPLY])
	{
		i *= 2;
		max->keys[MLX_KEY_KP_MULTIPLY] = 0;
	}
	if (max->keys[MLX_KEY_KP_DIVIDE])
	{
		i /= 2;
		max->keys[MLX_KEY_KP_DIVIDE] = 0;
	}
	if (max->keys[MLX_KEY_UP])
	{
		i += 10;
		max->keys[MLX_KEY_UP] = 0;
	}
	if (max->keys[MLX_KEY_DOWN])
	{
		i -= 10;
		max->keys[MLX_KEY_DOWN] = 0;
	}
	if (i < button->val->min)
		i = button->val->min;
	if (i > button->val->max)
		i = button->val->max;
	button->val->value = i;
	ft_snprintf(button->text.str, 19, "%s: %i", button->str,
		button->val->value);
}
