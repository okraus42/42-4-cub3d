/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamestart_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:23:25 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/11 14:24:45 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

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
