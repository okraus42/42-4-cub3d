/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:42:26 by okraus            #+#    #+#             */
/*   Updated: 2024/04/12 09:12:06 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"


// ft_draw_button(max, 200, 20, S_RESUME, INACTIVE);
// 	ft_draw_button(max, 200, 160, S_NEWGAME, ACTIVE);
// 	ft_draw_button(max, 200, 300, S_SAVEGAME, INACTIVE);
// 	ft_draw_button(max, 200, 440, S_LOADGAME, INACTIVE);
// 	ft_draw_button(max, 200, 580, S_SETTINGS, INACTIVE);
// 	ft_draw_button(max, 200, 720, S_HALLOFFAME, INACTIVE);
// 	ft_draw_button(max, 200, 860, S_QUITGAME, ACTIVE);

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
void	ft_initbuttons(t_max *max)
{
	t_button	button;
	t_text		text;

	ft_bzero(&text, sizeof(text));
	ft_bzero(&button, sizeof(button));
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
	button.button = max->menu.button;
	button.image = max->i.menuscreen;
	button.text = text;
	button.c = C_INACTIVE;
	button.x = 200;
	button.y = 0;
	button.w = 350;
	button.h = 150;
	button.state = INACTIVE;
	max->menu.mainbuttons[RESUME] = button;
	max->menu.mainbuttons[RESUME].id = RESUME;
	max->menu.mainbuttons[RESUME].group = MAINBUTTONS;
	max->menu.mainbuttons[RESUME].down = &max->menu.mainbuttons[NEWGAME];
	max->menu.mainbuttons[RESUME].y = 20;
	max->menu.mainbuttons[RESUME].text.text = S_RESUME;
	max->menu.mainbuttons[RESUME].text.sx = max->menu.mainbuttons[RESUME].x + 40;
	max->menu.mainbuttons[RESUME].text.sy = max->menu.mainbuttons[RESUME].y + 40;
	max->menu.mainbuttons[NEWGAME] = button;
	max->menu.mainbuttons[NEWGAME].id = NEWGAME;
	max->menu.mainbuttons[NEWGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[NEWGAME].up = &max->menu.mainbuttons[RESUME];
	max->menu.mainbuttons[NEWGAME].down = &max->menu.mainbuttons[SAVEGAME];
	max->menu.mainbuttons[NEWGAME].state = SELECTED;
	max->menu.mainbuttons[NEWGAME].y = 160;
	max->menu.mainbuttons[NEWGAME].text.text = S_NEWGAME;
	max->menu.mainbuttons[NEWGAME].text.sx = max->menu.mainbuttons[NEWGAME].x + 40;
	max->menu.mainbuttons[NEWGAME].text.sy = max->menu.mainbuttons[NEWGAME].y + 40;
	max->menu.mainbuttons[SAVEGAME] = button;
	max->menu.mainbuttons[SAVEGAME].id = SAVEGAME;
	max->menu.mainbuttons[SAVEGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[SAVEGAME].up = &max->menu.mainbuttons[NEWGAME];
	max->menu.mainbuttons[SAVEGAME].down = &max->menu.mainbuttons[LOADGAME];
	max->menu.mainbuttons[SAVEGAME].y = 300;
	max->menu.mainbuttons[SAVEGAME].text.text = S_SAVEGAME;
	max->menu.mainbuttons[SAVEGAME].text.sx = max->menu.mainbuttons[SAVEGAME].x + 40;
	max->menu.mainbuttons[SAVEGAME].text.sy = max->menu.mainbuttons[SAVEGAME].y + 40;
	max->menu.mainbuttons[LOADGAME] = button;
	max->menu.mainbuttons[LOADGAME].id = LOADGAME;
	max->menu.mainbuttons[LOADGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[LOADGAME].up = &max->menu.mainbuttons[SAVEGAME];
	max->menu.mainbuttons[LOADGAME].down = &max->menu.mainbuttons[SETTINGS];
	max->menu.mainbuttons[LOADGAME].y = 440;
	max->menu.mainbuttons[LOADGAME].text.text = S_LOADGAME;
	max->menu.mainbuttons[LOADGAME].text.sx = max->menu.mainbuttons[LOADGAME].x + 40;
	max->menu.mainbuttons[LOADGAME].text.sy = max->menu.mainbuttons[LOADGAME].y + 40;
	max->menu.mainbuttons[SETTINGS] = button;
	max->menu.mainbuttons[SETTINGS].id = SETTINGS;
	max->menu.mainbuttons[SETTINGS].group = MAINBUTTONS;
	max->menu.mainbuttons[SETTINGS].up = &max->menu.mainbuttons[LOADGAME];
	max->menu.mainbuttons[SETTINGS].down = &max->menu.mainbuttons[HALLOFFAME];
	max->menu.mainbuttons[SETTINGS].y = 580;
	max->menu.mainbuttons[SETTINGS].text.text = S_SETTINGS;
	max->menu.mainbuttons[SETTINGS].text.sx = max->menu.mainbuttons[SETTINGS].x + 40;
	max->menu.mainbuttons[SETTINGS].text.sy = max->menu.mainbuttons[SETTINGS].y + 40;
	max->menu.mainbuttons[HALLOFFAME] = button;
	max->menu.mainbuttons[HALLOFFAME].id = HALLOFFAME;
	max->menu.mainbuttons[HALLOFFAME].group = MAINBUTTONS;
	max->menu.mainbuttons[HALLOFFAME].up = &max->menu.mainbuttons[SETTINGS];
	max->menu.mainbuttons[HALLOFFAME].down = &max->menu.mainbuttons[QUITGAME];
	max->menu.mainbuttons[HALLOFFAME].state = ACTIVE;
	max->menu.mainbuttons[HALLOFFAME].y = 720;
	max->menu.mainbuttons[HALLOFFAME].text.text = S_HALLOFFAME;
	max->menu.mainbuttons[HALLOFFAME].text.sx = max->menu.mainbuttons[HALLOFFAME].x + 40;
	max->menu.mainbuttons[HALLOFFAME].text.sy = max->menu.mainbuttons[HALLOFFAME].y + 40;
	max->menu.mainbuttons[HALLOFFAME].text.height = 40;
	max->menu.mainbuttons[QUITGAME] = button;
	max->menu.mainbuttons[QUITGAME].id = QUITGAME;
	max->menu.mainbuttons[QUITGAME].group = MAINBUTTONS;
	max->menu.mainbuttons[QUITGAME].up = &max->menu.mainbuttons[HALLOFFAME];
	max->menu.mainbuttons[QUITGAME].state = ACTIVE;
	max->menu.mainbuttons[QUITGAME].y = 860;
	max->menu.mainbuttons[QUITGAME].text.text = S_QUITGAME;
	max->menu.mainbuttons[QUITGAME].text.sx = max->menu.mainbuttons[QUITGAME].x + 40;
	max->menu.mainbuttons[QUITGAME].text.sy = max->menu.mainbuttons[QUITGAME].y + 40;
	max->menu.newwritingbuttons[NAME] = button;
	max->menu.newwritingbuttons[NAME].id = NAME;
	max->menu.newwritingbuttons[NAME].group = NEWWRITING;
	max->menu.newwritingbuttons[NAME].down = &max->menu.newwritingbuttons[COALITION];
	max->menu.newwritingbuttons[NAME].state = ACTIVE;
	max->menu.newwritingbuttons[NAME].x = 600;
	max->menu.newwritingbuttons[NAME].y = 20;
	max->menu.newwritingbuttons[NAME].text.text = S_NAME;
	max->menu.newwritingbuttons[NAME].text.sx = max->menu.newwritingbuttons[NAME].x + 40;
	max->menu.newwritingbuttons[NAME].text.sy = max->menu.newwritingbuttons[NAME].y + 40;
	max->menu.newwritingbuttons[COALITION] = button;
	max->menu.newwritingbuttons[COALITION].id = COALITION;
	max->menu.newwritingbuttons[COALITION].group = NEWWRITING;
	max->menu.newwritingbuttons[COALITION].up = &max->menu.newwritingbuttons[NAME];
	max->menu.newwritingbuttons[COALITION].down = &max->menu.newwritingbuttons[CAMPUS];
	max->menu.newwritingbuttons[COALITION].state = ACTIVE;
	max->menu.newwritingbuttons[COALITION].x = 600;
	max->menu.newwritingbuttons[COALITION].y = 300;
	max->menu.newwritingbuttons[COALITION].text.text = S_COALITION;
	max->menu.newwritingbuttons[COALITION].text.sx = max->menu.newwritingbuttons[COALITION].x + 40;
	max->menu.newwritingbuttons[COALITION].text.sy = max->menu.newwritingbuttons[COALITION].y + 40;
	max->menu.newwritingbuttons[CAMPUS] = button;
	max->menu.newwritingbuttons[CAMPUS].id = CAMPUS;
	max->menu.newwritingbuttons[CAMPUS].group = NEWWRITING;
	max->menu.newwritingbuttons[CAMPUS].up = &max->menu.newwritingbuttons[COALITION];
	max->menu.newwritingbuttons[CAMPUS].down = &max->menu.newwritingbuttons[NWCONFIRM];
	max->menu.newwritingbuttons[CAMPUS].state = ACTIVE;
	max->menu.newwritingbuttons[CAMPUS].x = 600;
	max->menu.newwritingbuttons[CAMPUS].y = 580;
	max->menu.newwritingbuttons[CAMPUS].text.text = S_CAMPUS;
	max->menu.newwritingbuttons[CAMPUS].text.sx = max->menu.newwritingbuttons[CAMPUS].x + 40;
	max->menu.newwritingbuttons[CAMPUS].text.sy = max->menu.newwritingbuttons[CAMPUS].y + 40;
	// max->menu.newwritingbuttons[NWBACK] = button;
	// max->menu.newwritingbuttons[NWBACK].id = NWBACK;
	// max->menu.newwritingbuttons[NWBACK].group = NEWWRITING;
	// max->menu.newwritingbuttons[NWBACK].up = &max->menu.newwritingbuttons[CAMPUS];
	// max->menu.newwritingbuttons[NWBACK].right = &max->menu.newwritingbuttons[NWCONFIRM];
	// max->menu.newwritingbuttons[NWBACK].state = ACTIVE;
	// max->menu.newwritingbuttons[NWBACK].x = 800;
	// max->menu.newwritingbuttons[NWBACK].y = 860;
	// max->menu.newwritingbuttons[NWBACK].text.text = S_BACK;
	// max->menu.newwritingbuttons[NWBACK].text.sx = max->menu.newwritingbuttons[NWBACK].x + 40;
	// max->menu.newwritingbuttons[NWBACK].text.sy = max->menu.newwritingbuttons[NWBACK].y + 40;
	max->menu.newwritingbuttons[NWCONFIRM] = button;
	max->menu.newwritingbuttons[NWCONFIRM].id = NWCONFIRM;
	max->menu.newwritingbuttons[NWCONFIRM].group = NEWWRITING;
	max->menu.newwritingbuttons[NWCONFIRM].up = &max->menu.newwritingbuttons[CAMPUS];
	max->menu.newwritingbuttons[NWCONFIRM].state = ACTIVE;
	max->menu.newwritingbuttons[NWCONFIRM].x = 1200;
	max->menu.newwritingbuttons[NWCONFIRM].y = 860;
	max->menu.newwritingbuttons[NWCONFIRM].text.text = S_CONFIRM;
	max->menu.newwritingbuttons[NWCONFIRM].text.sx = max->menu.newwritingbuttons[NWCONFIRM].x + 40;
	max->menu.newwritingbuttons[NWCONFIRM].text.sy = max->menu.newwritingbuttons[NWCONFIRM].y + 40;
	max->menu.gamedifficultybuttons[EASY] = button;
	max->menu.gamedifficultybuttons[EASY].id = EASY;
	max->menu.gamedifficultybuttons[EASY].group = NEWDIFFICULTY;
	max->menu.gamedifficultybuttons[EASY].down = &max->menu.gamedifficultybuttons[MEDIUM];
	max->menu.gamedifficultybuttons[EASY].state = ACTIVE;
	max->menu.gamedifficultybuttons[EASY].x = 1000;
	max->menu.gamedifficultybuttons[EASY].y = 200;
	max->menu.gamedifficultybuttons[EASY].text.text = S_EASY;
	max->menu.gamedifficultybuttons[EASY].text.sx = max->menu.gamedifficultybuttons[EASY].x + 40;
	max->menu.gamedifficultybuttons[EASY].text.sy = max->menu.gamedifficultybuttons[EASY].y + 40;
	max->menu.gamedifficultybuttons[MEDIUM] = button;
	max->menu.gamedifficultybuttons[MEDIUM].id = MEDIUM;
	max->menu.gamedifficultybuttons[MEDIUM].group = NEWDIFFICULTY;
	max->menu.gamedifficultybuttons[MEDIUM].up = &max->menu.gamedifficultybuttons[EASY];
	max->menu.gamedifficultybuttons[MEDIUM].down = &max->menu.gamedifficultybuttons[HARD];
	max->menu.gamedifficultybuttons[MEDIUM].state = ACTIVE;
	max->menu.gamedifficultybuttons[MEDIUM].x = 1000;
	max->menu.gamedifficultybuttons[MEDIUM].y = 400;
	max->menu.gamedifficultybuttons[MEDIUM].text.text = S_MEDIUM;
	max->menu.gamedifficultybuttons[MEDIUM].text.sx = max->menu.gamedifficultybuttons[MEDIUM].x + 40;
	max->menu.gamedifficultybuttons[MEDIUM].text.sy = max->menu.gamedifficultybuttons[MEDIUM].y + 40;
	max->menu.gamedifficultybuttons[HARD] = button;
	max->menu.gamedifficultybuttons[HARD].id = HARD;
	max->menu.gamedifficultybuttons[HARD].group = NEWDIFFICULTY;
	max->menu.gamedifficultybuttons[HARD].up = &max->menu.gamedifficultybuttons[MEDIUM];
	max->menu.gamedifficultybuttons[HARD].state = ACTIVE;
	max->menu.gamedifficultybuttons[HARD].x = 1000;
	max->menu.gamedifficultybuttons[HARD].y = 600;
	max->menu.gamedifficultybuttons[HARD].text.text = S_HARD;
	max->menu.gamedifficultybuttons[HARD].text.sx = max->menu.gamedifficultybuttons[HARD].x + 40;
	max->menu.gamedifficultybuttons[HARD].text.sy = max->menu.gamedifficultybuttons[HARD].y + 40;
	// max->menu.gamedifficultybuttons[GDBACK] = button;
	// max->menu.gamedifficultybuttons[GDBACK].id = GDBACK;
	// max->menu.gamedifficultybuttons[GDBACK].group = NEWDIFFICULTY;
	// max->menu.gamedifficultybuttons[GDBACK].up = &max->menu.gamedifficultybuttons[MEDIUM];
	// max->menu.gamedifficultybuttons[GDBACK].right = &max->menu.gamedifficultybuttons[GDCONTINUE];
	// max->menu.gamedifficultybuttons[GDBACK].state = ACTIVE;
	// max->menu.gamedifficultybuttons[GDBACK].x = 800;
	// max->menu.gamedifficultybuttons[GDBACK].y = 300;
	// max->menu.gamedifficultybuttons[GDBACK].text.text = S_BACK;
	// max->menu.gamedifficultybuttons[GDBACK].text.sx = max->menu.gamedifficultybuttons[GDBACK].x + 40;
	// max->menu.gamedifficultybuttons[GDBACK].text.sy = max->menu.gamedifficultybuttons[GDBACK].y + 40;
	// max->menu.gamedifficultybuttons[GDCONTINUE] = button;
	// max->menu.gamedifficultybuttons[GDCONTINUE].id = GDCONTINUE;
	// max->menu.gamedifficultybuttons[GDCONTINUE].group = NEWDIFFICULTY;
	// max->menu.gamedifficultybuttons[GDCONTINUE].up = &max->menu.gamedifficultybuttons[MEDIUM];
	// max->menu.gamedifficultybuttons[GDCONTINUE].left = &max->menu.gamedifficultybuttons[GDBACK];
	// max->menu.gamedifficultybuttons[GDCONTINUE].state = ACTIVE;
	// max->menu.gamedifficultybuttons[GDCONTINUE].x = 1200;
	// max->menu.gamedifficultybuttons[GDCONTINUE].y = 300;
	// max->menu.gamedifficultybuttons[GDCONTINUE].text.text = S_CONTINUE;
	// max->menu.gamedifficultybuttons[GDCONTINUE].text.sx = max->menu.gamedifficultybuttons[GDCONTINUE].x + 40;
	// max->menu.gamedifficultybuttons[GDCONTINUE].text.sy = max->menu.gamedifficultybuttons[GDCONTINUE].y + 40;
	max->menu.gametypebuttons[CAMPAIGN] = button;
	max->menu.gametypebuttons[CAMPAIGN].id = CAMPAIGN;
	max->menu.gametypebuttons[CAMPAIGN].group = NEWSELECTION;
	max->menu.gametypebuttons[CAMPAIGN].down = &max->menu.gametypebuttons[TIMETRIAL];
	max->menu.gametypebuttons[CAMPAIGN].state = ACTIVE;
	max->menu.gametypebuttons[CAMPAIGN].x = 1000;
	max->menu.gametypebuttons[CAMPAIGN].y = 200;
	max->menu.gametypebuttons[CAMPAIGN].text.text = S_CAMPAIGN;
	max->menu.gametypebuttons[CAMPAIGN].text.sx = max->menu.gametypebuttons[CAMPAIGN].x + 40;
	max->menu.gametypebuttons[CAMPAIGN].text.sy = max->menu.gametypebuttons[CAMPAIGN].y + 40;
	max->menu.gametypebuttons[TIMETRIAL] = button;
	max->menu.gametypebuttons[TIMETRIAL].id = TIMETRIAL;
	max->menu.gametypebuttons[TIMETRIAL].group = NEWSELECTION;
	max->menu.gametypebuttons[TIMETRIAL].up = &max->menu.gametypebuttons[CAMPAIGN];
	max->menu.gametypebuttons[TIMETRIAL].down = &max->menu.gametypebuttons[ONEMAP];
	max->menu.gametypebuttons[TIMETRIAL].state = ACTIVE;
	max->menu.gametypebuttons[TIMETRIAL].x = 1000;
	max->menu.gametypebuttons[TIMETRIAL].y = 400;
	max->menu.gametypebuttons[TIMETRIAL].text.text = S_TIMETRIAL;
	max->menu.gametypebuttons[TIMETRIAL].text.sx = max->menu.gametypebuttons[TIMETRIAL].x + 40;
	max->menu.gametypebuttons[TIMETRIAL].text.sy = max->menu.gametypebuttons[TIMETRIAL].y + 40;
	max->menu.gametypebuttons[ONEMAP] = button;
	max->menu.gametypebuttons[ONEMAP].id = ONEMAP;
	max->menu.gametypebuttons[ONEMAP].group = NEWSELECTION;
	max->menu.gametypebuttons[ONEMAP].up = &max->menu.gametypebuttons[TIMETRIAL];
	max->menu.gametypebuttons[ONEMAP].state = ACTIVE;
	max->menu.gametypebuttons[ONEMAP].x = 1000;
	max->menu.gametypebuttons[ONEMAP].y = 600;
	max->menu.gametypebuttons[ONEMAP].text.text = S_ONEMAP;
	max->menu.gametypebuttons[ONEMAP].text.sx = max->menu.gametypebuttons[ONEMAP].x + 40;
	max->menu.gametypebuttons[ONEMAP].text.sy = max->menu.gametypebuttons[ONEMAP].y + 40;
	// max->menu.gametypebuttons[GTBACK] = button;
	// max->menu.gametypebuttons[GTBACK].id = GTBACK;
	// max->menu.gametypebuttons[GTBACK].group = NEWSELECTION;
	// max->menu.gametypebuttons[GTBACK].up = &max->menu.gametypebuttons[ONEMAP]; //maybe change later to CAMAPIGN
	// max->menu.gametypebuttons[GTBACK].right = &max->menu.gametypebuttons[GTCONTINUE];
	// max->menu.gametypebuttons[GTBACK].state = ACTIVE;
	// max->menu.gametypebuttons[GTBACK].x = 800;
	// max->menu.gametypebuttons[GTBACK].y = 300;
	// max->menu.gametypebuttons[GTBACK].text.text = S_BACK;
	// max->menu.gametypebuttons[GTBACK].text.sx = max->menu.gametypebuttons[GTBACK].x + 40;
	// max->menu.gametypebuttons[GTBACK].text.sy = max->menu.gametypebuttons[GTBACK].y + 40;
	// max->menu.gametypebuttons[GTCONTINUE] = button;
	// max->menu.gametypebuttons[GTCONTINUE].id = GTCONTINUE;
	// max->menu.gametypebuttons[GTCONTINUE].group = NEWSELECTION;
	// max->menu.gametypebuttons[GTCONTINUE].up = &max->menu.gametypebuttons[ONEMAP]; //maybe change later to CAMAPIGN
	// max->menu.gametypebuttons[GTCONTINUE].left = &max->menu.gametypebuttons[GTBACK];
	// max->menu.gametypebuttons[GTCONTINUE].state = ACTIVE;
	// max->menu.gametypebuttons[GTCONTINUE].x = 1200;
	// max->menu.gametypebuttons[GTCONTINUE].y = 300;
	// max->menu.gametypebuttons[GTCONTINUE].text.text = S_CONTINUE;
	// max->menu.gametypebuttons[GTCONTINUE].text.sx = max->menu.gametypebuttons[GTCONTINUE].x + 40;
	// max->menu.gametypebuttons[GTCONTINUE].text.sy = max->menu.gametypebuttons[GTCONTINUE].y + 40;
	max->menu.maptypebuttons[CUSTOM] = button;
	max->menu.maptypebuttons[CUSTOM].id = CUSTOM;
	max->menu.maptypebuttons[CUSTOM].group = NEWLEVEL;
	max->menu.maptypebuttons[CUSTOM].down = &max->menu.maptypebuttons[RANDOM];
	max->menu.maptypebuttons[CUSTOM].state = ACTIVE;
	max->menu.maptypebuttons[CUSTOM].x = 1000;
	max->menu.maptypebuttons[CUSTOM].y = 300;
	max->menu.maptypebuttons[CUSTOM].text.text = S_CUSTOM;
	max->menu.maptypebuttons[CUSTOM].text.sx = max->menu.maptypebuttons[CUSTOM].x + 40;
	max->menu.maptypebuttons[CUSTOM].text.sy = max->menu.maptypebuttons[CUSTOM].y + 40;
	max->menu.maptypebuttons[RANDOM] = button;
	max->menu.maptypebuttons[RANDOM].id = RANDOM;
	max->menu.maptypebuttons[RANDOM].group = NEWLEVEL;
	max->menu.maptypebuttons[RANDOM].up = &max->menu.maptypebuttons[CUSTOM];
	max->menu.maptypebuttons[RANDOM].state = ACTIVE;
	max->menu.maptypebuttons[RANDOM].x = 1000;
	max->menu.maptypebuttons[RANDOM].y = 600;
	max->menu.maptypebuttons[RANDOM].text.text = S_RANDOM;
	max->menu.maptypebuttons[RANDOM].text.sx = max->menu.maptypebuttons[RANDOM].x + 40;
	max->menu.maptypebuttons[RANDOM].text.sy = max->menu.maptypebuttons[RANDOM].y + 40;
	// max->menu.maptypebuttons[MTBACK] = button;
	// max->menu.maptypebuttons[MTBACK].id = MTBACK;
	// max->menu.maptypebuttons[MTBACK].group = NEWLEVEL;
	// max->menu.maptypebuttons[MTBACK].up = &max->menu.maptypebuttons[CUSTOM];
	// max->menu.maptypebuttons[MTBACK].state = ACTIVE;
	// max->menu.maptypebuttons[MTBACK].x = 800;
	// max->menu.maptypebuttons[MTBACK].y = 860;
	// max->menu.maptypebuttons[MTBACK].text.text = S_BACK;
	// max->menu.maptypebuttons[MTBACK].text.sx = max->menu.maptypebuttons[MTBACK].x + 40;
	// max->menu.maptypebuttons[MTBACK].text.sy = max->menu.maptypebuttons[MTBACK].y + 40;
	max->menu.mapselectionbuttons[CHOOSELEVEL] = button;
	max->menu.mapselectionbuttons[CHOOSELEVEL].id = CUSTOM;
	max->menu.mapselectionbuttons[CHOOSELEVEL].group = NEWMAP;
	max->menu.mapselectionbuttons[CHOOSELEVEL].down = &max->menu.mapselectionbuttons[MSPLAY];
	max->menu.mapselectionbuttons[CHOOSELEVEL].state = ACTIVE;
	max->menu.mapselectionbuttons[CHOOSELEVEL].x = 800;
	max->menu.mapselectionbuttons[CHOOSELEVEL].y = 20;
	max->menu.mapselectionbuttons[CHOOSELEVEL].text.text = S_CHOOSELEVEL;
	max->menu.mapselectionbuttons[CHOOSELEVEL].text.sx = max->menu.mapselectionbuttons[CHOOSELEVEL].x + 40;
	max->menu.mapselectionbuttons[CHOOSELEVEL].text.sy = max->menu.mapselectionbuttons[CHOOSELEVEL].y + 40;
	// max->menu.mapselectionbuttons[RANDOM] = button;
	// max->menu.mapselectionbuttons[RANDOM].id = RANDOM;
	// max->menu.mapselectionbuttons[RANDOM].group = NEWMAP;
	// max->menu.mapselectionbuttons[RANDOM].left = &max->menu.mapselectionbuttons[CHOOSELEVEL];
	// max->menu.mapselectionbuttons[RANDOM].down = &max->menu.mapselectionbuttons[MSPLAY];
	// max->menu.mapselectionbuttons[RANDOM].state = ACTIVE;
	// max->menu.mapselectionbuttons[RANDOM].x = 1200;
	// max->menu.mapselectionbuttons[RANDOM].y = 20;
	// max->menu.mapselectionbuttons[RANDOM].text.text = S_RANDOM;
	// max->menu.mapselectionbuttons[RANDOM].text.sx = max->menu.mapselectionbuttons[RANDOM].x + 40;
	// max->menu.mapselectionbuttons[RANDOM].text.sy = max->menu.mapselectionbuttons[RANDOM].y + 40;
	// max->menu.mapselectionbuttons[MSBACK] = button;
	// max->menu.mapselectionbuttons[MSBACK].id = MSBACK;
	// max->menu.mapselectionbuttons[MSBACK].group = NEWMAP;
	// max->menu.mapselectionbuttons[MSBACK].up = &max->menu.mapselectionbuttons[CHOOSELEVEL];
	// max->menu.mapselectionbuttons[MSBACK].right = &max->menu.mapselectionbuttons[MSPLAY];
	// max->menu.mapselectionbuttons[MSBACK].state = ACTIVE;
	// max->menu.mapselectionbuttons[MSBACK].x = 800;
	// max->menu.mapselectionbuttons[MSBACK].y = 860;
	// max->menu.mapselectionbuttons[MSBACK].text.text = S_BACK;
	// max->menu.mapselectionbuttons[MSBACK].text.sx = max->menu.mapselectionbuttons[MSBACK].x + 40;
	// max->menu.mapselectionbuttons[MSBACK].text.sy = max->menu.mapselectionbuttons[MSBACK].y + 40;
	max->menu.mapselectionbuttons[MSPLAY] = button;
	max->menu.mapselectionbuttons[MSPLAY].id = MSPLAY;
	max->menu.mapselectionbuttons[MSPLAY].group = NEWMAP;
	max->menu.mapselectionbuttons[MSPLAY].up = &max->menu.mapselectionbuttons[CHOOSELEVEL];
	max->menu.mapselectionbuttons[MSPLAY].state = INACTIVE;
	max->menu.mapselectionbuttons[MSPLAY].x = 1200;
	max->menu.mapselectionbuttons[MSPLAY].y = 860;
	max->menu.mapselectionbuttons[MSPLAY].text.text = S_PLAY;
	max->menu.mapselectionbuttons[MSPLAY].text.sx = max->menu.mapselectionbuttons[MSPLAY].x + 40;
	max->menu.mapselectionbuttons[MSPLAY].text.sy = max->menu.mapselectionbuttons[MSPLAY].y + 40;
	max->menu.randomselectionbuttons[RSPLAY] = button;
	max->menu.randomselectionbuttons[RSPLAY].id = RSPLAY;
	max->menu.randomselectionbuttons[RSPLAY].group = NEWRANDOM;
	max->menu.randomselectionbuttons[RSPLAY].down = &max->menu.randomselectionbuttons[RSADVANCED];
	max->menu.randomselectionbuttons[RSPLAY].state = ACTIVE;
	max->menu.randomselectionbuttons[RSPLAY].x = 1000;
	max->menu.randomselectionbuttons[RSPLAY].y = 300;
	max->menu.randomselectionbuttons[RSPLAY].text.text = S_PLAY;
	max->menu.randomselectionbuttons[RSPLAY].text.sx = max->menu.randomselectionbuttons[RSPLAY].x + 40;
	max->menu.randomselectionbuttons[RSPLAY].text.sy = max->menu.randomselectionbuttons[RSPLAY].y + 40;
	max->menu.randomselectionbuttons[RSADVANCED] = button;
	max->menu.randomselectionbuttons[RSADVANCED].id = RSADVANCED;
	max->menu.randomselectionbuttons[RSADVANCED].group = NEWRANDOM;
	max->menu.randomselectionbuttons[RSADVANCED].up = &max->menu.randomselectionbuttons[RSPLAY];
	max->menu.randomselectionbuttons[RSADVANCED].state = ACTIVE;
	max->menu.randomselectionbuttons[RSADVANCED].x = 1000;
	max->menu.randomselectionbuttons[RSADVANCED].y = 600;
	max->menu.randomselectionbuttons[RSADVANCED].text.text = S_ADVANCED;
	max->menu.randomselectionbuttons[RSADVANCED].text.sx = max->menu.randomselectionbuttons[RSADVANCED].x + 40;
	max->menu.randomselectionbuttons[RSADVANCED].text.sy = max->menu.randomselectionbuttons[RSADVANCED].y + 40;
// 	# define RWIDTH 0
// # define RHEIGHT 1
// # define RRATIODE 2 //deadends || loops || T || X
// # define RRATIOLO 3
// # define RRATIOTI 4
// # define RRATIOXI 5
// # define RNOROOMS 6
// # define ROROOMS 7
// # define RDOORS 8
// # define RDEADENDS 9
// # define RRANDOMIZE 10
// # define RPLAY 11
// # define RANDOMADVANCEDBUTTONCOUNT 12
	button.button = max->menu.buttonplus;
	button.text.height = 40;
	max->menu.randomadvancedbuttons[RWIDTH] = button;
	max->menu.randomadvancedbuttons[RWIDTH].id = RWIDTH;
	max->menu.randomadvancedbuttons[RWIDTH].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RWIDTH].down = &max->menu.randomadvancedbuttons[RRATIODE];
	max->menu.randomadvancedbuttons[RWIDTH].right = &max->menu.randomadvancedbuttons[RHEIGHT];
	max->menu.randomadvancedbuttons[RWIDTH].state = ACTIVE;
	max->menu.randomadvancedbuttons[RWIDTH].x = 700;
	max->menu.randomadvancedbuttons[RWIDTH].y = 20;
	max->menu.randomadvancedbuttons[RWIDTH].str = S_RWIDTH;
	max->menu.randomadvancedbuttons[RWIDTH].val = &max->menu.rm.width;
	ft_snprintf(max->menu.randomadvancedbuttons[RWIDTH].text.str, 19, "%s: %i", S_RWIDTH, max->menu.randomadvancedbuttons[RWIDTH].val->value);
	max->menu.randomadvancedbuttons[RWIDTH].text.text = max->menu.randomadvancedbuttons[RWIDTH].text.str;
	max->menu.randomadvancedbuttons[RWIDTH].text.sx = max->menu.randomadvancedbuttons[RWIDTH].x + 110;
	max->menu.randomadvancedbuttons[RWIDTH].text.sy = max->menu.randomadvancedbuttons[RWIDTH].y + 50;
	max->menu.randomadvancedbuttons[RHEIGHT] = button;
	max->menu.randomadvancedbuttons[RHEIGHT].id = RHEIGHT;
	max->menu.randomadvancedbuttons[RHEIGHT].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RHEIGHT].down = &max->menu.randomadvancedbuttons[RRATIOLO];
	max->menu.randomadvancedbuttons[RHEIGHT].left = &max->menu.randomadvancedbuttons[RWIDTH];
	max->menu.randomadvancedbuttons[RHEIGHT].state = ACTIVE;
	max->menu.randomadvancedbuttons[RHEIGHT].x = 1250;
	max->menu.randomadvancedbuttons[RHEIGHT].y = 20;
	max->menu.randomadvancedbuttons[RHEIGHT].str = S_RHEIGHT;
	max->menu.randomadvancedbuttons[RHEIGHT].val = &max->menu.rm.height;
	ft_snprintf(max->menu.randomadvancedbuttons[RHEIGHT].text.str, 19, "%s: %i", S_RHEIGHT, max->menu.randomadvancedbuttons[RHEIGHT].val->value);
	max->menu.randomadvancedbuttons[RHEIGHT].text.text = max->menu.randomadvancedbuttons[RHEIGHT].text.str;
	max->menu.randomadvancedbuttons[RHEIGHT].text.sx = max->menu.randomadvancedbuttons[RHEIGHT].x + 110;
	max->menu.randomadvancedbuttons[RHEIGHT].text.sy = max->menu.randomadvancedbuttons[RHEIGHT].y + 50;
	max->menu.randomadvancedbuttons[RRATIODE] = button;
	max->menu.randomadvancedbuttons[RRATIODE].id = RRATIODE;
	max->menu.randomadvancedbuttons[RRATIODE].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIODE].up = &max->menu.randomadvancedbuttons[RWIDTH];
	max->menu.randomadvancedbuttons[RRATIODE].down = &max->menu.randomadvancedbuttons[RRATIOTI];
	max->menu.randomadvancedbuttons[RRATIODE].right = &max->menu.randomadvancedbuttons[RRATIOLO];
	max->menu.randomadvancedbuttons[RRATIODE].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIODE].x = 700;
	max->menu.randomadvancedbuttons[RRATIODE].y = 160;
	max->menu.randomadvancedbuttons[RRATIODE].str = S_RRATIODE;
	max->menu.randomadvancedbuttons[RRATIODE].val = &max->menu.rm.ratiode;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIODE].text.str, 19, "%s: %i", S_RRATIODE, max->menu.randomadvancedbuttons[RRATIODE].val->value);
	max->menu.randomadvancedbuttons[RRATIODE].text.text = max->menu.randomadvancedbuttons[RRATIODE].text.str;
	max->menu.randomadvancedbuttons[RRATIODE].text.sx = max->menu.randomadvancedbuttons[RRATIODE].x + 110;
	max->menu.randomadvancedbuttons[RRATIODE].text.sy = max->menu.randomadvancedbuttons[RRATIODE].y + 50;
	max->menu.randomadvancedbuttons[RRATIOLO] = button;
	max->menu.randomadvancedbuttons[RRATIOLO].id = RRATIOLO;
	max->menu.randomadvancedbuttons[RRATIOLO].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIOLO].up = &max->menu.randomadvancedbuttons[RHEIGHT];
	max->menu.randomadvancedbuttons[RRATIOLO].down = &max->menu.randomadvancedbuttons[RRATIOXI];
	max->menu.randomadvancedbuttons[RRATIOLO].left = &max->menu.randomadvancedbuttons[RRATIODE];
	max->menu.randomadvancedbuttons[RRATIOLO].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIOLO].x = 1250;
	max->menu.randomadvancedbuttons[RRATIOLO].y = 160;
	max->menu.randomadvancedbuttons[RRATIOLO].str = S_RRATIOLO;
	max->menu.randomadvancedbuttons[RRATIOLO].val = &max->menu.rm.ratiolo;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIOLO].text.str, 19, "%s: %i", S_RRATIOLO, max->menu.randomadvancedbuttons[RRATIOLO].val->value);
	max->menu.randomadvancedbuttons[RRATIOLO].text.text = max->menu.randomadvancedbuttons[RRATIOLO].text.str;
	max->menu.randomadvancedbuttons[RRATIOLO].text.sx = max->menu.randomadvancedbuttons[RRATIOLO].x + 110;
	max->menu.randomadvancedbuttons[RRATIOLO].text.sy = max->menu.randomadvancedbuttons[RRATIOLO].y + 50;
	max->menu.randomadvancedbuttons[RRATIOTI] = button;
	max->menu.randomadvancedbuttons[RRATIOTI].id = RRATIOTI;
	max->menu.randomadvancedbuttons[RRATIOTI].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIOTI].up = &max->menu.randomadvancedbuttons[RRATIODE];
	max->menu.randomadvancedbuttons[RRATIOTI].down = &max->menu.randomadvancedbuttons[RNOROOMS];
	max->menu.randomadvancedbuttons[RRATIOTI].right = &max->menu.randomadvancedbuttons[RRATIOXI];
	max->menu.randomadvancedbuttons[RRATIOTI].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIOTI].x = 700;
	max->menu.randomadvancedbuttons[RRATIOTI].y = 300;
	max->menu.randomadvancedbuttons[RRATIOTI].str = S_RRATIOTI;
	max->menu.randomadvancedbuttons[RRATIOTI].val = &max->menu.rm.ratioti;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIOTI].text.str, 19, "%s: %i", S_RRATIOTI, max->menu.randomadvancedbuttons[RRATIOTI].val->value);
	max->menu.randomadvancedbuttons[RRATIOTI].text.text = max->menu.randomadvancedbuttons[RRATIOTI].text.str;
	max->menu.randomadvancedbuttons[RRATIOTI].text.sx = max->menu.randomadvancedbuttons[RRATIOTI].x + 110;
	max->menu.randomadvancedbuttons[RRATIOTI].text.sy = max->menu.randomadvancedbuttons[RRATIOTI].y + 50;
	max->menu.randomadvancedbuttons[RRATIOXI] = button;
	max->menu.randomadvancedbuttons[RRATIOXI].id = RRATIOXI;
	max->menu.randomadvancedbuttons[RRATIOXI].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRATIOXI].up = &max->menu.randomadvancedbuttons[RRATIOLO];
	max->menu.randomadvancedbuttons[RRATIOXI].down = &max->menu.randomadvancedbuttons[ROROOMS];
	max->menu.randomadvancedbuttons[RRATIOXI].left = &max->menu.randomadvancedbuttons[RRATIOTI];
	max->menu.randomadvancedbuttons[RRATIOXI].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRATIOXI].x = 1250;
	max->menu.randomadvancedbuttons[RRATIOXI].y = 300;
	max->menu.randomadvancedbuttons[RRATIOXI].str = S_RRATIOXI;
	max->menu.randomadvancedbuttons[RRATIOXI].val = &max->menu.rm.ratioxi;
	ft_snprintf(max->menu.randomadvancedbuttons[RRATIOXI].text.str, 19, "%s: %i", S_RRATIOXI, max->menu.randomadvancedbuttons[RRATIOXI].val->value);
	max->menu.randomadvancedbuttons[RRATIOXI].text.text = max->menu.randomadvancedbuttons[RRATIOXI].text.str;
	max->menu.randomadvancedbuttons[RRATIOXI].text.sx = max->menu.randomadvancedbuttons[RRATIOXI].x + 110;
	max->menu.randomadvancedbuttons[RRATIOXI].text.sy = max->menu.randomadvancedbuttons[RRATIOXI].y + 50;
	max->menu.randomadvancedbuttons[RNOROOMS] = button;
	max->menu.randomadvancedbuttons[RNOROOMS].id = RNOROOMS;
	max->menu.randomadvancedbuttons[RNOROOMS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RNOROOMS].up = &max->menu.randomadvancedbuttons[RRATIOTI];
	max->menu.randomadvancedbuttons[RNOROOMS].down = &max->menu.randomadvancedbuttons[RDOORS];
	max->menu.randomadvancedbuttons[RNOROOMS].right = &max->menu.randomadvancedbuttons[ROROOMS];
	max->menu.randomadvancedbuttons[RNOROOMS].state = ACTIVE;
	max->menu.randomadvancedbuttons[RNOROOMS].x = 700;
	max->menu.randomadvancedbuttons[RNOROOMS].y = 440;
	max->menu.randomadvancedbuttons[RNOROOMS].str = S_RNOROOMS;
	max->menu.randomadvancedbuttons[RNOROOMS].val = &max->menu.rm.rnorooms;
	ft_snprintf(max->menu.randomadvancedbuttons[RNOROOMS].text.str, 19, "%s: %i", S_RNOROOMS, max->menu.randomadvancedbuttons[RNOROOMS].val->value);
	max->menu.randomadvancedbuttons[RNOROOMS].text.text = max->menu.randomadvancedbuttons[RNOROOMS].text.str;
	max->menu.randomadvancedbuttons[RNOROOMS].text.sx = max->menu.randomadvancedbuttons[RNOROOMS].x + 110;
	max->menu.randomadvancedbuttons[RNOROOMS].text.sy = max->menu.randomadvancedbuttons[RNOROOMS].y + 50;
	max->menu.randomadvancedbuttons[ROROOMS] = button;
	max->menu.randomadvancedbuttons[ROROOMS].id = ROROOMS;
	max->menu.randomadvancedbuttons[ROROOMS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[ROROOMS].up = &max->menu.randomadvancedbuttons[RRATIOXI];
	max->menu.randomadvancedbuttons[ROROOMS].down = &max->menu.randomadvancedbuttons[RDEADENDS];
	max->menu.randomadvancedbuttons[ROROOMS].left = &max->menu.randomadvancedbuttons[RNOROOMS];
	max->menu.randomadvancedbuttons[ROROOMS].state = ACTIVE;
	max->menu.randomadvancedbuttons[ROROOMS].x = 1250;
	max->menu.randomadvancedbuttons[ROROOMS].y = 440;
	max->menu.randomadvancedbuttons[ROROOMS].str = S_ROROOMS;
	max->menu.randomadvancedbuttons[ROROOMS].val = &max->menu.rm.rorooms;
	ft_snprintf(max->menu.randomadvancedbuttons[ROROOMS].text.str, 19, "%s: %i", S_ROROOMS, max->menu.randomadvancedbuttons[ROROOMS].val->value);
	max->menu.randomadvancedbuttons[ROROOMS].text.text = max->menu.randomadvancedbuttons[ROROOMS].text.str;
	max->menu.randomadvancedbuttons[ROROOMS].text.sx = max->menu.randomadvancedbuttons[ROROOMS].x + 110;
	max->menu.randomadvancedbuttons[ROROOMS].text.sy = max->menu.randomadvancedbuttons[ROROOMS].y + 50;
	max->menu.randomadvancedbuttons[RDOORS] = button;
	max->menu.randomadvancedbuttons[RDOORS].id = RDOORS;
	max->menu.randomadvancedbuttons[RDOORS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RDOORS].up = &max->menu.randomadvancedbuttons[RNOROOMS];
	max->menu.randomadvancedbuttons[RDOORS].down = &max->menu.randomadvancedbuttons[RPLAY];
	max->menu.randomadvancedbuttons[RDOORS].right = &max->menu.randomadvancedbuttons[RDEADENDS];
	max->menu.randomadvancedbuttons[RDOORS].state = ACTIVE;
	max->menu.randomadvancedbuttons[RDOORS].x = 700;
	max->menu.randomadvancedbuttons[RDOORS].y = 580;
	max->menu.randomadvancedbuttons[RDOORS].str = S_RDOORS;
	max->menu.randomadvancedbuttons[RDOORS].val = &max->menu.rm.rdoors;
	ft_snprintf(max->menu.randomadvancedbuttons[RDOORS].text.str, 19, "%s: %i", S_RDOORS, max->menu.randomadvancedbuttons[RDOORS].val->value);
	max->menu.randomadvancedbuttons[RDOORS].text.text = max->menu.randomadvancedbuttons[RDOORS].text.str;
	max->menu.randomadvancedbuttons[RDOORS].text.sx = max->menu.randomadvancedbuttons[RDOORS].x + 110;
	max->menu.randomadvancedbuttons[RDOORS].text.sy = max->menu.randomadvancedbuttons[RDOORS].y + 50;
	max->menu.randomadvancedbuttons[RDEADENDS] = button;
	max->menu.randomadvancedbuttons[RDEADENDS].id = RDEADENDS;
	max->menu.randomadvancedbuttons[RDEADENDS].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RDEADENDS].up = &max->menu.randomadvancedbuttons[ROROOMS];
	max->menu.randomadvancedbuttons[RDEADENDS].down = &max->menu.randomadvancedbuttons[RPLAY];
	max->menu.randomadvancedbuttons[RDEADENDS].left = &max->menu.randomadvancedbuttons[RDOORS];
	max->menu.randomadvancedbuttons[RDEADENDS].state = ACTIVE;
	max->menu.randomadvancedbuttons[RDEADENDS].x = 1250;
	max->menu.randomadvancedbuttons[RDEADENDS].y = 580;
	max->menu.randomadvancedbuttons[RDEADENDS].str = S_RDEADENDS;
	max->menu.randomadvancedbuttons[RDEADENDS].val = &max->menu.rm.rdeadends;
	ft_snprintf(max->menu.randomadvancedbuttons[RDEADENDS].text.str, 19, "%s: %i", S_RDEADENDS, max->menu.randomadvancedbuttons[RDEADENDS].val->value);
	max->menu.randomadvancedbuttons[RDEADENDS].text.text = max->menu.randomadvancedbuttons[RDEADENDS].text.str;
	max->menu.randomadvancedbuttons[RDEADENDS].text.sx = max->menu.randomadvancedbuttons[RDEADENDS].x + 110;
	max->menu.randomadvancedbuttons[RDEADENDS].text.sy = max->menu.randomadvancedbuttons[RDEADENDS].y + 50;
	button.text.height = 60;
	button.button = max->menu.button;
	max->menu.randomadvancedbuttons[RRANDOMIZE] = button;
	max->menu.randomadvancedbuttons[RRANDOMIZE].id = RRANDOMIZE;
	max->menu.randomadvancedbuttons[RRANDOMIZE].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RRANDOMIZE].up = &max->menu.randomadvancedbuttons[RDOORS];
	max->menu.randomadvancedbuttons[RRANDOMIZE].right = &max->menu.randomadvancedbuttons[RPLAY];
	max->menu.randomadvancedbuttons[RRANDOMIZE].state = ACTIVE;
	max->menu.randomadvancedbuttons[RRANDOMIZE].x = 850;
	max->menu.randomadvancedbuttons[RRANDOMIZE].y = 860;
	max->menu.randomadvancedbuttons[RRANDOMIZE].text.text = S_RANDOMIZE;
	max->menu.randomadvancedbuttons[RRANDOMIZE].text.sx = max->menu.randomadvancedbuttons[RRANDOMIZE].x + 40;
	max->menu.randomadvancedbuttons[RRANDOMIZE].text.sy = max->menu.randomadvancedbuttons[RRANDOMIZE].y + 40;
	max->menu.randomadvancedbuttons[RPLAY] = button;
	max->menu.randomadvancedbuttons[RPLAY].id = RPLAY;
	max->menu.randomadvancedbuttons[RPLAY].group = NEWRANDOMADVANCED;
	max->menu.randomadvancedbuttons[RPLAY].up = &max->menu.randomadvancedbuttons[RDEADENDS];
	max->menu.randomadvancedbuttons[RPLAY].left = &max->menu.randomadvancedbuttons[RRANDOMIZE];
	max->menu.randomadvancedbuttons[RPLAY].state = ACTIVE;
	max->menu.randomadvancedbuttons[RPLAY].x = 1250;
	max->menu.randomadvancedbuttons[RPLAY].y = 860;
	max->menu.randomadvancedbuttons[RPLAY].text.text = S_PLAY;
	max->menu.randomadvancedbuttons[RPLAY].text.sx = max->menu.randomadvancedbuttons[RPLAY].x + 40;
	max->menu.randomadvancedbuttons[RPLAY].text.sy = max->menu.randomadvancedbuttons[RPLAY].y + 40;
	max->menu.halloffamebuttons[HOFBACK] = button;
	max->menu.halloffamebuttons[HOFBACK].id = HOFBACK;
	max->menu.halloffamebuttons[HOFBACK].group = HALLOFFAMEGROUP;
	max->menu.halloffamebuttons[HOFBACK].state = ACTIVE;
	max->menu.halloffamebuttons[HOFBACK].x = 1250;
	max->menu.halloffamebuttons[HOFBACK].y = 860;
	max->menu.halloffamebuttons[HOFBACK].text.text = S_BACK;
	max->menu.halloffamebuttons[HOFBACK].text.sx = max->menu.halloffamebuttons[HOFBACK].x + 40;
	max->menu.halloffamebuttons[HOFBACK].text.sy = max->menu.halloffamebuttons[HOFBACK].y + 40;
}

void	ft_draw_button(t_button *b, int state)
{
	int				w;
	int				h;
	int				j;
	int				i;
	int				a;
	unsigned int	c;

	b->state = state;
	w = b->button->width;
	h = b->button->height;
	j = 0;
	//draw button
	//printf("%i %i\n", b->id, state);
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			a = (j * w * 4) + (i * 4);
			if (i < w && j < h)
				c = (b->button->pixels[a]) << 24 | (b->button->pixels[a + 1]) << 16 | (b->button->pixels[a + 2]) << 8 | (b->button->pixels[a + 3]);
			else
				c = 0xFF00FFFF;
			if (c & 0xFFFFFF00)
			{
				if (state & INACTIVE)
					mlx_put_pixel(b->image, i + b->x, j + b->y, C_INACTIVE);
				else if (state & ACTIVE)
					mlx_put_pixel(b->image, i + b->x, j + b->y, C_ACTIVE);
				else if (state & SELECTED)
					mlx_put_pixel(b->image, i + b->x, j + b->y, C_SELECTED);
				else if (state & ACTIVATED)
					mlx_put_pixel(b->image, i + b->x, j + b->y, C_ACTIVATED);
			}
			else if ((c & 0xFF) == 0xFF)
				mlx_put_pixel(b->image, i + b->x, j + b->y, c);
			++i;
		}
		++j;
	}
	//draw text
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
	ft_snprintf(button->text.str, 19, "%s: %i", button->str, button->val->value);
}
