/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons_11.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:05:07 by tlukanie          #+#    #+#             */
/*   Updated: 2024/05/09 17:19:10 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_draw_button_2(t_button *b, int state, t_db db)
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

void	ft_draw_button_3(t_button *b, t_db *db)
{
	db->c = (b->button->pixels[db->a]) << 24
		| (b->button->pixels[db->a + 1]) << 16
		| (b->button->pixels[db->a + 2])
		<< 8 | (b->button->pixels[db->a + 3]);
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
				ft_draw_button_3(b, &db);
			else
				db.c = 0xFF00FFFF;
			if (db.c & 0xFFFFFF00)
				ft_draw_button_2(b, state, db);
			else if ((db.c & 0xFF) == 0xFF)
				mlx_put_pixel(b->image, db.i + b->x, db.j + b->y, db.c);
			++db.i;
		}
		++db.j;
	}
	ft_draw_text(&b->text, state);
}
