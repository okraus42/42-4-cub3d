/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:42:26 by okraus            #+#    #+#             */
/*   Updated: 2024/03/28 11:03:59 by okraus           ###   ########.fr       */
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

	text.font = max->font.asciitest;
	text.image = max->menuscreen;
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
	button.image = max->menuscreen;
	button.text = text;
	button.c = C_INACTIVE;
	button.x = 200;
	button.y = 0;
	button.w = 350;
	button.h = 150;
	button.state = INACTIVE;
	max->menu.mainbuttons[RESUME] = button;
	max->menu.mainbuttons[RESUME].y = 20;
	max->menu.mainbuttons[RESUME].text.text = S_RESUME;
	max->menu.mainbuttons[RESUME].text.sx = max->menu.mainbuttons[RESUME].x + 40;
	max->menu.mainbuttons[RESUME].text.sy = max->menu.mainbuttons[RESUME].y + 40;
	max->menu.mainbuttons[NEWGAME] = button;
	max->menu.mainbuttons[NEWGAME].state = SELECTED;
	max->menu.mainbuttons[NEWGAME].y = 160;
	max->menu.mainbuttons[NEWGAME].text.text = S_NEWGAME;
	max->menu.mainbuttons[NEWGAME].text.sx = max->menu.mainbuttons[NEWGAME].x + 40;
	max->menu.mainbuttons[NEWGAME].text.sy = max->menu.mainbuttons[NEWGAME].y + 40;
	max->menu.mainbuttons[SAVEGAME] = button;
	max->menu.mainbuttons[SAVEGAME].y = 300;
	max->menu.mainbuttons[SAVEGAME].text.text = S_SAVEGAME;
	max->menu.mainbuttons[SAVEGAME].text.sx = max->menu.mainbuttons[SAVEGAME].x + 40;
	max->menu.mainbuttons[SAVEGAME].text.sy = max->menu.mainbuttons[SAVEGAME].y + 40;
	max->menu.mainbuttons[LOADGAME] = button;
	max->menu.mainbuttons[LOADGAME].y = 440;
	max->menu.mainbuttons[LOADGAME].text.text = S_LOADGAME;
	max->menu.mainbuttons[LOADGAME].text.sx = max->menu.mainbuttons[LOADGAME].x + 40;
	max->menu.mainbuttons[LOADGAME].text.sy = max->menu.mainbuttons[LOADGAME].y + 40;
	max->menu.mainbuttons[SETTINGS] = button;
	max->menu.mainbuttons[SETTINGS].y = 580;
	max->menu.mainbuttons[SETTINGS].text.text = S_SETTINGS;
	max->menu.mainbuttons[SETTINGS].text.sx = max->menu.mainbuttons[SETTINGS].x + 40;
	max->menu.mainbuttons[SETTINGS].text.sy = max->menu.mainbuttons[SETTINGS].y + 40;
	max->menu.mainbuttons[HALLOFFAME] = button;
	max->menu.mainbuttons[HALLOFFAME].y = 720;
	max->menu.mainbuttons[HALLOFFAME].text.text = S_HALLOFFAME;
	max->menu.mainbuttons[HALLOFFAME].text.sx = max->menu.mainbuttons[HALLOFFAME].x + 40;
	max->menu.mainbuttons[HALLOFFAME].text.sy = max->menu.mainbuttons[HALLOFFAME].y + 40;
	max->menu.mainbuttons[HALLOFFAME].text.height = 40;
	max->menu.mainbuttons[QUITGAME] = button;
	max->menu.mainbuttons[QUITGAME].state = ACTIVE;
	max->menu.mainbuttons[QUITGAME].y = 860;
	max->menu.mainbuttons[QUITGAME].text.text = S_QUITGAME;
	max->menu.mainbuttons[QUITGAME].text.sx = max->menu.mainbuttons[QUITGAME].x + 40;
	max->menu.mainbuttons[QUITGAME].text.sy = max->menu.mainbuttons[QUITGAME].y + 40;
	max->menu.newwritingbuttons[NAME] = button;
	max->menu.newwritingbuttons[NAME].state = ACTIVE;
	max->menu.newwritingbuttons[NAME].x = 600;
	max->menu.newwritingbuttons[NAME].y = 20;
	max->menu.newwritingbuttons[NAME].text.text = S_NAME;
	max->menu.newwritingbuttons[NAME].text.sx = max->menu.newwritingbuttons[NAME].x + 40;
	max->menu.newwritingbuttons[NAME].text.sy = max->menu.newwritingbuttons[NAME].y + 40;
	max->menu.newwritingbuttons[COALITION] = button;
	max->menu.newwritingbuttons[COALITION].state = ACTIVE;
	max->menu.newwritingbuttons[COALITION].x = 600;
	max->menu.newwritingbuttons[COALITION].y = 300;
	max->menu.newwritingbuttons[COALITION].text.text = S_COALITION;
	max->menu.newwritingbuttons[COALITION].text.sx = max->menu.newwritingbuttons[COALITION].x + 40;
	max->menu.newwritingbuttons[COALITION].text.sy = max->menu.newwritingbuttons[COALITION].y + 40;
	max->menu.newwritingbuttons[CAMPUS] = button;
	max->menu.newwritingbuttons[CAMPUS].state = ACTIVE;
	max->menu.newwritingbuttons[CAMPUS].x = 600;
	max->menu.newwritingbuttons[CAMPUS].y = 580;
	max->menu.newwritingbuttons[CAMPUS].text.text = S_CAMPUS;
	max->menu.newwritingbuttons[CAMPUS].text.sx = max->menu.newwritingbuttons[CAMPUS].x + 40;
	max->menu.newwritingbuttons[CAMPUS].text.sy = max->menu.newwritingbuttons[CAMPUS].y + 40;
	max->menu.newwritingbuttons[NWBACK] = button;
	max->menu.newwritingbuttons[NWBACK].state = ACTIVE;
	max->menu.newwritingbuttons[NWBACK].x = 800;
	max->menu.newwritingbuttons[NWBACK].y = 860;
	max->menu.newwritingbuttons[NWBACK].text.text = S_BACK;
	max->menu.newwritingbuttons[NWBACK].text.sx = max->menu.newwritingbuttons[NWBACK].x + 40;
	max->menu.newwritingbuttons[NWBACK].text.sy = max->menu.newwritingbuttons[NWBACK].y + 40;
	max->menu.newwritingbuttons[NWCONTINUE] = button;
	max->menu.newwritingbuttons[NWCONTINUE].state = ACTIVE;
	max->menu.newwritingbuttons[NWCONTINUE].x = 1200;
	max->menu.newwritingbuttons[NWCONTINUE].y = 860;
	max->menu.newwritingbuttons[NWCONTINUE].text.text = S_CONTINUE;
	max->menu.newwritingbuttons[NWCONTINUE].text.sx = max->menu.newwritingbuttons[NWCONTINUE].x + 40;
	max->menu.newwritingbuttons[NWCONTINUE].text.sy = max->menu.newwritingbuttons[NWCONTINUE].y + 40;
	max->menu.gamedifficultybuttons[EASY] = button;
	max->menu.gamedifficultybuttons[EASY].state = ACTIVE;
	max->menu.gamedifficultybuttons[EASY].x = 600;
	max->menu.gamedifficultybuttons[EASY].y = 100;
	max->menu.gamedifficultybuttons[EASY].text.text = S_EASY;
	max->menu.gamedifficultybuttons[EASY].text.sx = max->menu.gamedifficultybuttons[EASY].x + 40;
	max->menu.gamedifficultybuttons[EASY].text.sy = max->menu.gamedifficultybuttons[EASY].y + 40;
	max->menu.gamedifficultybuttons[MEDIUM] = button;
	max->menu.gamedifficultybuttons[MEDIUM].state = ACTIVE;
	max->menu.gamedifficultybuttons[MEDIUM].x = 1000;
	max->menu.gamedifficultybuttons[MEDIUM].y = 100;
	max->menu.gamedifficultybuttons[MEDIUM].text.text = S_MEDIUM;
	max->menu.gamedifficultybuttons[MEDIUM].text.sx = max->menu.gamedifficultybuttons[MEDIUM].x + 40;
	max->menu.gamedifficultybuttons[MEDIUM].text.sy = max->menu.gamedifficultybuttons[MEDIUM].y + 40;
	max->menu.gamedifficultybuttons[HARD] = button;
	max->menu.gamedifficultybuttons[HARD].state = ACTIVE;
	max->menu.gamedifficultybuttons[HARD].x = 1400;
	max->menu.gamedifficultybuttons[HARD].y = 100;
	max->menu.gamedifficultybuttons[HARD].text.text = S_HARD;
	max->menu.gamedifficultybuttons[HARD].text.sx = max->menu.gamedifficultybuttons[HARD].x + 40;
	max->menu.gamedifficultybuttons[HARD].text.sy = max->menu.gamedifficultybuttons[HARD].y + 40;
	max->menu.gamedifficultybuttons[GDBACK] = button;
	max->menu.gamedifficultybuttons[GDBACK].state = ACTIVE;
	max->menu.gamedifficultybuttons[GDBACK].x = 800;
	max->menu.gamedifficultybuttons[GDBACK].y = 300;
	max->menu.gamedifficultybuttons[GDBACK].text.text = S_BACK;
	max->menu.gamedifficultybuttons[GDBACK].text.sx = max->menu.gamedifficultybuttons[GDBACK].x + 40;
	max->menu.gamedifficultybuttons[GDBACK].text.sy = max->menu.gamedifficultybuttons[GDBACK].y + 40;
	max->menu.gamedifficultybuttons[GDCONTINUE] = button;
	max->menu.gamedifficultybuttons[GDCONTINUE].state = ACTIVE;
	max->menu.gamedifficultybuttons[GDCONTINUE].x = 1200;
	max->menu.gamedifficultybuttons[GDCONTINUE].y = 300;
	max->menu.gamedifficultybuttons[GDCONTINUE].text.text = S_CONTINUE;
	max->menu.gamedifficultybuttons[GDCONTINUE].text.sx = max->menu.gamedifficultybuttons[GDCONTINUE].x + 40;
	max->menu.gamedifficultybuttons[GDCONTINUE].text.sy = max->menu.gamedifficultybuttons[GDCONTINUE].y + 40;
	max->menu.gametypebuttons[CAMPAIGN] = button;
	max->menu.gametypebuttons[CAMPAIGN].state = INACTIVE;
	max->menu.gametypebuttons[CAMPAIGN].x = 600;
	max->menu.gametypebuttons[CAMPAIGN].y = 100;
	max->menu.gametypebuttons[CAMPAIGN].text.text = S_CAMPAIGN;
	max->menu.gametypebuttons[CAMPAIGN].text.sx = max->menu.gametypebuttons[CAMPAIGN].x + 40;
	max->menu.gametypebuttons[CAMPAIGN].text.sy = max->menu.gametypebuttons[CAMPAIGN].y + 40;
	max->menu.gametypebuttons[TIMETRIAL] = button;
	max->menu.gametypebuttons[TIMETRIAL].state = INACTIVE;
	max->menu.gametypebuttons[TIMETRIAL].x = 1000;
	max->menu.gametypebuttons[TIMETRIAL].y = 100;
	max->menu.gametypebuttons[TIMETRIAL].text.text = S_TIMETRIAL;
	max->menu.gametypebuttons[TIMETRIAL].text.sx = max->menu.gametypebuttons[TIMETRIAL].x + 40;
	max->menu.gametypebuttons[TIMETRIAL].text.sy = max->menu.gametypebuttons[TIMETRIAL].y + 40;
	max->menu.gametypebuttons[ONEMAP] = button;
	max->menu.gametypebuttons[ONEMAP].state = ACTIVE;
	max->menu.gametypebuttons[ONEMAP].x = 1400;
	max->menu.gametypebuttons[ONEMAP].y = 100;
	max->menu.gametypebuttons[ONEMAP].text.text = S_ONEMAP;
	max->menu.gametypebuttons[ONEMAP].text.sx = max->menu.gametypebuttons[ONEMAP].x + 40;
	max->menu.gametypebuttons[ONEMAP].text.sy = max->menu.gametypebuttons[ONEMAP].y + 40;
	max->menu.gametypebuttons[GTBACK] = button;
	max->menu.gametypebuttons[GTBACK].state = ACTIVE;
	max->menu.gametypebuttons[GTBACK].x = 800;
	max->menu.gametypebuttons[GTBACK].y = 300;
	max->menu.gametypebuttons[GTBACK].text.text = S_BACK;
	max->menu.gametypebuttons[GTBACK].text.sx = max->menu.gametypebuttons[GTBACK].x + 40;
	max->menu.gametypebuttons[GTBACK].text.sy = max->menu.gametypebuttons[GTBACK].y + 40;
	max->menu.gametypebuttons[GTCONTINUE] = button;
	max->menu.gametypebuttons[GTCONTINUE].state = ACTIVE;
	max->menu.gametypebuttons[GTCONTINUE].x = 1200;
	max->menu.gametypebuttons[GTCONTINUE].y = 300;
	max->menu.gametypebuttons[GTCONTINUE].text.text = S_CONTINUE;
	max->menu.gametypebuttons[GTCONTINUE].text.sx = max->menu.gametypebuttons[GTCONTINUE].x + 40;
	max->menu.gametypebuttons[GTCONTINUE].text.sy = max->menu.gametypebuttons[GTCONTINUE].y + 40;
	max->menu.maptypebuttons[CUSTOM] = button;
	max->menu.maptypebuttons[CUSTOM].state = ACTIVE;
	max->menu.maptypebuttons[CUSTOM].x = 800;
	max->menu.maptypebuttons[CUSTOM].y = 20;
	max->menu.maptypebuttons[CUSTOM].text.text = S_CUSTOM;
	max->menu.maptypebuttons[CUSTOM].text.sx = max->menu.maptypebuttons[CUSTOM].x + 40;
	max->menu.maptypebuttons[CUSTOM].text.sy = max->menu.maptypebuttons[CUSTOM].y + 40;
	max->menu.maptypebuttons[RANDOM] = button;
	max->menu.maptypebuttons[RANDOM].state = ACTIVE;
	max->menu.maptypebuttons[RANDOM].x = 1200;
	max->menu.maptypebuttons[RANDOM].y = 20;
	max->menu.maptypebuttons[RANDOM].text.text = S_RANDOM;
	max->menu.maptypebuttons[RANDOM].text.sx = max->menu.maptypebuttons[RANDOM].x + 40;
	max->menu.maptypebuttons[RANDOM].text.sy = max->menu.maptypebuttons[RANDOM].y + 40;
	max->menu.maptypebuttons[MTBACK] = button;
	max->menu.maptypebuttons[MTBACK].state = ACTIVE;
	max->menu.maptypebuttons[MTBACK].x = 800;
	max->menu.maptypebuttons[MTBACK].y = 860;
	max->menu.maptypebuttons[MTBACK].text.text = S_BACK;
	max->menu.maptypebuttons[MTBACK].text.sx = max->menu.maptypebuttons[MTBACK].x + 40;
	max->menu.maptypebuttons[MTBACK].text.sy = max->menu.maptypebuttons[MTBACK].y + 40;
	max->menu.mapselectionbuttons[CUSTOM] = button;
	max->menu.mapselectionbuttons[CUSTOM].state = ACTIVE;
	max->menu.mapselectionbuttons[CUSTOM].x = 800;
	max->menu.mapselectionbuttons[CUSTOM].y = 20;
	max->menu.mapselectionbuttons[CUSTOM].text.text = S_CUSTOM;
	max->menu.mapselectionbuttons[CUSTOM].text.sx = max->menu.mapselectionbuttons[CUSTOM].x + 40;
	max->menu.mapselectionbuttons[CUSTOM].text.sy = max->menu.mapselectionbuttons[CUSTOM].y + 40;
	max->menu.mapselectionbuttons[RANDOM] = button;
	max->menu.mapselectionbuttons[RANDOM].state = ACTIVE;
	max->menu.mapselectionbuttons[RANDOM].x = 1200;
	max->menu.mapselectionbuttons[RANDOM].y = 20;
	max->menu.mapselectionbuttons[RANDOM].text.text = S_RANDOM;
	max->menu.mapselectionbuttons[RANDOM].text.sx = max->menu.mapselectionbuttons[RANDOM].x + 40;
	max->menu.mapselectionbuttons[RANDOM].text.sy = max->menu.mapselectionbuttons[RANDOM].y + 40;
	max->menu.mapselectionbuttons[MSBACK] = button;
	max->menu.mapselectionbuttons[MSBACK].state = ACTIVE;
	max->menu.mapselectionbuttons[MSBACK].x = 800;
	max->menu.mapselectionbuttons[MSBACK].y = 860;
	max->menu.mapselectionbuttons[MSBACK].text.text = S_BACK;
	max->menu.mapselectionbuttons[MSBACK].text.sx = max->menu.mapselectionbuttons[MSBACK].x + 40;
	max->menu.mapselectionbuttons[MSBACK].text.sy = max->menu.mapselectionbuttons[MSBACK].y + 40;
	max->menu.mapselectionbuttons[MSCONTINUE] = button;
	max->menu.mapselectionbuttons[MSCONTINUE].state = ACTIVE;
	max->menu.mapselectionbuttons[MSCONTINUE].x = 1200;
	max->menu.mapselectionbuttons[MSCONTINUE].y = 860;
	max->menu.mapselectionbuttons[MSCONTINUE].text.text = S_CONTINUE;
	max->menu.mapselectionbuttons[MSCONTINUE].text.sx = max->menu.mapselectionbuttons[MSCONTINUE].x + 40;
	max->menu.mapselectionbuttons[MSCONTINUE].text.sy = max->menu.mapselectionbuttons[MSCONTINUE].y + 40;
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
// # define RBACK 10
// # define RCONTINUE 11
// # define RANDOMBUTTONCOUNT 12
	button.button = max->menu.buttonplus;
	button.text.height = 40;
	max->menu.randomselectionbuttons[RWIDTH] = button;
	max->menu.randomselectionbuttons[RWIDTH].state = ACTIVE;
	max->menu.randomselectionbuttons[RWIDTH].x = 700;
	max->menu.randomselectionbuttons[RWIDTH].y = 20;
	max->menu.randomselectionbuttons[RWIDTH].str = S_RWIDTH;
	max->menu.randomselectionbuttons[RWIDTH].val = &max->menu.rm.width;
	ft_snprintf(max->menu.randomselectionbuttons[RWIDTH].text.str, 19, "%s: %i", S_RWIDTH, max->menu.randomselectionbuttons[RWIDTH].val->value);
	max->menu.randomselectionbuttons[RWIDTH].text.text = max->menu.randomselectionbuttons[RWIDTH].text.str;
	max->menu.randomselectionbuttons[RWIDTH].text.sx = max->menu.randomselectionbuttons[RWIDTH].x + 110;
	max->menu.randomselectionbuttons[RWIDTH].text.sy = max->menu.randomselectionbuttons[RWIDTH].y + 50;
	max->menu.randomselectionbuttons[RHEIGHT] = button;
	max->menu.randomselectionbuttons[RHEIGHT].state = ACTIVE;
	max->menu.randomselectionbuttons[RHEIGHT].x = 1250;
	max->menu.randomselectionbuttons[RHEIGHT].y = 20;
	ft_snprintf(max->menu.randomselectionbuttons[RHEIGHT].text.str, 19, "RHEIGHT: %i", 32);
	max->menu.randomselectionbuttons[RHEIGHT].text.text = max->menu.randomselectionbuttons[RHEIGHT].text.str;
	max->menu.randomselectionbuttons[RHEIGHT].text.sx = max->menu.randomselectionbuttons[RHEIGHT].x + 110;
	max->menu.randomselectionbuttons[RHEIGHT].text.sy = max->menu.randomselectionbuttons[RHEIGHT].y + 50;
	max->menu.randomselectionbuttons[RRATIODE] = button;
	max->menu.randomselectionbuttons[RRATIODE].state = ACTIVE;
	max->menu.randomselectionbuttons[RRATIODE].x = 700;
	max->menu.randomselectionbuttons[RRATIODE].y = 160;
	ft_snprintf(max->menu.randomselectionbuttons[RRATIODE].text.str, 19, "RRATIODE: %i", 32);
	max->menu.randomselectionbuttons[RRATIODE].text.text = max->menu.randomselectionbuttons[RRATIODE].text.str;
	max->menu.randomselectionbuttons[RRATIODE].text.sx = max->menu.randomselectionbuttons[RRATIODE].x + 110;
	max->menu.randomselectionbuttons[RRATIODE].text.sy = max->menu.randomselectionbuttons[RRATIODE].y + 50;
	max->menu.randomselectionbuttons[RRATIOLO] = button;
	max->menu.randomselectionbuttons[RRATIOLO].state = ACTIVE;
	max->menu.randomselectionbuttons[RRATIOLO].x = 1250;
	max->menu.randomselectionbuttons[RRATIOLO].y = 160;
	ft_snprintf(max->menu.randomselectionbuttons[RRATIOLO].text.str, 19, "RRATIOLO: %i", 32);
	max->menu.randomselectionbuttons[RRATIOLO].text.text = max->menu.randomselectionbuttons[RRATIOLO].text.str;
	max->menu.randomselectionbuttons[RRATIOLO].text.sx = max->menu.randomselectionbuttons[RRATIOLO].x + 110;
	max->menu.randomselectionbuttons[RRATIOLO].text.sy = max->menu.randomselectionbuttons[RRATIOLO].y + 50;
	max->menu.randomselectionbuttons[RRATIOTI] = button;
	max->menu.randomselectionbuttons[RRATIOTI].state = ACTIVE;
	max->menu.randomselectionbuttons[RRATIOTI].x = 700;
	max->menu.randomselectionbuttons[RRATIOTI].y = 300;
	ft_snprintf(max->menu.randomselectionbuttons[RRATIOTI].text.str, 19, "RRATIOTI: %i", 32);
	max->menu.randomselectionbuttons[RRATIOTI].text.text = max->menu.randomselectionbuttons[RRATIOTI].text.str;
	max->menu.randomselectionbuttons[RRATIOTI].text.sx = max->menu.randomselectionbuttons[RRATIOTI].x + 110;
	max->menu.randomselectionbuttons[RRATIOTI].text.sy = max->menu.randomselectionbuttons[RRATIOTI].y + 50;
	max->menu.randomselectionbuttons[RRATIOXI] = button;
	max->menu.randomselectionbuttons[RRATIOXI].state = ACTIVE;
	max->menu.randomselectionbuttons[RRATIOXI].x = 1250;
	max->menu.randomselectionbuttons[RRATIOXI].y = 300;
	ft_snprintf(max->menu.randomselectionbuttons[RRATIOXI].text.str, 19, "RRATIOXI: %i", 32);
	max->menu.randomselectionbuttons[RRATIOXI].text.text = max->menu.randomselectionbuttons[RRATIOXI].text.str;
	max->menu.randomselectionbuttons[RRATIOXI].text.sx = max->menu.randomselectionbuttons[RRATIOXI].x + 110;
	max->menu.randomselectionbuttons[RRATIOXI].text.sy = max->menu.randomselectionbuttons[RRATIOXI].y + 50;
	max->menu.randomselectionbuttons[RNOROOMS] = button;
	max->menu.randomselectionbuttons[RNOROOMS].state = ACTIVE;
	max->menu.randomselectionbuttons[RNOROOMS].x = 700;
	max->menu.randomselectionbuttons[RNOROOMS].y = 440;
	ft_snprintf(max->menu.randomselectionbuttons[RNOROOMS].text.str, 19, "RNOROOMS: %i", 32);
	max->menu.randomselectionbuttons[RNOROOMS].text.text = max->menu.randomselectionbuttons[RNOROOMS].text.str;
	ft_printf("%s\n", max->menu.randomselectionbuttons[RNOROOMS].text.str);
	ft_printf("%s\n", max->menu.randomselectionbuttons[RNOROOMS].text.text);
	max->menu.randomselectionbuttons[RNOROOMS].text.sx = max->menu.randomselectionbuttons[RNOROOMS].x + 110;
	max->menu.randomselectionbuttons[RNOROOMS].text.sy = max->menu.randomselectionbuttons[RNOROOMS].y + 50;
	max->menu.randomselectionbuttons[ROROOMS] = button;
	max->menu.randomselectionbuttons[ROROOMS].state = ACTIVE;
	max->menu.randomselectionbuttons[ROROOMS].x = 1250;
	max->menu.randomselectionbuttons[ROROOMS].y = 440;
	ft_snprintf(max->menu.randomselectionbuttons[ROROOMS].text.str, 19, "ROROOMS: %i", 32);
	max->menu.randomselectionbuttons[ROROOMS].text.text = max->menu.randomselectionbuttons[ROROOMS].text.str;
	max->menu.randomselectionbuttons[ROROOMS].text.sx = max->menu.randomselectionbuttons[ROROOMS].x + 110;
	max->menu.randomselectionbuttons[ROROOMS].text.sy = max->menu.randomselectionbuttons[ROROOMS].y + 50;
	max->menu.randomselectionbuttons[RDOORS] = button;
	max->menu.randomselectionbuttons[RDOORS].state = ACTIVE;
	max->menu.randomselectionbuttons[RDOORS].x = 700;
	max->menu.randomselectionbuttons[RDOORS].y = 580;
	ft_snprintf(max->menu.randomselectionbuttons[RDOORS].text.str, 19, "RDOORS: %i", 32);
	max->menu.randomselectionbuttons[RDOORS].text.text = max->menu.randomselectionbuttons[RDOORS].text.str;
	max->menu.randomselectionbuttons[RDOORS].text.sx = max->menu.randomselectionbuttons[RDOORS].x + 110;
	max->menu.randomselectionbuttons[RDOORS].text.sy = max->menu.randomselectionbuttons[RDOORS].y + 50;
	max->menu.randomselectionbuttons[RDEADENDS] = button;
	max->menu.randomselectionbuttons[RDEADENDS].state = ACTIVE;
	max->menu.randomselectionbuttons[RDEADENDS].x = 1250;
	max->menu.randomselectionbuttons[RDEADENDS].y = 580;
	ft_snprintf(max->menu.randomselectionbuttons[RDEADENDS].text.str, 19, "RDEADENDS: %i", 32);
	max->menu.randomselectionbuttons[RDEADENDS].text.text = max->menu.randomselectionbuttons[RDEADENDS].text.str;
	max->menu.randomselectionbuttons[RDEADENDS].text.sx = max->menu.randomselectionbuttons[RDEADENDS].x + 110;
	max->menu.randomselectionbuttons[RDEADENDS].text.sy = max->menu.randomselectionbuttons[RDEADENDS].y + 50;
	button.text.height = 60;
	button.button = max->menu.button;
	max->menu.randomselectionbuttons[RBACK] = button;
	max->menu.randomselectionbuttons[RBACK].state = ACTIVE;
	max->menu.randomselectionbuttons[RBACK].x = 850;
	max->menu.randomselectionbuttons[RBACK].y = 860;
	max->menu.randomselectionbuttons[RBACK].text.text = S_BACK;
	max->menu.randomselectionbuttons[RBACK].text.sx = max->menu.randomselectionbuttons[RBACK].x + 40;
	max->menu.randomselectionbuttons[RBACK].text.sy = max->menu.randomselectionbuttons[RBACK].y + 40;
	max->menu.randomselectionbuttons[RCONTINUE] = button;
	max->menu.randomselectionbuttons[RCONTINUE].state = ACTIVE;
	max->menu.randomselectionbuttons[RCONTINUE].x = 1250;
	max->menu.randomselectionbuttons[RCONTINUE].y = 860;
	max->menu.randomselectionbuttons[RCONTINUE].text.text = S_CONTINUE;
	max->menu.randomselectionbuttons[RCONTINUE].text.sx = max->menu.randomselectionbuttons[RCONTINUE].x + 40;
	max->menu.randomselectionbuttons[RCONTINUE].text.sy = max->menu.randomselectionbuttons[RCONTINUE].y + 40;
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
	if (max->key.add)
	{
		++i;
		max->key.add = 0;
	}
	if (max->key.subtract)
	{
		--i;
		max->key.subtract = 0;
	}
	if (max->key.multiply)
	{
		i *= 2;
		max->key.multiply = 0;
	}
	if (max->key.divide)
	{
		i /= 2;
		max->key.divide = 0;
	}
	if (i < button->val->min)
		i = button->val->min;
	if (i > button->val->max)
		i = button->val->max;
	button->val->value = i;
	ft_snprintf(max->menu.randomselectionbuttons[RWIDTH].text.str, 19, "%s: %i", button->str, button->val->value);
}
