/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamestart.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:57:06 by okraus            #+#    #+#             */
/*   Updated: 2024/05/10 17:55:38 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_initgamestart(t_max *max)
{
	max->gamestart.background = max->t.textbg;
	max->gamestart.text = "Lorem ipsum dolor sit amet,\
	consectetur adipiscing elit, sed do eiusmod tempor incididunt\
	ut labore et dolore magna aliqua.";
	max->gamestart.font = max->font.asciitest;
	max->gamestart.image = max->i.textscreen;
	max->gamestart.c = 0XFF;
	max->gamestart.cb = 0;
	max->gamestart.sx = 200;
	max->gamestart.sy = 100;
	max->gamestart.x = 0;
	max->gamestart.y = 0;
	max->gamestart.height = 80;
	max->gamestart.highlight = -1;
	max->gamestart.i = 0;
}

void	ft_draw_background(t_max *max)
{
	t_dbgs	dbgs;

	dbgs.w = max->gamestart.background->width;
	dbgs.h = max->gamestart.background->height;
	dbgs.y = 0;
	while (dbgs.y < dbgs.h)
	{
		dbgs.x = 0;
		while (dbgs.x < dbgs.w)
		{
			dbgs.a = (dbgs.y * dbgs.w * 4) + (dbgs.x * 4);
			if (dbgs.x < dbgs.w && dbgs.y < dbgs.h)
				dbgs.c = (max->gamestart.background->pixels[dbgs.a]) << 24
					| (max->gamestart.background->pixels[dbgs.a + 1]) << 16
					| (max->gamestart.background->pixels[dbgs.a + 2]) << 8
					| 0xFF;
			else
				dbgs.c = 0xFF00FFFF;
			mlx_put_pixel(max->i.textscreen, dbgs.x, dbgs.y, dbgs.c);
			++dbgs.x;
		}
		++dbgs.y;
	}
}

void	ft_draw_gamechar_2(t_gametext *text, t_db *db)
{
	db->a = (db->j * (240 / text->height) * 11400 * 4)
		+ ((db->i * (240 / text->height) + text->offset) * 4);
	db->c = (text->font->pixels[db->a]) << 24
		| (text->font->pixels[db->a + 1]) << 16
		| (text->font->pixels[db->a + 2]) << 8
		| (text->font->pixels[db->a + 3]);
}

void	ft_draw_gamechar(t_gametext *text)
{
	t_db	db;

	db.w = text->height / 2;
	db.h = text->height;
	db.j = 0;
	while (db.j < db.h)
	{
		db.i = 0;
		while (db.i < db.w)
		{
			ft_draw_gamechar_2(text, &db);
			if (db.c < 0x7FFFFFFF)
				mlx_put_pixel(text->image, db.i + text->x, db.j
					+ text->y, text->c);
			else if (text->cb)
				mlx_put_pixel(text->image, db.i + text->x, db.j
					+ text->y, text->cb);
			++db.i;
		}
		++db.j;
	}
}

void	ft_draw_gametext_2(t_gametext *text, int i)
{
	if (ft_isprint(text->text[i]))
	{
		text->offset = (text->text[i] - ' ') * 120;
		if (text->offset)
			text->offset -= 2;
		ft_draw_gamechar(text);
		text->x += text->height / 2;
	}
	else if (text->text[i] == '\t')
		text->x += text->height * 2;
	else if (text->text[i] == '\n')
	{
		text->y += text->height;
		text->x = text->sx;
	}
}

void	ft_draw_gametext(t_gametext *text)
{
	int				i;
	unsigned int	oldcb;

	oldcb = text->cb;
	i = 0;
	text->x = text->sx;
	text->y = text->sy;
	while (text->text[i])
	{
		text->cb = oldcb;
		if (i == text->highlight)
			text->cb = 0x00FF00FF;
		if (i > text->i)
			return ;
		if (text->x > 1920 - 200 - text->height / 2)
		{
			text->y += text->height;
			text->x = text->sx;
		}
		if (text->y > 1080 - 100 - text->height)
			return ;
		ft_draw_gametext_2(text, i);
		++i;
	}
	text->cb = oldcb;
}

void	ft_gamestart_2(t_max *max)
{
	max->settings.lightdist = max->settings.maxdist / 4;
	max->game_mode = GAMEPLAY;
	ft_init_rayangles(max);
	ft_init_orays(max);
	ft_init_fogscreen(max);
	max->i.textscreen->enabled = 0;
	max->i.maximap->enabled = 0;
	max->i.overlay->enabled = 1;
	max->game_in_progress = 1;
	max->gamestart.i = 0;
	max->levelms = 0;
	max->keys[MLX_KEY_ENTER] = 0;
}

void	ft_gamestart(t_max *max)
{
	max->gamestart.timems += max->framems;
	ft_draw_background(max);
	if (max->gamestart.timems >= 25)
	{
		max->gamestart.timems = 0;
		if (max->gamestart.i <= (int)ft_strlen(max->gamestart.text))
			++max->gamestart.i;
	}
	if (max->keys[MLX_KEY_SPACE])
	{
		max->gamestart.i = (int)ft_strlen(max->gamestart.text);
		max->keys[MLX_KEY_SPACE] = 0;
	}
	ft_draw_gametext(&max->gamestart);
	if (max->keys[MLX_KEY_ENTER])
		ft_gamestart_2(max);
}

void	ft_initgamewon(t_max *max)
{
	max->gamewon.background = max->gamestart.background;
	max->gamewon.text = max->gamewon.stats;
	ft_sprintf(max->gamewon.stats, "You won!\nCongratulations!\n");
	max->gamewon.font = max->font.asciitest;
	max->gamewon.image = max->i.textscreen;
	max->gamewon.c = 0XFF;
	max->gamewon.cb = 0;
	max->gamewon.sx = 200;
	max->gamewon.sy = 100;
	max->gamewon.x = 0;
	max->gamewon.y = 0;
	max->gamewon.height = 80;
	max->gamewon.highlight = -1;
	max->gamewon.i = 0;
}

void	ft_gamewon(t_max *max)
{
	max->gamewon.timems += max->framems;
	ft_draw_background(max);
	if (max->gamewon.timems >= 25)
	{
		max->gamewon.timems = 0;
		if (max->gamewon.i <= (int)ft_strlen(max->gamewon.text))
			++max->gamewon.i;
	}
	if (max->keys[MLX_KEY_SPACE])
	{
		max->gamewon.i = (int)ft_strlen(max->gamewon.text);
		max->keys[MLX_KEY_SPACE] = 0;
	}
	ft_draw_gametext(&max->gamewon);
	if (max->keys[MLX_KEY_ENTER])
	{
		if (max->game_type == ONEMAP)
		{
			max->game_mode = MENU;
			max->i.textscreen->enabled = 0;
			max->game_in_progress = 0;
			max->gamewon.i = 0;
			max->keys[MLX_KEY_ENTER] = 0;
		}
		if (max->game_type == TIMETRIAL)
		{
			++max->level;
			ft_inittimetrialmap(&max->menu.rm, max->level);
			ft_snprintf(max->map.file, 4095, "RANDOM");
			if (ft_process_random(max))
			{
				printf("gamestart loop starting...\n");
				max->game_mode = GAMESTART;
				max->menu.current_button[MAINBUTTONS] = RESUME;
				max->menu.current_buttongroup = MAINBUTTONS;
				max->game_in_progress = 0;
				max->i.menuscreen->enabled = 0;
				max->i.textscreen->enabled = 1;
			}
			else
			{
				ft_dprintf(2, "Invalid map\n");
			}
			max->keys[MLX_KEY_ENTER] = 0;
		}
		if (max->game_type == CAMPAIGN)
		{
			++max->level;
			if (max->level > 4)
			{
				max->game_mode = MENU;
				max->i.textscreen->enabled = 0;
				max->game_in_progress = 0;
				max->gamewon.i = 0;
				max->gamems = 0;
				max->keys[MLX_KEY_ENTER] = 0;
			}
			ft_sprintf(max->campaignmap, "./campaign/map%i.cub", max->level);
			ft_snprintf(max->map.file, 4095, max->campaignmap);
			if (ft_process_file(max))
			{
				printf("gamestart loop starting...\n");
				max->game_mode = GAMESTART;
				max->menu.current_button[MAINBUTTONS] = RESUME;
				max->menu.current_buttongroup = MAINBUTTONS;
				max->game_in_progress = 0;
				max->i.menuscreen->enabled = 0;
				max->i.textscreen->enabled = 1;
			}
			else
			{
				ft_dprintf(2, "Invalid map\n");
			}
			max->keys[MLX_KEY_ENTER] = 0;
		}
	}
}

void	ft_initgamelost(t_max *max)
{
	max->gamelost.background = max->gamestart.background;
	max->gamelost.text = max->gamelost.stats;
	ft_sprintf(max->gamelost.stats, "You lost:(\n");
	max->gamelost.font = max->font.asciitest;
	max->gamelost.image = max->i.textscreen;
	max->gamelost.c = 0XFF;
	max->gamelost.cb = 0;
	max->gamelost.sx = 200;
	max->gamelost.sy = 100;
	max->gamelost.x = 0;
	max->gamelost.y = 0;
	max->gamelost.height = 80;
	max->gamelost.highlight = -1;
	max->gamelost.i = 0;
}

void	ft_gamelost(t_max *max)
{
	max->gamelost.timems += max->framems;
	ft_draw_background(max);
	if (max->gamelost.timems >= 25)
	{
		max->gamelost.timems = 0;
		if (max->gamelost.i <= (int)ft_strlen(max->gamelost.text))
			++max->gamelost.i;
	}
	if (max->keys[MLX_KEY_SPACE])
	{
		max->gamelost.i = (int)ft_strlen(max->gamelost.text);
		max->keys[MLX_KEY_SPACE] = 0;
	}
	ft_draw_gametext(&max->gamelost);
	if (max->keys[MLX_KEY_ENTER])
	{
		if (max->game_type == ONEMAP)
		{
			max->game_mode = MENU;
			max->gamems = 0;
			max->i.textscreen->enabled = 0;
			max->game_in_progress = 0;
			max->gamelost.i = 0;
			max->keys[MLX_KEY_ENTER] = 0;
		}
		if (max->game_type == TIMETRIAL)
		{
			max->game_mode = MENU;
			if (ft_writescore(max))
				ft_printf("Warning: Could not write the final score\n");
			max->gamems = 0;
			max->i.textscreen->enabled = 0;
			max->game_in_progress = 0;
			max->gamelost.i = 0;
			max->keys[MLX_KEY_ENTER] = 0;
		}
		if (max->game_type == CAMPAIGN)
		{
			max->game_mode = MENU;
			max->gamems = 0;
			max->i.textscreen->enabled = 0;
			max->game_in_progress = 0;
			max->gamelost.i = 0;
			max->keys[MLX_KEY_ENTER] = 0;
		}
	}
}
