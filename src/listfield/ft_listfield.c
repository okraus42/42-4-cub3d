/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listfield.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <tlukanie@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:00:54 by okraus            #+#    #+#             */
/*   Updated: 2024/05/11 19:03:06 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_reinitlistfield(t_listfield	*listfield)
{
	int	i;

	i = 0;
	while (listfield->files && listfield->files[i + listfield->topfile]
		&& i < 10)
	{
		listfield->text[i].text = listfield->files[i + listfield->topfile];
		++i;
	}
	while (i < 10)
	{
		listfield->text[i].text = " - - - ";
		++i;
	}
}

void	ft_draw_listfield_inner(t_listfield *lf, t_db dl)
{
	dl.i = 0;
	while (dl.i < dl.w)
	{
		dl.a = (dl.j * dl.w * 4) + (dl.i * 4);
		if (dl.i < dl.w && dl.j < dl.h)
			dl.c = (lf->listfield->pixels[dl.a]) << 24
				| (lf->listfield->pixels[dl.a + 1]) << 16
				| (lf->listfield->pixels[dl.a + 2]) << 8
				| (lf->listfield->pixels[dl.a + 3]);
		else
			dl.c = 0xFF00FFFF;
		if (dl.c & 0xFFFFFF00)
			mlx_put_pixel(lf->image, dl.i + lf->x, dl.j + lf->y, 0xFF);
		else if ((dl.c & 0xFF) == 0xFF)
			mlx_put_pixel(lf->image, dl.i + lf->x, dl.j + lf->y, dl.c);
		++dl.i;
	}
}

void	ft_draw_listfield(t_listfield *lf, int state)
{
	t_db	dl;

	lf->state = state;
	dl.w = lf->listfield->width;
	dl.h = lf->listfield->height;
	dl.j = 0;
	ft_reinitlistfield(lf);
	while (dl.j < dl.h)
	{
		ft_draw_listfield_inner(lf, dl);
		++dl.j;
	}
	lf->text[lf->highlight].c = 0xFF;
	lf->text[lf->highlight].cb = 0x00FF00FF;
	dl.i = 0;
	while (dl.i < 10)
	{
		ft_draw_text(&lf->text[dl.i], state);
		++dl.i;
	}
}

//topitemnumber
//total items number

void	ft_choose_in_listfield_keys(t_max *max, int *i)
{
	if (max->keys[MLX_KEY_UP])
	{
		--(*i);
		max->keys[MLX_KEY_UP] = 0;
	}
	if (max->keys[MLX_KEY_DOWN])
	{
		++(*i);
		max->keys[MLX_KEY_DOWN] = 0;
	}
}

void	ft_choose_in_listfield(t_max *max, t_listfield *listfield)
{
	int	i;

	i = listfield->highlight;
	listfield->text[i].cb = 0;
	listfield->text[i].c = 0x00FF00FF;
	ft_choose_in_listfield_keys(max, &i);
	if (i < 0)
	{
		i = 0;
		if (listfield->topfile > 0)
			--listfield->topfile;
	}
	if (i > 9)
	{
		i = 9;
		if (listfield->topfile < listfield->totalfiles - 10)
			++listfield->topfile;
	}
	if (i && i >= listfield->totalfiles - listfield->topfile)
		--i;
	listfield->highlight = i;
}
